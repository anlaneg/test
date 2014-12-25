#
class Point
	def initialize(name)
   		@name = name;
		@line = [];
	end
	
	def point_to(other_point)
		@line.push(other_point.get_name());
		other_point.get_line().push(@name);
	end

	def to_s()
		@line.each do |i|
			puts "#{@name}->#{i}";
		end
	end

	def get_name()
	return @name;
	end

	def get_line()
	return @line;
	end
end

a = Point.new("A");
b = Point.new("B");
c = Point.new("C");

a.point_to(b);
b.point_to(c);
c.point_to(a);

a.to_s 
b.to_s
c.to_s
