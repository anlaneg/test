eval_string="
class Persion
   def initialize(name)
     puts \"initialize name \", name;
   end
end

along = Persion.new(\"along\");
"

eval eval_string
