#include "./libvnc/rfb/rfbclient.h"
#include "screen.h"
#include "chai3d.h"
#include <iostream>
// rfbClient* client  = rfbGetClient(8,3,4);
// time_t t=time(NULL);

#include <string>

//#include "gl_helpers.h"

extern int argc_p;
extern char* argv_p[];

namespace Screen{

  rfbClient* client; 
  std::shared_ptr<chai3d::cImage> img;
  std::shared_ptr<chai3d::cTexture2d> tex;
  



///////////////////////////LIBVNC snippit, cuase.. why not? Why include this? pff.

static rfbBool rfbInitConnection(rfbClient* client)
{
  /* Unless we accepted an incoming connection, make a TCP connection to the
     given VNC server */

  if (!client->listenSpecified) {
    if (!client->serverHost)
      return FALSE;
    if (client->destHost) {
      if (!ConnectToRFBRepeater(client,client->serverHost,client->serverPort,client->destHost,client->destPort))
        return FALSE;
    } else {
      if (!ConnectToRFBServer(client,client->serverHost,client->serverPort))
        return FALSE;
    }
  }

  /* Initialise the VNC connection, including reading the password */

  if (!InitialiseRFBConnection(client))
    return FALSE;

  client->width=client->si.framebufferWidth;
  client->height=client->si.framebufferHeight;
  if (!client->MallocFrameBuffer(client))
    return FALSE;

  if (!SetFormatAndEncodings(client))
    return FALSE;

  if (client->updateRect.x < 0) {
    client->updateRect.x = client->updateRect.y = 0;
    client->updateRect.w = client->width;
    client->updateRect.h = client->height;
  }

  if (client->appData.scaleSetting>1)
  {
      if (!SendScaleSetting(client, client->appData.scaleSetting))
          return FALSE;
      if (!SendFramebufferUpdateRequest(client,
			      client->updateRect.x / client->appData.scaleSetting,
			      client->updateRect.y / client->appData.scaleSetting,
			      client->updateRect.w / client->appData.scaleSetting,
			      client->updateRect.h / client->appData.scaleSetting,
			      FALSE))
	      return FALSE;
  }
  else
  {
      if (!SendFramebufferUpdateRequest(client,
			      client->updateRect.x, client->updateRect.y,
			      client->updateRect.w, client->updateRect.h,
			      FALSE))
      return FALSE;
  }

  return TRUE;
}



void update(rfbClient* client, int x, int y, int w, int h){
    return;
//  std::cout << "VNC UPDATE" << std::endl;
    rfbPixelFormat* pf=&client->format;
//    PrintPixelFormat (pf);
//    32 bits per pixel.
//    Least significant byte first in each pixel.
//    TRUE colour: max red 255 green 255 blue 255, shift red 0 green 8 blue 16

      //Manual stuffs
    //unsigned char* d = img.getData();
   
    int bpp=pf->bitsPerPixel/8;
    int row_stride=client->width*bpp;
    int ix=0;
    int iy=0;
/*
    for(int x=0; x < img.getWidth(); x++){
      for(int y=0; y < img.getHeight(); y++){ */
    #pragma omp parallel for
    for(int j=0;j<client->height*row_stride;j+=row_stride){
      for(int i=0;i<client->width*bpp;i+=bpp) {
        unsigned char* p=client->frameBuffer+j+i;
                        unsigned int v;
                        if(bpp==4)
                                v=*(unsigned int*)p;
                        else if(bpp==2)
                                v=*(unsigned short*)p;
                        else
                                v=*(unsigned char*)p;
        
        GLubyte R = (v>>pf->redShift)*256/(pf->redMax+1);
        GLubyte G = (v>>pf->greenShift)*256/(pf->greenMax+1);
        GLubyte B = (v>>pf->blueShift)*256/(pf->blueMax+1);
//        R /=256;
//        G /=256;
//        B /=256;
        chai3d::cColorb c = chai3d::cColorb(chai3d::cColorBtoF(R),chai3d::cColorBtoF(G),chai3d::cColorBtoF(B));

//          std::cout << "(" << R << "," << G << "," << B << ")" << std::endl;

        //img->setPixelColor(ix,iy,c);
        ix++;
      }
    iy++;
  }
  //tex->setImage(img);
}

int cnt=0;
void check(){
  if(cnt > 100){
    WaitForMessage(client,0);
    HandleRFBServerMessage(client);
    cnt = 0;
  }
  cnt++;
}

void InitScreen(){
 

  client  = rfbGetClient(8,3,4);

  rfbPixelFormat* pf=&client->format;
  int bpp=pf->bitsPerPixel/8;
  int row_stride=client->width*bpp;

  strcpy(client->serverHost, std::string("localhost").c_str());
  client->serverPort = 5900;

//    rfbInitConnection(client)
  if(!rfbInitConnection(client)){
    std::cout << "No VNC client." << std::endl;
  }

  //Data seems to hide in client->frameBuffer+j+i

  client->GotFrameBufferUpdate = update;

  
//  img->allocate(client->width, client->height,GL_RGB,GL_UNSIGNED_INT);
//  std::cout << client->width << "," <<  client->height << std::endl; //Img size OK
  
  //Set Img to RFB buffer?
//  img.setData(client->framebuffer, client->size
  
  
}


};
