## What is an IP address

IP(Internet Protocol) 주소는 IP를 이용하여 통신을 하기 위해서 사용하는 numerical label로서, computer network에 연결되는 각각의 장치에 하나씩 부여된다.

IPv4(Internet Protocol version 4)는 32-bit(4 bytes)로 구성되어 있고, IPv6는 128-bit(16 bytes)로 구성되어 있다.

## What is a Netmask

netmask는 32-bit로 구성되어 있으며, IP 주소를 subnet으로 나누고 네트워크의 가용 호스트를 선별하는데 사용된다. 0과 255는 각각 network 주소와 broadcast 주소로 할당된다.

## What is the subnet of an IP with Netmask

subnet은 network를 두개 이상으로 나눈 것을 말한다. 예를 들어, IP주소가 200.100.10.0인 class C의 network를 두개로 쪼갠다면, default netmask인 255.255.255.0에 의해 생기는 host bits의 최상위 비트를 이용해 200.100.10.0/25과 200.100.10.128/25 두개로 나눌 수 있다. 네트워크 내부에 필요 이상으로 많은 호스트 IP를 갖게 되면 네트워크 대역망에 비효율적인 flow가 발생하기 때문에 이러한 문제를 줄이기 위한 목적으로 사용된다.

## What is the broadcast address of a subnet

broadcast 주소는 network 내의 모든 device들과 통신하기 위해 사용된다. DHCP server로 부터 IP 주소를 요청하는 host가 사용한다. Network IP 주소의 host part의 bit 가 전부 1로 되어 있는 주소를 broadcast 주소로 사용한다.

## What are the different ways to represent an IP address with the Netmask



## What are the differences between public and private IPs

- public IP는 Internet에서 직접적인 접근이 가능한 주소로 하나의 computing device에 유일한 IP주소 하나가 할당된다. google.com 의 172.217.22.14, Google's DNS server의 8.8.8.8 과 같이 web server, email server 등에 하나씩 할당되어 있어 바로 접근이 가능한 주소이다.

- private IP는 네트워크 망 내부에서 사용할 목적의 주소로, Class A,B,C 의 네트워크에서 할당된다. 가정에서 사용되는 컴퓨터, 프린터 등은 기기 당 하나의 private IP가 할당되어 내부적으로만 직접적인 접근이 가능하다. 외부 network에서 private IP로 접근하기 위해서는 NAT(Network Address Translator)가 필요하다. 

  다음과 같은 사설 IP들이 있다.

  - **192.168.0.0 - 192.168.255.255** (65,536 IP addresses)
  - **172.16.0.0 - 172.31.255.255** (1,048,576 IP addresses)
  - **10.0.0.0 - 10.255.255.255** (16,777,216 IP addresses)

## What is a class of IP addresses

네트워크를 효율적으로 운영하기 위해 하나의 network에 필요한 hosts의 개수에 따라 A,B,C,D,E 의 총 다섯 개의 class로 IP 계층을 나누어 사용한다.

> Number of networks = 2 ^ network_bits
>
> Number of Hosts/Network = 2 ^ host_bits - 2

#### Class A 주소

1st octec의 첫 bit는 0이다. 따라서 첫 octet 값의 범위는 1~127(0000 0001 ~ 0111 1111)이 된다. 하지만 127.x.x.x는 loopback IP 주소들로 사용하기 때문에, Class A에 속한 IP 주소는 1.x.x.x ~ 126.x.x.x의 값을 갖게 된다.

Class A IP 주소에 사용되는 default subnet mask는 255.0.0.0이다. 128(2^7)개의 네트워크와 16777214(2^24 - 2)개의 호스트가 있다.

#### Class B 주소

최상위 2bits가 10으로 구성된 주소이다. default subnet mask는 255.255.0.0이고 IP 주소는 128(10000000).0.x.x ~ 191(10111111).255.x.x의 값을 갖게 된다. 16384(2^14)개의 네트워크와 65534(2^16 - 2)개의 호스트가 있다.

#### Class C 주소

최상위 3bits가 110으로 구성된 주소이다. Default subnet mask는 255.255.255.0이고 IP 주소는 192(11000000).0.0.x ~ 223(11011111).255.255.x의 값을 갖게 된다. 2097152(2^21)개의 네트워크와 254(2^8 - 2)개의 호스트가 있다.

#### Class D 주소

최상위 4bits가 1110으로 구성된 주소이다. 224.0.0.0 ~ 239.255.255.255의 범위를 갖고 multicasting을 위한 주소이다. 서브넷 마스크는 없다.

#### Class E 주소

최상위 4bits가 1111로 구성된다. 240.0.0.0 ~ 255.255.255.255의 범위를 갖는다. 서브넷 마스크가 없다.

## What is TCP

TCP(Transmission Control Protocol)는 Internet protocol suite 중 하나로, IP network에 있는 host 간 통신을 위한 데이터 흐름을 안정적으로 처리할 수 있다. Connection-oriented 란 특성 때문에, client와 server 간 연결을 성립한 이후에 데이터를 주고 받는다. 

이러한 connection establishment는 three-way handshake 방식으로 진행된다. 

- Step 1 (SYN) : client는 server와 연결하기 위해 전송하려는 시작 segment의 번호 정보(x)와 함께 SYN(Synchronize Sequence Number) 신호를 보낸다.
- Step 2 (SYN-ACK) : 이에 대한 반응으로, server에서 client로 y번호의 SYN과 x+1 번호의 ACK(Acknowlegement) 신호를 보낸다.
- Step 3 (ACK) : 마지막으로 client에서 y+1번호의 ACK 신호를 server로 보내면서 둘 사이의 연결이 성립된다.

1,2 과정과 2,3과정으로 각 방향에 대한 연결이 성립된 것이고, full-duplex 통신이 가능해진다.

연결 종료는 4-way handshake 방식으로 진행되며 각각 FIN 패킷과 ACK패킷을 주고 받으면 각 방향으로의 연결을 종료시킨다.

## What is UDP

UDP(User Datagram Protocol)은 메시지에 해당하는 datagram이라고 불리는 전송 unit을 사용하여 통신한다. connectionless communication model을 사용하여 빠른 속도로 데이터 통신을 할 수 있다. Error check나 correction이 필요 없고 빠른 속도를 요구하는 application에서 사용하는 전송 프로토콜이다.

## What are the network layers



## What is the OSI model

OSI(Open System Interconnection) model은 표준 통신 프로토콜을 이용하여 여러 통신 시스템에서 정보 처리의 상호 운용을 가능케 하기 위한 목적으로 설계된 개념적 모델이다. 각 layer는 상위, 하위 layer와 필요한 정보를 주고 받아 역할을 수행한다.

- Layer 1: Physical Layer

  physical layer는 device와 physical transmission medium 간의 unstructured raw data 전송과 수신 process를 처리한다. 

- Layer 2: Data Link Layer

  data link layer는 물리적으로 연결된 두개의 device간의 연결을 맺고 종료하는 역할을 수행한다. 그리고 physical layer에서 발생하는 error를 확인하고 수정하며, 송신측과 수신측의 데이터 흐름 rate을 맞추기 위한 flow control도 수행한다.

- Layer 3: Network Layer

  network layer는 packet이라 불리는 다양한 길이의 data sequence를 다른 네트워크에 속한 node로 전송하는 기능적 절차적 수단을 제공한다. 네트워크에는 여러개의 node가 있고, 송신 노드에서 중간 노드들을 거쳐 최종적인 수신 노드까지 가는 network path를 정한다. 그리고 만약, data link layer에서 생성한 message가 길다면 여러개의 fragment로 쪼개어 독립적으로 전송하고 재조립하는 역할도 수행한다. 전송 에러에 대한 처리도 가능하다.

- Layer 4: Transport Layer

  transport layer는 두 host간의 데이터 전송에 관한 기능적 절차적 수단을 제공한다. 흐름 제어, segmentation/desegmentation, error control을 통해 안정성을 보장할 수 있다. 즉, 전송하는 segment를 감시하여, 성공적인 수신을 확인하고 손실시에 재전송하여 다음 데이터를 보내는 과정을 반복한다. 그리고 application layer에서 받은 message를 쪼개어 segment로 분리하는 역할도 수행한다. TCP와 UDP는 OSI 참조 모델에 속하지는 않지만, transport layer로 분류한다.

- Layer 5: Session Layer

  session layer는 컴퓨터 간의 connection establishment, management, termination을 제어한다. full-duplex, half-duplex, simplex와 같은 통신 방식을 관리하며 transport layer의 TCP에서 처리하는 closing session에 대한 역할도 수행한다. 그리고 session checkpoint 설정과 복구에 관한 역할도 수행한다. 

- Layer 6: Presentation Layer

  syntax layer라고도 불리는 presentation layer는 application 과 network간의 데이터 변환을 처리한다. 

- Layer 7: Application Layer

  application layer는 user interface로서 presentation layer와 상호작용할 수 있는 데이터와 그림을 사용자에게 보여주는 역할을 수행한다.

## What is a DHCP server and the DHCP protocol

DHCP(Dynamic Host Configuration Protocol)는 IP network에서 사용되는 network management protocol이다. DHCP로 인해 DHCP server는 네트워크 내부의 각 device에 IP 주소와 network configuration parameters 를 할당할 수 있고, 다른 IP network와 통신할 수 있는 것이다.

## What is a DNS server and the DNS protocol

DNS(Domain Name System)은 Internet의 전화번호부로 비유되는데, DNS server에 저장된 매핑 정보를 통해 domain name인 google.com을 IP 주소로 연결시켜준다.

## What are the rules to make 2 devices communicate using IP addresses



## How does routing work with IP



## What is a default gateway for routing



## What is a port from an IP point of view and what is it used for when connecting to another device







