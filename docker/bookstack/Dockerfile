# This is wrzfeijianshen First Dockerfile
# Version 1.0
# Author: wrzfeijianshen wrzfeijianshen@126.com

# Base images 基础镜像
FROM ubuntu:18.04
# MAINTAINER 维护者信息
MAINTAINER wrzfeijianshen

ENV BUILD_ROOT /usr/local/src/
RUN cp /etc/apt/sources.list /etc/apt/sources.list.bak \
    && sed -i "s/archive\.ubuntu\.com/mirrors\.163\.com/g" /etc/apt/sources.list \
    && apt-get update 
RUN apt-get -y install wget 
RUN mkdir -p $BUILD_ROOT \
    && cd $BUILD_ROOT \
	&& wget -O install.sh http://download.bt.cn/install/install-ubuntu.sh && bash install.sh
# 镜像暴露8888端口；
EXPOSE 8888