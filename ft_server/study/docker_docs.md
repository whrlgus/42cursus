# Docker overview

docker는 application을 개발하고, 옮기고, 실행(developing, shipping, running)하기 위한 platform이다. infrastructure의 제약 없이 빠르고 간편하게 코드를 테스트 하고 배치할 수 있는 장점이 있다. 



## Docker architecture

Docker는 client-server architecture를 사용한다. client가 daemon에게 building, running, distributing container 와 같은 요청을 하는 것이다. 둘을 같은 system에 존재할 수 있고, remote daemon과 연결할 수도 있다. REST API를 사용하여 통신한다.

### The Docker daemon

Docker **daemon**(dockerd)은 Docker API 요청을 listen하고 images, containers, networks, and volumes와 같은 Docker object를 관리한다. Docker service를 관리하기 위해 다른 daemon과 통신도 가능하다.

### Ther Docker client

Docker client(docker)는Docker와 상호작용하는 주요한 방법이다. `docker run` command로, client는 `dockerd` 에게 명령어를 보내 실행하게 한다. `docker` command는 Docker API를 사용하는 것이고, client는 여러개의 daemon과 통신할 수 있다.

### Docker registries

Docker **registry**는 Docker image를 저장한다. Docker **Hub**라는 public registry를 default값으로 설정하여 `docker pull` 이나 `docker run` command를 실행하면 **Hub**에서 required image를 가져온다. 물론 private registry를 사용하는 것도 가능하다.

### Docker objects

- **Images**

  image는 Docker **container**를 생성하기 위한 read-only 명령어 template이다. image는 다른 image를 기반으로 하여 customization을 통해 새로 생성할 수 있다. 예를 들어, `ubuntu` image에 필요한 application을 수행하기 위해 Apache web server를 설치하거나 configuration을 세팅하여 image를 만들 수 있다. 

  이렇게 registry에 published한 image를 가지고 새로운 image를 만들기 위해서는 **Dockerfile을** 작성하여 image를 build해야 한다. Dockerfile의 각각의 명령어는 image의 layer를 생성하며 rebuild시에 변경된 부분만 rebuilt된다. 이러한 mechanism으로 다른 virtualization technology 기술에 비해 image를 작고 빠르게 만들어 낼 수 있는 것이다.

- **Containers**

  container는 image의 runnable instance이다. Docker API나 CLI를 사용하여 container를 생성, 시작, 정지, 이동, 삭제할 수 있다. 여러개의 network에 연결할 수 있고, 저장 공간은 부착할 수 있으며, instance의 현재 상황에서 새로운 image를 생성하는 것도 가능하다.

  한 container의 network, storage, underlying subsystem들을 다른 container나 host 기기와 얼마나 독립된 상태로 사용할지에 대한 제어도 가능하다.

  다음 명령어는 `ubuntu` container를 실행하여 local common-line session에 결합하며, `/bin/bash` 를 실행하는 것으로, 아래와 같은 일련의 작업이 수행된다.

  ```bash
  $ docker run -i -t ubuntu /bin/bash
  ```

  1. `ubuntu` image를 가지고 있지 않다면, Docker는 configured registry로부터 image를 pull 한다. `docker pull ubuntu` command를 수행한다.
  2. Docker는 새로운 container를 생성한다. `docker container create` command를 수행한다.
  3. Docker는 read-write filesystem을 container에게 할당한다.
  4. networking option을 명시하지 않았기 때문에, Docker는 container와 default network를 연결하기 위한 network interface를 생성한다. 기본 값에의해 host 기기의 network connection으로 외부 network와 통신한다.
  5. Docker는 container를 시작하고 /bin/bash를 실행한다. `-i` 와 `-t` flag로 running interactively and attached to your terminal 한 상태로 실행된다. (`-i` 는 stdin stream을 추가하고, `-t` 는 terminal driver를 추가한다고 볼 수 있다.) 따라서, keyboard로 input을 제공하고 terminal을 통해 output을 확인할 수 있다.
  6. `exit` 명령어로 `bin/bash` 를 종료할 수 있으며, container도 멈추지만 제거되지 않아, 재실행하거나 제거할 수 있다.



