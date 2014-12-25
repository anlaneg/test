#! /bin/ruby

number=0
File.open("/home/along/test.rb").each { |line| number=number+1}
puts("共计#{number}行\n")

