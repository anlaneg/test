

BEGIN{
 printf("start");
}
{
	find_str="id=\"lbl_"
	begin=index($0,find_str);
}
END{
}
