# WebSocket以及wss #

转自：https://blog.csdn.net/qq_28804275/article/details/80891921

过去的这一个多月里，我的工（开）作（发）任务转战回了游戏。短短的一个月里，催着输出两款h5游戏，再加上对接、联调，想想真是够辛（ku）苦（bi）的。本人负责后端，也就是服务端这块的游戏主流程输出。去年下半年，在前任大佬的带领下，做过一两款棋牌类的手游，虽然目前的运营状况不太乐观。不过好在，过去学的那点皮毛也还没丢光，所以这次写h5后端总体还算顺畅。至于怎么用Java来写游戏，下来如果有时间会整理下这块的思路和知识。

## 关于WebSocket，维基百科是这样介绍的： ##

以前，很多网站为了实现实时推送技术，所用的技术都是轮询。轮询是在特定的时间间隔（如每1秒），由浏览器对服务器发出HTTP请求，然后由服务器返回最新的数据给客户端。这种传统的模式带来的缺点很明显，即浏览器需要不断的向服务器发出请求，然而HTTP请求包含较多的请求头信息，而其中真正有效的数据只是很小的一部分，显然这样会浪费很多的带宽等资源。在这种情况下，HTML5定义了WebSocket协议，能更好的节省服务器资源和带宽，并且能够更实时地进行通讯。
   WebSocket是一种在单个TCP连接上进行全双工通讯的协议，使得客户端和服务器之间的数据交换变得更加简单，允许服务端主动向客户端推送数据。在WebSocket API中，浏览器和服务器只需要完成一次握手，两者之间就可以创建持久性的连接，并进行双向数据传输。

WebSocket 协议在2008年诞生，2011年成为国际标准，现在几乎所有浏览器都已经支持了。它的最大特点就是，服务器可以主动向客户端推送信息，客户端也可以主动向服务器发送信息，是真正的双向平等对话，属于服务器推送技术的一种。

## WebSocket ##

  简单来说，WebSocket减少了客户端与服务器端建立连接的次数，减轻了服务器资源的开销，只需要完成一次HTTP握手。整个通讯过程是建立在一次连接/状态中，也就避免了HTTP的非状态性，服务端会一直与客户端保持连接，直到双方发起关闭请求，同时由原本的客户端主动询问，转换为服务器有信息的时候推送。所以，它能做实时通信（聊天室、直播间等），其他特点还包括：

**建立在 TCP 协议之上，服务器端的实现比较容易**
与 HTTP 协议有着良好的兼容性。默认端口也是80和443，并且握手阶段采用 HTTP 协议，因此握手时不容易屏蔽，能通过各种 HTTP 代理服务器
数据格式比较轻量，性能开销小，通信高效
可以发送文本，也可以发送二进制数据
没有同源限制，客户端可以与任意服务器通信
协议标识符是ws（如果加密，则为wss），服务器网址就是 URL


## HTTP、HTTPS、WS、WSS ##

  差点就跑题了。这不，由于业务需求，上头要求新出的h5游戏要配上Https。无奈，公司小，没有专业的运维人员，所以只能由我们这些开发“猿”顶上了，以为会很顺畅，但一连串的问题没想到也才刚刚开始。因此本文，就是用来记录这些踩过的“坑”，希望可以让后人少走点弯路。

**1.申领证书**

   公有云服务器上，一般大家都习惯使用Nginx来做反向代理。首先，配置Https，需要我们到专业的CA机构去申领证书，这个证书大多数情况下都是要钱的，但其实也有免费的（有效期1年），例如利用国内的阿里云或者腾讯云就可以很方便的申请这证书。

   - 阿里云 - Https证书申请
   - 腾讯云 - Https证书申请

阿里云Https证书申请

阿里云 - SSL证书申领

  PS： 通过阿里云申领免费版SSL证书有点套路，藏得有点深。点击以上链接进入后，如果在“证书类型”一栏中没找到“免费型DV SSL”，那么请依次点击第三栏的“选择品牌”中的“Symantec”，然后回到第一栏的“证书类型”，点击出现的第三个选项“增强型OV SSL”，之后就会在“证书类型”中出现我们需要的第二项：“免费型DV SSL”。

阿里云免费型SSL证书申领过程

腾讯云Https证书申请

腾讯云 - SSL证书申领

  确认申领、购买之后，下来还需要绑定我们的域名（注意：免费型的SSL证书一般仅支持绑定一个一级域名或者子域名，通配符的证书一般是需要花钱的），以及进行域名身份验证等操作。等这两步都完成之后，只需要等待CA机构扫描认证之后，我们就可以拿到真正的证书了。

**2.配置Https**

  下载好证书压缩包并解压之后，一般里面有IIS、Apache和Nginx三款主流服务器的ssl证书，这里我们也仅需要Nginx的证书。首先，将证书里Nginx文件夹下的1_{域名}bundle.crt 和2{域名}.key复制到我们服务器上的指定位置（假设在/root/ssl/下面）。基于Nginx的Https配置还是比较简单的，参考如下。

    server {
    
    #listen 80; #如果需要同时支持http和https
    
    listen 443 ssl http2;
    
    listen [::]:443 ssl http2;
    
    ssl_certificate "/root/ssl/1_{域名}_bundle.crt";
    
    ssl_certificate_key "/root/ssl/2_{域名}.key";
    
    ssl_session_cache shared:SSL:1m;
    
    ssl_session_timeout 10m;
    
    ssl_ciphers HIGH:!aNULL:!MD5;
    
    ssl_prefer_server_ciphers on;
    
     
    server_name {域名};
    
    location / {
    
    proxy_pass http://localhost:{代理端口};
    
    }
    
    }

附：下面是开启Nginx的Gzip压缩的配置，有需要的也可以参考。

    http {
    
    gzip on;
    
    gzip_disable "msie6";
    
    gzip_min_length 1k;
    
    gzip_vary on;
    
    gzip_proxied any;
    
    gzip_comp_level 6;
    
    gzip_buffers 16 8k;
    
    gzip_http_version 1.1;
    
    gzip_types application/font-woff text/plain application/javascript application/json text/css application/xml text/javascript image/jpg image/jpeg image/png image/gif image/x-icon;
    
     
    server {
    
    # 这里是server相关的配置
    
    }
    
    }


## 事故现场 ##
完成以上步骤后，按道理来说，h5游戏确实可以通过https的形式来打开了，简单测试后的确没啥问题，然后大家也就这样愉快的下班了。不过正如“墨菲定律”所说的：“凡事只要有可能出错，那就一定会出错”。果不其然，一段时间后，测试就在群里反馈，某段时间后h5游戏就无法加载正常进行下去了，一看时间，正是配完Https之后开始出现的问题。没办法，于是连忙打开电脑，开始排查解决问题，直觉告诉我要先打开浏览器的控制面板，果不其然，立刻发现了问题。

浏览器控制面板异常信息

Mixed Content: The page at ‘https://{域名}.com/‘ was loaded over HTTPS, but attempted to connect to the insecure WebSocket endpoint ‘ws://{ip}:{port}/‘. This request has been blocked; this endpoint must be available over WSS.
Uncaught DOMException: Failed to construct 'WebSocket': An insecure WebSocket connection may not be initiated from a page loaded over HTTPS.

好家伙，这种情况，毫无疑问我们就需要使用 wss:// 安全协议了，于是立即联系h5客户端，把连接服务端webscoket的形式由ws:// 改为 wss:// 。本以为这样就解决了，没想到一段时间后下一个问题又来了。

## 扩展：关于 ws 和 wss ##

WebSocket可以使用 ws 或 wss 来作为统一资源标志符，类似于 HTTP 或 HTTPS。其中 ，wss 表示在 TLS 之上的 WebSocket，相当于 HTTPS。默认情况下，WebSocket的 ws 协议基于Http的 80 端口；当运行在TLS之上时，wss 协议默认是基于Http的 443 端口。说白了，wss 就是 ws 基于 SSL 的安全传输，与 HTTPS 一样样的道理。所以，如果你的网站是 HTTPS 协议的，那你就不能使用 ws:// 了，浏览器会 block 掉连接，和 HTTPS 下不允许 HTTP 请求一样。

h5客户端改成wss连接后，测试发现还是无法正常游戏。无奈，再次打开浏览器面板，果然，又看到一个新的问题。

浏览器控制面板异常信息

	WebSocket connection to ‘wss://{ip}:{port}/‘ failed: Error in connection establishment: net::ERR_SSL_PROTOCOL_ERROR

之前在Http的情况下，客户端一直是用ip+port的形式来连接服务端，当然了也不会出现什么问题。很明显，在更改成Https后，若还是以这种方式连接服务端，浏览器就会报 SSL 协议错误，这很明显就是证书的问题。如果这时候还用 IP + 端口号 的方式连接 WebSocket ，是根本就没有证书存在的（即使我们在Nginx配置了SSL证书，但这种方式其实是不会走Nginx代理的），所以在生成环境下，更推荐大家用域名的方式来连接。于是，立刻又联系前端，再一次做更改，修改为 wss://{域名}/ 进行连接。我以为这样就真的解决了，没想到还是too young too simple，没一会下个问题又来了，测试反馈的结果还是不可以，第三次打开浏览器控制面板，果然又是一个新的错误信息。

浏览器控制面板异常信息

	WebSocket connection to ‘wss://{域名}/‘ failed: Error during WebSocket handshake: Unexpected response code: 400

看到这个错误信息后，确定这是服务端返回的400响应。既然可以请求到服务端，就说明客户端这边是没有问题的，那么问题最可能出在客户端和服务端之间。由于中间层使用了Nginx做转发，所以导致服务端无法知道这是一个合法的WebSocket请求。于是立刻查找了网上资料，在Nginx配置文件加入了以下配置，成功解决了这个问题。

    server {
    
    location / {
    
    proxy_pass http://localhost:{port};
    
    proxy_http_version 1.1;
    
    proxy_set_header Upgrade $http_upgrade;
    
    proxy_set_header Connection "upgrade";
    
    }
    
    }


接着，连忙拿域名进行再次连接测试，终于看到了101 Switching Protocols的响应Status Code。就这样，也算是终于解决完在 HTTPS 下以 wss://{域名}/ 的方式连接 WebSocket的一系列问题。不过，最后这其中还有一个小问（插）题（曲）。

关于Nginx中的WebSocket配置

自1.3 版本开始，Nginx就支持 WebSocket，并且可以为 WebSocket 应用程序做反向代理和负载均衡。WebSocket 和 HTTP 是两种不同的协议，但是 WebSocket 中的握手和 HTTP 中的握手兼容，它使用 HTTP 中的 Upgrade 协议头将连接从 HTTP 升级到 WebSocket，当客户端发过来一个 Connection: Upgrade请求头时，其实Nginx是不知道的。所以，当 Nginx 代理服务器拦截到一个客户端发来的 Upgrade 请求时，需要我们显式的配置Connection、Upgrade头信息，并使用 101（交换协议）返回响应，在客户端、代理服务器和后端应用服务之间建立隧道来支持 WebSocket。
   当然，还需要注意一点，此时WebSocket 仍然受到 Nginx 缺省为60秒的 proxy_read_timeout 配置影响。这意味着，如果你有一个程序使用了 WebSocket，但又可能超过60秒不发送任何数据的话，那么需要增大超时时间（配置proxy_read_timeout），要么实现一个Ping、Pong的心跳消息以保持客户端和服务端的联系。使用Ping、Pong的解决方法有额外的好处，如：可以发现连接是否被意外关闭等。

关于最后的这个小问题，主要是在对Nginx配置的时候将location=/的请求都进行了proxy_pass（转发）。由于h5客户端的文件打包成静态文件后，存放在服务器的指定目录下（这里假设在/root/html/static/路径下），这也就导致这种配置的情况下Nginx无法正常代理指定目录下的客户端文件。于是再一次修改配置文件，添加location配置，最终完美解决所有问题。


    location /static/ {
    
    root /root/html;
    
    }



小知识：

SSL

SSL(Secure Socket Layer，安全套接层) 简单来说是一种加密技术, 通过它, 我们可以在通信的双方上建立一个安全的通信链路, 因此数据交互的双方可以安全地通信, 而不需要担心数据被窃取. 关于 SSL 的深入知识, 可以看这篇文章: SSL/TLS协议运行机制的概述

WSS

WSS 是 Web Socket Secure 的简称, 它是 WebSocket 的加密版本. 我们知道 WebSocket 中的数据是不加密的, 但是不加密的数据很容易被别有用心的人窃取, 因此为了保护数据安全, 人们将 WebSocket 与 SSL 结合, 实现了安全的 WebSocket 通信, 即 WebSocket Secure.
所以说 WSS 是使用 SSL 进行加密了的 WebSocket 通信技术.

HTTPS

其实 HTTPS 和 WSS 类似, HTTP 之于 HTTPS 就像 WebSocket 之于 WebSocket Secure.
HTTP 协议本身也是明文传输, 因此为了数据的安全性, 人们利用 SSL 作为加密通道, 在 SSL 之上传递 HTTP 数据, 因此 SSL 加密通道上运行的 HTTP 协议就被称为 HTTPS 了.

总结

SSL 是基础, 在 SSL 上运行 WebSocket 协议就是 WSS; 在 SSL 上运行 HTTP 协议就是 HTTPS

