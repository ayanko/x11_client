#include "ruby.h"
#include "X11/Xlib.h"

VALUE X11Client_start(VALUE self);
VALUE X11Client_stop(VALUE self);
VALUE X11Client_get_event(XEvent any_event);
VALUE X11Client_visibility_event_state(XVisibilityEvent *event);
