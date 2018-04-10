#include "./libvnc/rfb/rfbclient.h"
#include "screen.h"
#include "chai3d.h"
#include <iostream>
// rfbClient* client  = rfbGetClient(8,3,4);
// time_t t=time(NULL);

#include <string>

#include "screen_keyhelp.h"

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

  int bytesPerPixel = client->format.bitsPerPixel / 8;
  img->setData(client->frameBuffer, client->width * bytesPerPixel * client->height, false);
//  std::cout << img->getFormat() << "," << img->getType()  << std::endl;
    //6408,5121
  if(img->getWidth() == 0){
    std::cout << "VNC resolution diff. " << std::endl;
//    img->setProperties(client->width, client->height, img->getFormat(), img->getType());
//    img->setProperties(client->width, client->height, GL_RGBA, GL_UNSIGNED_INT);//GL_UNSIGNED_INT);
 //   img->setData(client->frameBuffer, client->width * bytesPerPixel * client->height, false);
  }
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

void sendKey(char c){
  SendKeyEvent(client, getKey(c), true); 
  SendKeyEvent(client, getKey(c), false); 
}



};
