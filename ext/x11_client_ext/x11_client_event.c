#include "x11_client.h"
#include "x11_client_event.h"

VALUE X11Client_start(VALUE self) {
  X11Client *client;
  VALUE event;
  XEvent any_event;

  rb_need_block();

  Data_Get_Struct(self, X11Client, client);
  client->loop = True;

  XSelectInput(client->display, DefaultRootWindow(client->display), SubstructureNotifyMask);

  while ( client->loop ) {
    XNextEvent(client->display, &any_event);

    event = X11Client_get_event(any_event);

    if(event && event != Qnil) {
      rb_yield(event);
    }
  }
  return Qnil;
}

VALUE X11Client_stop(VALUE self) {
  X11Client *client;
  Data_Get_Struct(self, X11Client, client);

  XSelectInput(client->display, DefaultRootWindow(client->display), 0);
  client->loop = False;
  return Qnil;
}

VALUE X11Client_get_event(XEvent any_event) {
  XCreateWindowEvent *create_event;
  XDestroyWindowEvent *destroy_event;
  XMapEvent *map_event;
  XUnmapEvent *unmap_event;
  XVisibilityEvent *visibility_event;
  VALUE result = Qnil;

  switch(any_event.type) {

    case CreateNotify:
      ;
      create_event = (XCreateWindowEvent *)&any_event;

      result = rb_hash_new();
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("type"), rb_str_new2("CreateWindowEvent"));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("window_id"), LONG2FIX(create_event->window) );
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("parent_id"), LONG2FIX(create_event->parent));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("x"), INT2FIX(create_event->x));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("y"), INT2FIX(create_event->y));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("width"), INT2FIX(create_event->width));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("height"), INT2FIX(create_event->height));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("border_width"), INT2FIX(create_event->border_width));
      break;

    case DestroyNotify:
      ;
      destroy_event = (XDestroyWindowEvent *)&any_event;

      result = rb_hash_new();
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("type"), rb_str_new2("DestroyWindowEvent"));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("window_id"), LONG2FIX(destroy_event->window) );
      break;

    case MapNotify:
      ;
      map_event = (XMapEvent *)&any_event;

      result = rb_hash_new();
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("type"), rb_str_new2("MapEvent"));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("window_id"), LONG2FIX(map_event->window) );
      break;

    case UnmapNotify:
      ;
      unmap_event = (XUnmapEvent *)&any_event;

      result = rb_hash_new();
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("type"), rb_str_new2("UnmapEvent"));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("window_id"), LONG2FIX(unmap_event->window) );
      break;

    case VisibilityNotify:
      ;
      visibility_event = (XVisibilityEvent *)&any_event;

      result = rb_hash_new();
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("type"), rb_str_new2("VisibilityEvent"));
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("window_id"), LONG2FIX(visibility_event->window) );
      rb_funcall(result, rb_intern("[]="), 2, rb_str_new2("state"), X11Client_visibility_event_state(visibility_event));
      break;

    default:
      result = Qnil;

  }
  return result;
}

VALUE X11Client_visibility_event_state(XVisibilityEvent *event) {
  VALUE result;

  switch(event->state) {
    case VisibilityUnobscured:
      rb_str_new2("unobscured");
      break;
    case VisibilityPartiallyObscured:
      rb_str_new2("partially_obscured");
      break;
    case VisibilityFullyObscured:
      rb_str_new2("fully_unobscured");
      break;
    default:
      result = Qnil;
  }

  return result;
}

