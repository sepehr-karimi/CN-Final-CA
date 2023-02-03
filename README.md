# CN-Final-CA
FINAL PROJECT OF CN

## PART A: 

DESCRIPTION OF PROJECT:
here we're going to build a network and send files from host A to Host B using a router.
we will be sending a 1 MB file and use slow start along with go back N  algorithm.


### Questions:

1.


TCP (Transmission Control Protocol) and UDP (User Datagram Protocol) are two types of protocols that are used to send data over the internet. They differ in their approach to sending data and the level of reliability they provide.

Reliability: TCP is a reliable protocol that ensures that the data being transmitted is accurate and arrives in the correct order. It does this by sending data in packets and re-sending any packets that are not received. UDP, on the other hand, does not guarantee the reliability of the data being sent and does not re-send packets that are lost.
Speed: Because of the added reliability measures, TCP is slower than UDP. However, the speed difference is usually not noticeable to the user.
Use case: TCP is commonly used for applications that require reliable data transmission, such as file transfers, email, and web browsing. UDP is typically used for applications that require real-time data transmission, such as streaming media, online gaming, and voice over IP.
In summary, TCP is used for applications that require accuracy and reliability, while UDP is used for applications that require speed and real-time data transmission.


2.

Go back N protocol use a timer for receiving the first packet ACK. If the acknowledgment of a
frame is not received within an agreed upon time period, all frames starting from that frame are
retransmitted.
Pros: It just needs a single timer
Cons: not efficient, waste bandwidth when a packet is lost/broken.

Selective Repeat protocol It uses two windows of equal size: a sending window that stores
the frames to be sent and a receiving window that stores the frames received by the receiver.
The size is half the maximum sequence number of the frame. The receiver records the
sequence number of the earliest incorrect or un-received frame. It then fills the receiving window
with the subsequent frames that it has received. It sends the sequence number of the missing
frame along with every acknowledgement frame.
Pros: efficient, only lost/broken packets need retransmission
Cons: complicated with multiple timers, receiver needs a buffer to buffer out-of-order packets


### description of code:

in packettools.cpp we will create the structure that is given to us in the HW.

We will be using the below code for go back N.
:
![Alt text](gbn.jpg?raw=true "Optional Title")

### Results:

#### connecting router to Hosts:

as you can see in the below pictures first we're connecting the hosts to the router.
and as you can see all of them are connected to the router
![Alt text](1.1.jpg?raw=true "Optional Title")

![Alt text](1.2.jpg?raw=true "Optional Title")

![Alt text](1.3.jpg?raw=true "Optional Title")

#### Sending Files:

Here we're going to show results of sending the files given to us that is 1MB. we will use packet size of 1.5 kB

![Alt text](2.1.jpg?raw=true "Optional Title")

![Alt text](2.2.jpg?raw=true "Optional Title")


## PART 2:
### Phase one
were going to create topology of a network and calculate min cost using DVRP algorithm


Qusetions:

1.

There are several methods to update routing tables efficiently in a network without having to run the routing algorithm for all nodes after a change in the network topology:

Link State Routing (LSR): LSR algorithms, such as OSPF and IS-IS, only require updates to be sent to the nodes directly connected to the affected link. The updates are then propagated throughout the network, allowing the routing tables to be updated quickly and efficiently.
Distance Vector Routing (DVR): In DVR algorithms, such as RIP and BGP, nodes can exchange information about their neighbors' routes and make updates to their routing tables as needed. This reduces the number of updates required when there is a change in the network topology.
Route Flapping Detection: Route flapping detection mechanisms can be used to minimize the number of updates required in both LSR and DVR algorithms. This can be done by detecting when a route changes frequently and ignoring further updates for a set period of time.
Route Aggregation: Route aggregation can also be used to reduce the number of updates required by combining multiple routes into a single route. This reduces the amount of information that must be sent in updates and helps to improve the stability of the network.
Hybrid Routing: Hybrid routing algorithms, such as EIGRP, combine aspects of both LSR and DVR to provide efficient updates while maintaining stability and reliability.
In conclusion, choosing the right method to update routing tables will depend on the specific requirements and constraints of the network, and may involve a combination of the above methods.

2.

Distance Vector Routing Protocol (DVRP) and Link State Routing Protocol (LSRP) are two types of routing protocols used in computer networks.

Distance Vector Routing Protocol (DVRP): DVRP is a type of routing protocol that uses the concept of distances and vectors to determine the best path for data to travel. Each node in the network maintains a table of the distances to all other nodes, and the best path is determined based on the minimum distance. DVRP is simple to implement and easy to understand, but can suffer from problems such as slow convergence, counting to infinity, and route oscillation.
Link State Routing Protocol (LSRP): LSRP is a type of routing protocol that uses the concept of link state information to determine the best path for data to travel. Each node in the network maintains a map of the entire network, including the state of all links, and the best path is determined based on the shortest path to the destination. LSRP is more complex to implement but provides more accurate and stable routing information, and is less prone to the problems that affect DVRP.
The choice between DVRP and LSRP will depend on the specific requirements and constraints of the network, including the size of the network, the level of accuracy required, and the level of complexity that can be supported.

In summary, DVRP is suitable for smaller networks with simple requirements, while LSRP is better suited for larger and more complex networks where accurate and stable routing information is critical


### phase two

1.

Random Early Detection (RED) and Explicit Congestion Notification (ECN) are two congestion control mechanisms used in computer networks to prevent network congestion.

Random Early Detection (RED): RED operates by randomly dropping packets before the network becomes congested. This serves as an early warning signal to senders, who can then reduce their transmission rate to avoid further packet drops. The random nature of the drops helps to avoid unfair treatment of individual flows and ensures that the network remains responsive.
Explicit Congestion Notification (ECN): ECN operates by marking packets instead of dropping them when the network is congested. The marked packets serve as a notification to the sender that the network is congested, allowing the sender to reduce its transmission rate. This avoids the waste of dropped packets and allows for more efficient use of network resources.
Both RED and ECN are used in the Internet Protocol (IP) networks to manage congestion and ensure that network resources are used efficiently. RED is often used in legacy networks, while ECN is becoming more common in modern IP networks.

In summary, the choice between RED and ECN will depend on the specific requirements of the network, including the type of traffic, the level of congestion, and the desired level of responsiveness.


### Description of Code:

here is the dvrp algorithm:

Using the File Router.cpp we're going to add routers
each of the routers require an ip for adding 

Using the file links.cpp we're going to add each link with the respectful cost of that.

Using the file Hosts.cpp we're going to add each host with an ip for that.

Using the file Graph.cpp we're going to plot the network.


# Contributers :

sepehr karimi

nilufar mohammadi
