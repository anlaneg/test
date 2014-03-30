#! /bin/bash

for((i=1;i<8;++i)) 
do 
	./cache_size_g > g.$i.txt ; 
	sleep 20; 
	./cache_size_O1 > O1.$i.txt ; 
	sleep 20;
	 ./cache_size_O2 > O2.$i.txt ;
	 sleep 20 ; 
	./cache_size_O3 > O3.$i.txt ; 
	sleep 20; 
done
