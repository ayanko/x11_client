## X11Client

X11Client is C extension that manages X11 windows/events.

It can be handy if you want to controll some programs running in Xvfb.

## Dependencies

* Xlib
* Xtst
* Xext

## Installation

    gem install x11_client

## API

* X11Client.new(display) - create new client for given display
* X11Client#open_display - explicit open display
* X11Client#close_display - explicit close display
* X11Client#sync - sync display
* X11Client#start(&block) - block execution and yield event attributes for each new event.
* X11Client#stop - stop blocking loop
* X11Client#root_window_id - returns root window id in decimal.
* X11Client#get_window(window_id) - returns window attributes hash or nil for given window_id.
* X11Client#mousemove(x,y) - move mouse pointer to (x,y) coordinates.
* X11Client#mousedown(button) - down mouse buton
* X11Client#mouseup(buton) - up mouse button
* X11Client#mouseclick(button) - mousedown and mouseup

## Mouse buttons

* 1 - left
* 2 - right
* 3 - middle
* 4 - wheel up
* 5 - wheel down

## X11 Window attributes

* id - window id
* root_id - root window id 
* x - X coordinate
* y - Y coordinate
* width - window width
* height - window height
* border_width - window border width
* state - window state
 * shown
 * hidden
 * unmapped

## X11 Event attributes

Supported events:

* CreateWindowEvent
* DestroyWindowEvent
* MapEvent
* UnmapEvent
* VisibilityEvent

### CreateWindowEvent attributes:

* type
* window_id
* parent_id
* x
* y
* width
* height
* border_width

### DestroyWindowEvent attributes:

* type
* window_id

### MapEvent attributes:

* type
* window_id

### UnmapEvent attributes:

* type
* window_id

### VisibilityEvent attributes:

* type
* window_id
* state:
 * unobscured
 * partially_obscured
 * fully_unobscured 

## Example

    client = X11Client.new(":0")

    client.start do |event|

      case event['type']
      when 'CreateWindowEvent'
        window = client.get_window(event["window_id"])
        next unless window

        case window['class']
        when /skype/i
          case window['name']
          when /End User License Agreement/i
            # Accept Skype Aggreement
            client.mousemove(window['x'] + 500, window['y'] + 340)
            client.sync
            sleep(1)
            client.mouseclick(1)
            client.stop
          end
        end

      end

    end

## Testing

    $ sudo pacman -S xorg-xwininfo
    $ bundle install
    $ bundle exec rspec spec

## References

* [The Xlib Programming Manual](http://tronche.com/gui/x/xlib/)
