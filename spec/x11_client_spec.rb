require "spec_helper"

describe X11Client do
  let(:client) { described_class.new(ENV['DISPLAY']) }

  let(:root_window_id) { `xwininfo -root -int | grep "Window id:"`.scan(/\d+/).first.to_i }

  describe "#root_window_id" do
    it "should be root window integer" do
      root_window_id.should_not be_zero
      client.root_window_id.should == root_window_id
    end
  end

  describe "#root_window" do
    it "should return hash of root window attributes" do
      window = client.root_window
      window.should be_kind_of(Hash)
      window['id'].should == root_window_id
      window['root_id'].should == root_window_id
      window['x'].should == 0
      window['y'].should == 0
    end
  end
end
