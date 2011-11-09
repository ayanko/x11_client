require "spec_helper"

describe X11Client, "#root_window_id" do
  let(:client) { described_class.new(ENV['DISPLAY']) }

  it "should be root window integer" do
    root_window_id = `xwininfo -root -int | grep "Window id:"`.scan(/\d+/).first.to_i
    root_window_id.should_not be_zero
    client.root_window_id.should == root_window_id
  end
end
