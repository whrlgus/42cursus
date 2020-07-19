http://nginx.org/en/docs/beginners_guide.html

nginx는 한개의 **master** process와 여러개의 **worker** process로 동작한다. **master** process는 configuration을 읽어 evaluate 하고, worker process를 관리한다. **worker** process는 요청을 처리한다. Worker process의 개수는 configuration file에 정의되어 있고, 가능한 CPU core개수에 따라 자동적으로 조정된다. nginx와 module들의 동작은 configuration file에 의해 결정되며, default로 **/etc/nginx/nginx.conf** 가 설정 파일에 해당한다.



### Starting, Stopping, and Reloading Configuration

nginx는  `nginx -s [stop|quit|reload|reopen]` 과 같은 명령어로 동작시킬 수 있다.

**reload** configuration 신호를 받은 master process는 새로운 configuration file의 syntax 타당성 검사를 하고 변동 사항을 반영한다. 만약, 그 과정이 성공한다면, master process는 새로운 worker process를 생성하여 old worker process에게 shut down 요청을 보낸다. 반대의 경우는, master process가 변동사항을 roll back 하고 old configuration으로 동작을 계속한다. Shut down 요청을 받은 worker process는 새로운 요청은 받지 않고 수행중인 일을 마무리한 뒤 종료된다.



### Configuration File's Structure

nginx는 configuration file에 명시된 **directive**(지시)에 의해 제어되는 module들로 구성되어 있다. directive는 simple directive와 block directive로 나뉜다; **simple directive**는 공백으로 구분된 name과 parameters로 구성되고 semicolon으로 끝난다. **block directive**는 simple directive와 동일한 구조를 갖지만, semicolon대신에  `{}` 형태로 추가적인 명령어들을 명시한다. Events, http, server, location과 같이 nested 구조를 갖는 block directive를 context라고도 한다. 그리고 가장 바깥쪽에 있는 directive는 main context이다.



### Serving Static Content

웹 서버의 중요한 일은 image나 static HTML page를 제공하는 것이다. 다음과 같이 http, server, location block 구조로 요청에 해당하는 file이 포함된 local directory 경로를 명시함으로써 이를 가능하게 한다. reload 후에 서버에 접속하면 /data/www/index.html 파일의 페이지가 보여진다.

```nginx
http {
	server {
		location / {
			root /data/www;
		}
	}
}
```



### Setting Up a Simple Proxy Server

nginx는 proxy server로서의 역할을 수행할 수도 있다.

```nginx
http {
  # proxy server
	server {
		location / {
			proxy_pass http://localhost:8080;
		}
		location ~ \.(gif|jpg|png)$ {
			root /data/images;
		}
	}
  # proxied server
	server {
		listen 8080;
		root /data/up1;
		location / {
		}
	}
}
```

`http://localhost/apple.png` 의 URI로 접속하면 proxy server는 8080포트를 listen하는 서버로 요청을 보내 proxied server에서 받은 응답을 client에게 전달해준다.



### Setting Up FastCGI Proxying

nginx는 다양한 framework와 PHP와 같은 여러 programming language로 만들어진 application을 실행하는 FastCGI server로 요청을 전달하는 역할도 한다. 

> CGI(Common Gateway Interface)는 web server와 external application을 연결시기는 protocol이다. FastCGI(FCGI)는 web server와 CGI program간의 연결에서 overhead를 줄이는 목적으로 설계되었다.



FastCGI server와 함께 동작하는 nginx의 대부분의 configuration은 `proxy_pass` directive 대신에 `fastcgi_pass`가 사용되고, FastCGI server로 전달할 parameter를 설정하는 `fastcgi_param` directive를 사용한다.

```nginx
server {
    location / {
        fastcgi_pass  localhost:9000;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        fastcgi_param QUERY_STRING    $query_string;
    }
}
```

