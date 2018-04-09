#include "./libvnc/rfb/rfbclient.h"
#include "screen.h"
#include "chai3d.h"
#include <iostream>
// rfbClient* client  = rfbGetClient(8,3,4);
// time_t t=time(NULL);

#include <string>

extern int argc_p;
extern char* argv_p[];

namespace Screen{

  rfbClient* client; 
  chai3d::cImage img;
  chai3d::cImage img_b;

  



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
//  std::cout << "VNC UPDATE" << std::endl;

}

int cnt=0;
void check(){
  if(cnt > 30){
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

}


};
