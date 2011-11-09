#include "ruby.h"

VALUE X11Client_initialize(VALUE self, VALUE display);
VALUE X11Client_alloc(VALUE klass);
void X11Client_free(X11Client *client);

