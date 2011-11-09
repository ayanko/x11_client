#ifndef X11_CLIENT_H
#define X11_CLIENT_H

#include "ruby.h"
#include <X11/Xlib.h>

typedef struct {
  Display *display;
  int loop;
} X11Client;

#endif
