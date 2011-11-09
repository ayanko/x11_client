// returns root window id
VALUE X11Client_root_window_id(VALUE self);

// returns window attributes for specified window id
VALUE X11Client_get_window(VALUE self, VALUE window_id);

// return children window ids for specified window id
VALUE X11Client_window_children_ids(VALUE self, VALUE window_id);

// get window state
VALUE X11Client_window_state(XWindowAttributes attributes);

// get window name for given window id
VALUE X11Client_get_window_name(VALUE self, VALUE window_id);

// handler that ignores BadWindow error
int X11Client_IgnoreBadWindowHandler(Display *display, XErrorEvent *error);
