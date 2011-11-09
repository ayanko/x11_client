#include "x11_client.h"

#include "x11_client_display.h"

#include "x11_client_utils.h"

static VALUE eX11ClientError = Qnil;

VALUE X11Client_open_display(VALUE self) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  if(client->display) { 
    rb_raise(eX11ClientError, "Display already opened");
  }

  client->display = XOpenDisplay(RSTRING_PTR(rb_iv_get(self, "@display")));
  if( client->display == NULL ) {
    rb_raise(eX11ClientError, "Can't open display");
  }

  return self;
}

VALUE X11Client_close_display(VALUE self) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  if(client->display == NULL) { 
    rb_raise(eX11ClientError, "Display already closed");
  }

  X11Client_free_display(client->display);
  return self;
}

VALUE X11Client_sync(VALUE self) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  XSync(client->display, False);
  return self;
}
