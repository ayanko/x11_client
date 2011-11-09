require "spec_helper"

describe X11Client do
  let(:client) { described_class.new(ENV['DISPLAY']) }

  let(:root_window_id) { `xwininfo -root -int | grep "Window id:"`.scan(/\d+/).first.to_i }

  let(:root_window_children_ids) do
    ids = []
    `xwininfo -root -int -children`.split("\n").each do |line|
      next if line =~ /\d+\s+children:/
      line =~ /^\s*(\d+)/ and  ids.push($1.to_i)
    end
    ids
  end

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

  describe "#window_children" do
    it "should return empty array if window does not exists" do
      client.window_children(0).should == []
    end

    it "should return root window children array for roor window" do
      root_window_children_ids.should_not be_empty
      children = client.window_children(root_window_id)

      children.should be_kind_of(Array)
      children.map { |child| child['id'] }.sort.should == root_window_children_ids.sort
    end
  end
end
