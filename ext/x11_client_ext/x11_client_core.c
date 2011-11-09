#include "x11_client.h"
#include "x11_client_utils.h"
#include "x11_client_core.h"

VALUE X11Client_initialize(VALUE self, VALUE display) {
  Check_Type(display, T_STRING);
  rb_iv_set(self, "@display", display);
  rb_funcall(self, rb_intern("open_display"), 0, 0);
  return self;
}

VALUE X11Client_alloc(VALUE klass) {
  VALUE obj;
  X11Client *client = ALLOC_N(X11Client, 1);
  client->display = NULL;

  obj = Data_Wrap_Struct(klass, 0, X11Client_free, client); 
  return obj;
}

void X11Client_free(X11Client *client) {
  X11Client_free_display(client->display);
  free(client);
}
