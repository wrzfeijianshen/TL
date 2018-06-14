# This is wrzfeijianshen First Dockerfile
# Version 1.0
# Author: wrzfeijianshen wrzfeijianshen@126.com

# Base images 基础镜像
FROM centos:6

# MAINTAINER 维护者信息
MAINTAINER wrzfeijianshen

RUN	mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo.backup
	
ADD Centos-6.repo /etc/yum.repos.d/CentOS-Base.repo
ADD epel-6.repo /etc/yum.repos.d/epel.repo

RUN yum clean all &&  yum makecache
RUN yum install -y wget gcc gcc-c++ make openssl-devel
RUN yum install -y mysql-server mysql 

# 安装完成以后，执行以下命令。配置用户名密码相关信息；
RUN /etc/init.d/mysqld start \  
    && mysql -e "grant all privileges on *.* to 'root'@'%' identified by '123456' WITH GRANT OPTION ;"\  
    && mysql -e "grant all privileges on *.* to 'root'@'localhost' identified by '123456' WITH GRANT OPTION ;"\ 
    && mysql -u root -p123456 -e "show databases;"  

ENV PATH /usr/bin/:$PATH

# 镜像暴露3306端口；
EXPOSE 3306

CMD ["mysqld_safe"]