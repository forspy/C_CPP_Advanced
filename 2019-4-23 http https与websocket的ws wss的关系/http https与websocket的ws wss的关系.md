#http/https与websocket的ws/wss的关系

今天在域名升级到HTTPS的时候遇到websocket的链接问题，之前在http下使用的是new WebSocket('ws://xxx');但是在切换到HTTPS后这个链接部分浏览器报错甚至代码整体抛出异常走不下去了，之前没有注意过websocket在两个不同协议下有什么不同，实际上按照标准来是有如下对应关系的

    http -> new WebSocket('ws://xxx')
    
    https -> new WebSocket('wss://xxx')

也就是在https下应该使用wss协议做安全链接，且wss下不支持ip地址的写法，写成域名形式

经过测试，部分报错的浏览器的确是因为这个原因导致的代码异常，即在https下把ws换成wss请求即可，看到这里心细的也许会发现，是部分浏览器，实际上浏览器并没有严格的限制http下一定使用ws，而不能使用wss，经过测试http协议下同样可以使用wss协议链接，https下同样也能使用ws链接，那么出问题的是哪一部分呢

    1.Firefox环境下https不能使用ws连接
    
    2.chrome内核版本号低于50的浏览器是不允许https下使用ws链接
    
    3.Firefox环境下https下使用wss链接需要安装证书


实际上主要是问题出在Firefox以及低版本的Chrome内核浏览器上，于是在http与https两种协议都支持的情况下可以做兼容处理，即在http协议下使用ws，在https协议下使用wss

    let protocol = location.protocol === 'https' 
    	? 'wss://localhost:8888' 
    	: 'ws://localhost:8889';
    new WebSocket(protocol);

这样可以更加不同的协议环境采取不同的链接方法，当然如果只支持https那最好还是使用wss协议，避免Firefox以及部分低版本Chrome内核浏览器的异常，当然新版本的浏览器都是支持的
