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
	#&& curl -o /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-6.repo \
	&& yum clean all \
	&& yum makecache \
	
RUN yum install -y gcc gcc-c++ make  perl zip unzip openssl-devel pcre-devel\
	&& mkdir -p $BUILD_ROOT \
	&& cd $BUILD_ROOT \
	&& curl https://ftp.pcre.org/pub/pcre/pcre-$PCRE_VERSION.zip -o $BUILD_ROOT/pcre-$PCRE_VERSION.zip \
	&& curl https://www.openssl.org/source/openssl-$OPENSSL_VERSION.tar.gz -o $BUILD_ROOT/openssl-$OPENSSL_VERSION.tar.gz \
	&& curl http://www.zlib.net/zlib-$ZLIB_VERSION.tar.gz -o $BUILD_ROOT/zlib-$ZLIB_VERSION.tar.gz \
	&& curl https://nginx.org/download/nginx-$NGINX_VERSION.tar.gz -o $BUILD_ROOT/nginx-$NGINX_VERSION.tar.gz \
	&& tar vxzf nginx-$NGINX_VERSION.tar.gz \
	&& unzip pcre-$PCRE_VERSION.zip \
	&& tar vxfz zlib-$ZLIB_VERSION.tar.gz \
	&& tar vxfz openssl-$OPENSSL_VERSION.tar.gz \
	&& cd nginx-$NGINX_VERSION \
	&& BUILD_CONFIG="\
		--prefix=/usr/local/nginx \
		--sbin-path=/usr/sbin/nginx \
		--conf-path=/etc/nginx/nginx.conf \
		--error-log-path=/var/log/nginx/error.log \
		--http-log-path=/var/log/nginx/access.log \
		--pid-path=/var/run/nginx.pid \
		--lock-path=/var/run/nginx.lock \
		--http-client-body-temp-path=/var/cache/nginx/client_temp \
		--http-proxy-temp-path=/var/cache/nginx/proxy_temp \
		--http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp \
		--http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp \
		--http-scgi-temp-path=/var/cache/nginx/scgi_temp \
		--with-openssl=$BUILD_ROOT/openssl-$OPENSSL_VERSION \
		--with-pcre=$BUILD_ROOT/pcre-$PCRE_VERSION \
		--with-zlib=$BUILD_ROOT/zlib-$ZLIB_VERSION \
		--with-http_ssl_module \
		--with-http_v2_module \ 
		--with-threads \
		" \
	&& mkdir -p /var/cache/nginx \
	&& ./configure $BUILD_CONFIG \
	&& make && make install \
	&& rm -rf $BUILD_ROOT \
	&& yum -y remove gcc gcc-c++ make perl zip unzip \
	&& yum clean all
	
WORKDIR /usr/local/nginx
EXPOSE 80 443
CMD ["nginx", "-g", "daemon off;"]