FROM centos:6
MAINTAINER wrzfeijianshen@126.com

mkdir -p $BUILD_ROOT \
ADD aliyun-mirror.repo /etc/yum.repos.d/CentOS-Base.repo
ADD aliyun-epel.repo /etc/yum.repos.d/epel.repo

RUN yum makecache \
	&& yum makecache \
	&& yum install -y gcc gcc-c++ make openssl-devel pcre-devel \
	&& mkdir -p $BUILD_ROOT \