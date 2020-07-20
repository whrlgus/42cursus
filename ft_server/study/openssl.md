https://www.cloudflare.com/learning/ssl/how-does-ssl-work/

https://www.digicert.com/kb/ssl-support/openssl-quick-reference-guide.htm

### What is SSL?

SSL(Secure Sockets Layer)은 인터넷에서 발생하는 통신을 암호화하여 보호하기 위한 protocol이다. TLS(Transport Layer Security)라는 개선된 protocol로 대체되었지만, 여전히 이러한 기술을 지칭하는 용어로 사용되고 있다.



### How does SSL/TLS work?

secure communication은 client와 server간의 secure connection을 open하고 public key를 교환하는 TLS handshake로 시작된다. TLS handshake 에서, 두 단말은 이후에 이뤄지는 communication의 모든 부분을 암호화하고 복호화 하는데 사용되는 session key를 생성한다. Asymmeric encryption 방식으로 상대의 public key를 이용해 암호화 하고 상대는 자신의 private key를 이용해서 복호화 한다.



### Generating SSL Certificates

테스트용 웹 서버에 SSL certificate이 필요하지만, 굳이 CA-signed certificate이 아니어도 되기 때문에 Self-Signed Certificate을 사용한다. 브라우저로 접속하면 신뢰할 수 없다는 경고를 보겠지만 말이다.

```shell
openssl req \
       -newkey rsa:2048 -nodes -keyout /etc/ssl/private/localhost.key \
       -x509 -out /etc/ssl/certs/localhost.crt \
       -subj '/C=KR'
```

`-newkey rsa:2048` option은 RSA 알고리즘을 사용해 2048-bit 의 private key를 만들겠다고 명시하는 것이다. `-nodes` option은 private key를 pass phrase로 암호화 하지 않는다는 것이다. `-x509`는 self-signed certificate을 만든다는 것이고, 유효 기간은 default 값이 30일이며 `-days 365 ` 와 같이 명시할 수도 있다. CSR의 정보는 `-subj`뒤에 명시한다.

