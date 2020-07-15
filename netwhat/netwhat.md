## What is an IP address

IP(Internet Protocol) 주소는 IP를 이용하여 통신을 하기 위해서 사용하는 numerical label로서, computer network에 연결되는 각각의 장치에 하나씩 부여된다.

IPv4(Internet Protocol version 4)는 32-bit(4 bytes)로 구성되어 있고, IPv6는 128-bit(16 bytes)로 구성되어 있다.

## What is a Netmask

netmask는 32-bit로 구성되어 있으며, IP 주소를 subnet으로 나누고 네트워크의 가용 호스트를 선별하는데 사용된다. 0과 255는 각각 network 주소와 broadcast 주소로 할당된다.

## What is the subnet of an IP with Netmask



## What is the broadcast address of a subnet

broadcast 주소는 network 내의 모든 device들과 통신하기 위해 사용된다. DHCP server로 부터 IP 주소를 요청하는 host가 사용한다. Network IP 주소의 host part의 bit 가 전부 1로 되어 있는 주소를 broadcast 주소로 사용한다.

## What are the different ways to represent an IP address with the Netmask



## What are the differences between public and private IPs



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



## What is UDP



## What are the network layers



## What is the OSI model



## What is a DHCP server and the DHCP protocol

DHCP(Dynamic Host Configuration Protocol)는 IP network에서 사용되는 network management protocol이다. DHCP로 인해 DHCP server는 네트워크 내부의 각 device에 IP 주소와 network configuration parameters 를 할당할 수 있고, 다른 IP network와 통신할 수 있는 것이다.

## What is a DNS server and the DNS protocol



## What are the rules to make 2 devices communicate using IP addresses



## How does routing work with IP



## What is a default gateway for routing



## What is a port from an IP point of view and what is it used for when connecting to another device



