#pragma once

#include <rfb/rfbclient.h>

class Screen{
  public:
    rfbClient* client;// = rfbGetClient(8,3,4);
//    time_t t=time(NULL);

    Screen();

};



