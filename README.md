<h1>WebServer based on Boost asio</h1>


[English version](https://github.com/Iridesscent/web-server/blob/master/README_en.md)

基于Boost Asio的多线程Web服务器。   

1.  服务器由Web服务模块，日志模块，Cache模块，XML配置模块构成。
2.  支持HTTP，HTTPS协议。HTTPS协议用asio::ssl::context对象对socket数据流进行加密。
3.  支持静态HTML页面，GET/POST方法，可以方便的进行横向扩展以支持新的请求方法。
4.  日志系统支持日志轮转，设置最大日志占用空间，定时轮转，过滤器等功能。
5.  缓存系统支持两种缓存，第一种是本服务器自带内存缓存，可以制定缓存大小，用LRU算法进行替换。第二种缓存是用Redis做页面缓存，需要在配置文件里完成Redis相应配置。换句话说，本数据库有三种缓存策略，无缓存，内存缓存和Redis缓存。在通常情况下，Redis缓存能获得更好的并发效率。

<h1>OS</h1>

建议ubuntu14及以上<br>

<h1>Complier</h1>

G++5及以上
<h1>Library dependencies</h1>   

以下库都在CMakeLists.txt中包含
> boost_system 
> ssl 
> crypto 
> pthread 
> boost_log 
> boost_thread 
> boost_log_setup 
> boost_regex

开发环境Boost版本为1.63.0
详情见[Boost 1_63_0官方文档](http://www.boost.org/doc/)

强烈建议在本机用相同的编译器编译本程序以及Boost库,防止链接动态库时出错。
<h1>Make</h1>

```
cd web-server
cmake CMakeLists.txt
make
```
  

<h1>Configurations</h1>   

所有的配置都要写在WebConfig.xml文件内，并放在和编译生成文件相同目录下。WebConfig.xml.sample是一份样例配置，请按文件里的注释进行配置。   
IP黑名单暂时只能配置，并不会生效，但是很快会在后续版本里支持。

<h1>Run</h1>

运行'web-server'文件来开始服务器。

./web-server 是服务器可执行文件。 ./web/是默认的web根目录(可以在WebConfig.xml中修改). 必需保证Web根目录下有index.html文件. 否则服务器将会返回一个404页面。

Run as a HTTP/HTTPS server:<br>
```
nohup ./web_server &
```
<h1>Load Test</h1>   
运行在Redis缓存模式下
服务器配置：阿里云双核Intel(R) Xeon(R) CPU E5-2682 v4 @ 2.50GHz 4G RAM   
模拟3000个用户对七个页面并发访问，每个用户每秒访问一个页面    
结果如下：   

![测试结果](http://iridescent.com.cn/Reference/LoadTest.png)   
服务器cpu负载一直在20左右
<h1>DEMO</h1>

[http://118.190.23.140:1234/index.html](http://118.190.23.140:1234/index.html)<br>

<h1>Contact me</h1>
392183501@outlook.com<br>
