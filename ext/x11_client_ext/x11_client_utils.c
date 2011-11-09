#include "x11_client_utils.h"

void X11Client_free_display(Display *display) {
  if(display) {
    XCloseDisplay(display);
  }
}
