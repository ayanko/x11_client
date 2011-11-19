require "x11_client_ext"
require "x11_client/keysym"

class X11Client
  def window_children(window_id)
    window_children_ids(window_id).map do |child_id|
      get_window(child_id)
    end.compact
  end

  def window_descendants(window_id)
    windows = []
    ids = [window_id]
    until ids.empty?
      window = get_window(ids.shift)
      windows << window
      ids += window_children_ids(window['id'])
    end
    windows
  end

  def root_window
    get_window(root_window_id)
  end

  def root_window_children
    window_children(root_window_id)
  end

  def root_window_descendants
    window_descendants(root_window_id)
  end

  # Convert X11 key name to symbol (integer)
  def key2sym(key)
    KEYSYM[key] or raise ArgumentError, "Can't convert #{key} key to X11 sym"
  end

  # Press a key
  # @param [String] name a key name
  def keypdown(name)
    keyaction(key2sym(name), true)
  end

  # Release a key
  # @param [String] name a key name
  def keyup(name)
    keyaction(key2sym(name), false)
  end

  # Press and release a key
  # @param [String] name a key name
  # @param [Float] time sleep time in seconds between actions
  def key(name, time = 0.01)
    keypdown(name)
    sleep(time)
    keyup(name)
    self
  end

  # Type a word
  # @param [SString] word a string of ASCII characters without spaces etc...
  def type_word(word)
    word.each_char do |char|
      key("XK_#{char}")
    end
    self
  end
end
