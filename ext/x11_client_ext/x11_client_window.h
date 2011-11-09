VALUE X11Client_get_window(VALUE self, VALUE window_id);
VALUE X11Client_window_state(XWindowAttributes attributes);
int X11Client_IgnoreBadWindowHandler(Display *display, XErrorEvent *error);
