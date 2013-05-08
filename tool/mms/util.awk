#! /usr/bin/awk -f

BEGIN {
  split_char="<<-->>";
  mms_start_char="mms://";
  rtsp_start_char="rtsp://";
  url_char="[0-9a-zA-Z:/_~\.]+"
}

function parser_url_comment(line,regex)
{
	match_ret=match(line,regex);
	if(match_ret <=0)
	{
		printf("error(%d):no find%s line=\"%s\"\n",NR,regex,line);
	}

	url=substr(line,match_ret,RLENGTH+match_ret-1);
	comment=substr(line,0,match_ret-1) "" substr(line,match_ret + RLENGTH)
	#printf("\"%s\"%s\"%s\"\n",url,split_char,comment);
	#printf("%s\n",comment);
	printf("%s\n",url);
}


{
	mms_start=index($0,mms_start_char);
	rtsp_start = index($0,rtsp_start_char);
	if(mms_start > 0)
	{
		if(rtsp_start > 0)
		{
			printf("warning(%d):line=\"%s\"\n",NR,$0);
		}
		parser_url_comment($0,"(" mms_start_char "" url_char ")");
	}
	
	if(rtsp_start > 0)
	{
		if(mms_start > 0)
		{
			printf("warning(%d):line=\"%s\"\n",NR,$0);
		}
		parser_url_comment($0,"(" rtsp_start_char "" url_char ")");
	}
}
