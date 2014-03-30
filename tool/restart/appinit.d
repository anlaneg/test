#! /usr/bin/awk -f
/\^\s+[/ {
 start_idx = index($0,'[');
 end_idx = index($0,']');
 if(end_idx <= 0 || start_idx < 0 || end_idx <= start_idx)
 {
 }
 appname=index($0,'['),;
}

{
}

END{
}
