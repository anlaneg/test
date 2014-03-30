class Person

def initialize(name,age)
	@name=name;
	@age=age;
end

def to_s()
     to_string();
end

private

def to_string()
	return "{#{@name},#{@age}}";
end
end

along = Person.new("along",23)
puts along.to_s();
puts along.methods.join(' ')

