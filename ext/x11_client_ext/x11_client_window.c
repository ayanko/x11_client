#include "x11_client.h"

#include "x11_client_window.h"

#include "X11/Xutil.h"

VALUE X11Client_root_window_id(VALUE self) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  return LONG2FIX(DefaultRootWindow(client->display));
}

VALUE X11Client_get_window(VALUE self, VALUE window_id) {
  VALUE result = Qnil;

  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  Window window = NUM2LONG(window_id);
  char* window_name = '\0';
  XWindowAttributes attributes;
  XClassHint classhint;
  
  XSetErrorHandler(X11Client_IgnoreBadWindowHandler);

  if(XGetWindowAttributes(client->display, window, &attributes)) {
    result = rb_hash_new();
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("id"), LONG2FIX(window));
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("x"), INT2FIX(attributes.x));
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("y"), INT2FIX(attributes.y));
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("width"), INT2FIX(attributes.width));
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("height"), INT2FIX(attributes.height));
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("border_width"), INT2FIX(attributes.border_width));
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("root_id"), LONG2FIX(attributes.root));
    rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("state"), X11Client_window_state(attributes));

    if (XFetchName(client->display, window, &window_name)) {
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("name"), rb_str_new2(window_name));
      XFree(window_name);
    }

    if (XGetClassHint(client->display, window, &classhint)) {
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("class"), rb_str_new2(classhint.res_class));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("class_name"), rb_str_new2(classhint.res_name));
      XFree(classhint.res_name);
      XFree(classhint.res_class);
    }
  }

  XSetErrorHandler(NULL);

  return result;
}

VALUE X11Client_window_children_ids(VALUE self, VALUE window_id) {
  Window window = NUM2LONG(window_id);
  Window dummy;
  Window *children;
  unsigned int i, nchildren;

  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  XSetErrorHandler(X11Client_IgnoreBadWindowHandler);

  VALUE children_ids = rb_ary_new();
  if (XQueryTree(client->display, window, &dummy, &dummy, &children, &nchildren)) {
    for (i = 0; i < nchildren; i++) {
      Window child_id = children[i];
      rb_funcall(children_ids, rb_intern("push"), 1, LONG2FIX(child_id));
    }
  }

  XSetErrorHandler(NULL);
  return children_ids;
}

VALUE X11Client_window_state(XWindowAttributes attributes) {
  VALUE state = Qnil;
  switch(attributes.map_state) {
    case IsViewable:
      state = rb_str_new2("shown");
      break;
    case IsUnviewable:
      state = rb_str_new2("hidden");
      break;
    case IsUnmapped:
      state = rb_str_new2("unmapped");
      break;
  }

  return state;
}

int X11Client_IgnoreBadWindowHandler(Display *display, XErrorEvent *error) {
  if (error->request_code != BadWindow) {
    XSetErrorHandler(NULL);
  }
  return 1;
}
