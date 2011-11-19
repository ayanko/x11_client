$:.unshift File.expand_path("../../lib")

require "x11_client"

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
        # Accept Skype Agreement
        client.mousemove(window['x'] + 500, window['y'] + 340)
        client.sync
        sleep(1)
        client.mouseclick(1)
        client.stop
      end
    end

  end

end
