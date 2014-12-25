require 'optparse'

options = {}
OptionParser.new do |opts|
  opts.banner = "Usage: example.rb [options]"

  opts.on("-v", "--[no-]verbose", "Run verbosely") do |v|
    options[:verbose] = v
  end 
  opts.on("-l", "--lelp","Help command line") do |v|
    options[:help]=v
  end
end.parse!

p options
p ARGV
