#! /bin/bash

FILE=www.csdn.net.sql

{
  read line1;
  read line2;
}<${FILE}


echo $line1;
echo $line2;
