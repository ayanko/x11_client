#ifndef X11_CLIENT_H
#define X11_CLIENT_H

#include "ruby.h"
#include <ruby18_compat.h>
#include <X11/Xlib.h>

typedef struct {
  Display *display;
  int loop;
} X11Client;

VALUE eX11ClientError;

VALUE cX11Client;

#endif
