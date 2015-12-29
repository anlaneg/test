
drop procedure if exists select_all_login;
DELIMITER //
create procedure select_all_login(in username varchar(64))
begin
    select * from login where username = username;
end;
// 

