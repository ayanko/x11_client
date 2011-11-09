require "x11_client_ext"

class X11Client

  def root_window
    get_window(root_window_id)
  end

end
