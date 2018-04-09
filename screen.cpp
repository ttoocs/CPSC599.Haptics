#include "./libvnc/rfb/rfbclient.h"
#include "screen.h"
// rfbClient* client  = rfbGetClient(8,3,4);
// time_t t=time(NULL);

Screen::Screen(){
  client  = rfbGetClient(8,3,4);

  rfbPixelFormat* pf=&client->format;
  int bpp=pf->bitsPerPixel/8;
  int row_stride=client->width*bpp;

  //Data seems to hide in client->frameBuffer+j+i
}

