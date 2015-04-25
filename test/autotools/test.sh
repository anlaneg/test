#! /bin/bash

rm -rf autom4te.cache autoscan.log config.status configure configure.ac configure.scan config.h.in config.log
autoscan
cp bak_configure configure.ac
aclocal
autoheader
exit 1
autoconf
automake 
