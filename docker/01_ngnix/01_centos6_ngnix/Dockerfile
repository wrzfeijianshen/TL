FROM centos:6
MAINTAINER wrzfeijianshen@126.com

ENV NGINX_VERSION 1.15.0
ENV OPENSSL_VERSION 1.0.2k
ENV PCRE_VERSION 8.40
ENV ZLIB_VERSION 1.2.11
ENV BUILD_ROOT /usr/local/src/nginx

RUN	yum -y install curl \
	&& mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo.backup \
	#&& mv /etc/yum.repos.d/epel.repo /etc/yum.repos.d/epel.repo.backup \
	&& curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-6.repo \ 
	&& curl -o /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-6.repo \
	&& yum clean all \
	&& yum makecache
	
RUN yum install -y gcc gcc-c++ wget make  perl openssl-devel pcre-devel zlib zlib-devel

RUN mkdir -p $BUILD_ROOT \ 
	&& curl -o $BUILD_ROOT/nginx-$NGINX_VERSION.tar.gz https://nginx.org/download/nginx-$NGINX_VERSION.tar.gz \
	&& ls
RUN cd $BUILD_ROOT \
	&& ls \
	&& tar vxzf nginx-$NGINX_VERSION.tar.gz \
	&& cd nginx-$NGINX_VERSION \
	&& BUILD_CONFIG=" \
	&& ./configure --prefix=/usr/local/nginx \
	&& make  \
	&& make install
RUN yum -y remove gcc gcc-c++ make perl\
	&& yum clean all
	
	
WORKDIR /usr/local/nginx
EXPOSE 80 443
CMD ["nginx", "-g", "daemon off;"]