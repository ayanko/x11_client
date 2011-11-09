// returns root window id
VALUE X11Client_root_window_id(VALUE self);

// returns window attributes for specified window id
VALUE X11Client_get_window(VALUE self, VALUE window_id);

//VALUE X11Client_window_children_ids(VALUE self, VALUE window);

// get window state
VALUE X11Client_window_state(XWindowAttributes attributes);

// handler that ignores BadWindow error
int X11Client_IgnoreBadWindowHandler(Display *display, XErrorEvent *error);
