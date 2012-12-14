	awk '{
	printf ("curl http://dict.baidu.com/s?wd=%s  -s |  grep \"</b><a href=\\\"#\\\" url=\\\"http://bs.baidu.com/handian\" | awk -F\"b>\" '\''{ printf(\"%%s\",$2);}'\''  \n",$0) ;
	}'   word

