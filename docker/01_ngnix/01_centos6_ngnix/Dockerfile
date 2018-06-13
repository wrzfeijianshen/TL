# This is wrzfeijianshen First Dockerfile
# Version 1.0
# Author: wrzfeijianshen wrzfeijianshen@126.com

# Base images 基础镜像
FROM centos:6

# MAINTAINER 维护者信息
MAINTAINER wrzfeijianshen

ENV NGINX_VERSION 1.15.0
ENV PCRE_VERSION=8.42
ENV BUILD_ROOT /usr/local/src/

RUN	yum -y install curl \
	&& mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo.backup \
	#&& mv /etc/yum.repos.d/epel.repo /etc/yum.repos.d/epel.repo.backup \
	&& curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-6.repo \ 
	&& curl -o /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-6.repo \
	&& yum clean all \
	&& yum makecache
	
RUN yum install -y wget gcc gcc-c++ make openssl-devel

RUN useradd -s /sbin/nologin -M www

RUN mkdir -p $BUILD_ROOT \ 
	&& curl -o $BUILD_ROOT/nginx-$NGINX_VERSION.tar.gz https://nginx.org/download/nginx-$NGINX_VERSION.tar.gz \
	&& curl -o $BUILD_ROOT/pcre-$PCRE_VERSION.tar.gz https://ftp.pcre.org/pub/pcre/pcre-$PCRE_VERSION.tar.gz\
	
RUN cd $BUILD_ROOT \
	&& tar vxzf nginx-$NGINX_VERSION.tar.gz \
	&& tar vxzf pcre-$PCRE_VERSION.tar.gz \
	
#WORKDIR
WORKDIR /usr/local/src/nginx-$NGINX_VERSION
RUN ./configure --prefix=/usr/local/nginx \
	--user=www --group=www \
	--with-http_ssl_module \
	--with-http_stub_status_module \
	--with-pcre=/usr/local/src/pcre-$PCRE_VERSION \
	&& make && make install

RUN echo "daemon off;" >> /usr/local/nginx/conf/nginx.conf

ENV PATH /usr/local/nginx/sbin:$PATH
EXPOSE 80

CMD ["nginx"]