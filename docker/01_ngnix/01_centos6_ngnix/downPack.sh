#!/bin/sh
NGINX_VERSION=1.0.2
PCRE_VERSION=8.42
ZLIB_VERSION=1.2.11

curl -o ./Centos-6.repo http://mirrors.aliyun.com/repo/Centos-6.repo 
curl -o ./epel-6.repo http://mirrors.aliyun.com/repo/epel-6.repo 
curl -o ./openssl-$OPENSSL_VERSION.tar.gz https://www.openssl.org/source/openssl-$OPENSSL_VERSION.tar.gz 
curl -o ./nginx-$NGINX_VERSION.tar.gz https://nginx.org/download/nginx-$NGINX_VERSION.tar.gz 
curl -o ./pcre-$PCRE_VERSION.tar.gz https://ftp.pcre.org/pub/pcre/pcre-$PCRE_VERSION.tar.gz

#curl -o $BUILD_ROOT/zlib-$ZLIB_VERSION.tar.gz https://www.zlib.net/zlib-$ZLIB_VERSION.tar.gz
#curl -o $BUILD_ROOT/zlib-$ZLIB_VERSION.tar.gz https://www.zlib.net/zlib-$ZLIB_VERSION.tar.gz
#wget -O $BUILD_ROOT/zlib-$ZLIB_VERSION.tar.gz https://www.zlib.net/zlib-$ZLIB_VERSION.tar.gz

#curl -o $BUILD_ROOT/pcre-$PCRE_VERSION.zip https://ftp.pcre.org/pub/pcre/pcre-$PCRE_VERSION.zip