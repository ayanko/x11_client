require "x11_client_ext"

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
end
