#! /bin/bash

username=root
password=root
database_name=along

echo "import sql"
mysql -u $username -p$password -D $database_name< ./db/proc.sql
