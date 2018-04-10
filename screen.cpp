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
// chai3d::cImage img;
// chai3d::cTexture2d tex;
  chai3d::cImagePtr img = chai3d::cImage::create();
  chai3d::cTexture2dPtr tex = chai3d::cTexture2d::create();


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
static uint32_t get(rfbClient *cl, int x, int y)
{
//        switch (bytesPerPixel) {
        switch (4) {
        case 1: return ((uint8_t *)cl->frameBuffer)[x + y * cl->width];
        case 2: return ((uint16_t *)cl->frameBuffer)[x + y * cl->width];
        case 4: return ((uint32_t *)cl->frameBuffer)[x + y * cl->width];
        default:
                //rfbClientErr("Unknown bytes/pixel: %d", bytesPerPixel);
                exit(1);
        }
}



void update(rfbClient* client, int x, int y, int w, int h){
//    std::cout << "(" << x << "," << y << "," << w << "," << h << ")" << std::endl;

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
// /*
//    for(ix=x; ix < w; ix++){
//      for(iy=y; iy < h; iy++){ 
// */

//    #pragma omp parallel for
 /*
//    for(int j=0;j<client->height*row_stride;j+=row_stride){
//      for(int i=0;i<client->width*bpp;i+=bpp) {
        int j = client->height*row_stride*y;
        int i = bpp*x;
//        uint32_t p = get(client, ix,iy);
//        std::cout << "p: \t" << p << std::endl;
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

// */
//        R /=256;
//        G /=256;
//        B /=256;
        
//        chai3d::cColorb c = chai3d::cColorb(chai3d::cColorBtoF(R),chai3d::cColorBtoF(G),chai3d::cColorBtoF(B));
//          int offset = y*row_stride + x;
//          GLubyte r = *(client->frameBuffer+offset);
//          GLubyte g = *(client->frameBuffer+offset + 1);
//          GLubyte b = *(client->frameBuffer+offset + 2);

//          chai3d::cColorb c =chai3d::cColorb(r,g,b);
//          chai3d::cColorb c = chai3d::cColorb(255,0,0); 
//          std::cout << "(" << R << "," << G << "," << B << ")" << std::endl;
//        unsigned char * d = img->getData();
//        d[x + y*img->getHeight()] = 0xff;
//        img->setPixelColor(ix,iy,c);
//        ix++;
//      }
//    iy++;
//  }
  int bytesPerPixel = client->format.bitsPerPixel / 8;
  img->setData(client->frameBuffer, client->width * bytesPerPixel * client->height, false);
  //std::cout << img->getWidth() << std::endl;
  tex->setImage(img);
}

bool connected = false;
int cnt=0;

void check(){
  if(!connected)
    return;
  if(cnt > 0){
    SendFramebufferUpdateRequest (client, 0, 0, client->width, client->height, FALSE);
    WaitForMessage(client,1);
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
    connected=false;
  }else
    connected = true;
 

  //Data seems to hide in client->frameBuffer+j+i

  client->GotFrameBufferUpdate = update;
//  client->FinishedFrameBufferUpdate = update;

    
  //img->allocate(client->width, client->height,GL_RGB,GL_UNSIGNED_INT);
//  img->allocate(1, 1,GL_RGB,GL_UNSIGNED_INT);
 // img->cImage::clear(chai3d::cColorb(0xff,0,0));
  
  tex->setImage(img);
  tex->setWrapModeS(GL_REPEAT);
  
  tex->loadFromFile("/tmp/pic.png");
  img = tex->m_image;
 img->convert(GL_RGBA);
 

//  std::cout << client->width << "," <<  client->height << std::endl; //Img size OK
  
  //Set Img to RFB buffer?
// int bytesPerPixel = client->format.bitsPerPixel / 8;
//  img->setData(client->frameBuffer, client->width * bytesPerPixel * client->height, false);

  
  
}


};
