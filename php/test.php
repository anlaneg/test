<?php 

$color=" p";
$x = 3 ;
$y = 6 ;
$z = $x + $y ;

if($z > 3)
{
	echo " $z " ;
}

class A
{
	var $a;
	var $b;
	var $c;
	function A($a,$b,$c="hello world")
	{
		$this->a = $a;
		$this->b = $b;
		$this->c = $c;
	}

	function echo1()
	{
		echo "{$this->a} {$this->b} {$this->c}";
	}
}

  $a = new A("along","bnf");
 echo "hello world {$color} {$z} " . $a->echo1() ?><br/>

