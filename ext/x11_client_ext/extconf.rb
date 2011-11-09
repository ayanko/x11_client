require 'mkmf'

$CFLAGS << ' -Wall '

$LDFLAGS << ' ' << `pkg-config --libs x11 xtst xext`

create_makefile 'x11_client_ext'
