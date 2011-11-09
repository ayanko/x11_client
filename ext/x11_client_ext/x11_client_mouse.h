#include "ruby.h"

VALUE X11Client_mousemove(VALUE self, VALUE x, VALUE y);
VALUE X11Client_mousedown(VALUE self, VALUE button);
VALUE X11Client_mouseup(VALUE self, VALUE button);
VALUE X11Client_mouseclick(VALUE self, VALUE button);
