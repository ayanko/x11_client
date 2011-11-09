#include "x11_client.h"
#include "x11_client_mouse.h"

#include <X11/extensions/XTest.h>
#include <unistd.h>

VALUE X11Client_mousemove(VALUE self, VALUE x, VALUE y) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  XTestFakeMotionEvent(client->display, 0, NUM2INT(x), NUM2INT(y), CurrentTime);
  return self;
}

VALUE X11Client_mousedown(VALUE self, VALUE button) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  XTestFakeButtonEvent(client->display, NUM2INT(button), True,  CurrentTime);
  return self;
}

VALUE X11Client_mouseup(VALUE self, VALUE button) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  XTestFakeButtonEvent(client->display, NUM2INT(button), False,  CurrentTime);
  return self;
}

VALUE X11Client_mouseclick(VALUE self, VALUE button) {
  X11Client_mousedown(self, button);
  sleep(0.01);
  X11Client_mouseup(self, button);
  return self;
}

