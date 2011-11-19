#include "x11_client.h"
#include "x11_client_keyboard.h"

#include <X11/keysymdef.h>
#include <X11/extensions/XTest.h>

/*
 * Perform key action action (up or down)
 * @param [String] keyname a X11 keyname e.g. XK_space 
 * @param [Boolen] action either true (down) or false (up)
 * @raise ArgumentError 
 */
VALUE X11Client_keyaction(VALUE self, VALUE keysym, VALUE action) {
  X11Client *client;
  KeyCode keycode;
  Bool is_press;

  Data_Get_Struct(self, X11Client, client);

  Check_Type(keysym, T_FIXNUM);

  //keysym = XStringToKeysym(RSTRING_PTR(keyname));
  //if ( keysym == NoSymbol )
  //  rb_raise(rb_eArgError, "Can't convert %s to keysym", RSTRING_PTR(keyname));

  keycode = XKeysymToKeycode(client->display, FIX2INT(keysym));
  if (keycode == 0)
    rb_raise(rb_eArgError, "Can't convert %s to keycode", FIX2INT(keysym));

  is_press = action == Qtrue ? True : False;
  XTestFakeKeyEvent(client->display, keycode, is_press, CurrentTime);

  return self;
}

