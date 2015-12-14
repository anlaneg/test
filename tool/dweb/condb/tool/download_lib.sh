#! /bin/bash
if [ ! -e "./commons-beanutils-1.9.1-bin.zip" ];
then
    wget -c http://archive.apache.org/dist/commons/beanutils/binaries/commons-beanutils-1.9.1-bin.zip
fi;

if [ ! -e "commons-logging-1.2-bin.zip" ];
then
    wget -c http://mirrors.cnnic.cn/apache//commons/logging/binaries/commons-logging-1.2-bin.zip
fi;

if [ ! -e "mysql-connector-java-5.1.38.zip" ];
then
    wget -c http://cdn.mysql.com/Downloads/Connector-J/mysql-connector-java-5.1.38.zip
fi;

unzip -o -j ./commons-beanutils-1.9.1-bin.zip commons-beanutils-1.9.1/commons-beanutils-1.9.1.jar -d ./lib
unzip -o -j ./commons-logging-1.2-bin.zip     commons-logging-1.2/commons-logging-1.2.jar         -d ./lib
unzip -o -j ./mysql-connector-java-5.1.38.zip mysql-connector-java-5.1.38/mysql-connector-java-5.1.38-bin.jar -d ./lib

