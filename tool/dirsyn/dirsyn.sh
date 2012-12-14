#! /bin/bash

#此文件用于实现目录同步
#当多个存储设备连接至运行设备时
#运行设备主动检查存储设备的某个已配置目录
#如果已配置目录中存在运行设备不存在的文件
#则将直接同步此文件至运行设备
#形式化语言说明功能如下:
# if [ ! -e file ] ; cp file to here

awk -f dirsyn.awk dirsyn.config
