#! /bin/bash


#HOME_URL='http://www.fang99.com/buycenter/buildingsearch.aspx?isGjss=1&Zone=&Trade=';
HOME_URL='http://www.fang99.com/buycenter/buildingsearch.aspx?isGjss=1&Zone=&Trade=&page='

source ./content

function do_main()
{
for((i = 1; i <= 49 ; ++i))
do

helper_get_page_content "$HOME_URL$i" | grep "<div style=\"text-align:center;padding:3px;\">" | sed 's.</\?tr>.\n.g;s.</td>.\n.g;s.<td>.\n<td>.g;' | grep "<td "  | awk -F'>' -f index.awk  >>result.txt

done;
}

HOME_INFO_URL='http://www.fang99.com/buycenter/buildInfo.aspx?BuildingId=0000005884'
helper_get_page_content "$HOME_INFO_URL" >an.txt # | awk '{ str="" ; if(index($0,"<table")) { str=str+$0 ; readline ; while(index($0,"<\table>") < 0) {str=str+$0 ;  readline; } printf("%s",str); } }'
