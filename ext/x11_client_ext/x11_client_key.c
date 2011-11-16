#include "x11_client.h"
#include "x11_client_key.h"

#include <X11/extensions/XTest.h>
#include <unistd.h>

VALUE X11Client_keydown(VALUE self, VALUE keysym) {
  X11Client *client;
  KeyCode keycode;
  Data_Get_Struct(self, X11Client, client);

  printf("keydown\n", keycode);

  keycode = XKeysymToKeycode (client->display, NUM2INT(keysym));
  if (keycode == 0) return self;  

  printf("keydown sent with keysym %d\n", keycode);

  XTestFakeKeyEvent(client->display, keycode, True, CurrentTime);

  return self;
}

VALUE X11Client_keyup(VALUE self, VALUE keysym) {
  X11Client *client;
  KeyCode keycode;
  Data_Get_Struct(self, X11Client, client);

  printf("keydown\n", keycode);

  keycode = XKeysymToKeycode (client->display, NUM2INT(keysym));  
  if (keycode == 0) return self;  

  printf("keyup sent with keysym %d\n", keycode);

  XTestFakeKeyEvent(client->display, keycode, False, CurrentTime);
  return self;
}

VALUE X11Client_keypress(VALUE self, VALUE keysym) {
  X11Client_keydown(self, keysym);
  sleep(0.01);
  X11Client_keyup(self, keysym);

  return self;
}

