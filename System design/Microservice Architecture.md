#### TODO

- Event sourcing
- Command-query responsibility segregation (CQRS)
- Saga design pattern (for distributed transactions)
- Transactional outbox pattern (for fault tolerance)
- Circuit-breaker design-pattern

#### Questions

- How do API gateways discover different instances of a service?
- How are distributed transactions performed?


---

#### Microservices architecture vs Service oriented architecture

- Microservices own their own data. All data which is required by a microservice will be stored in the microservice's own database. SOA services don't own all their required data. If a piece of data is to be shared between services, the dependent service can fetch the data when required. This means there can be strong coupling between SOA services.


---

#### Messaging patterns

1. **Publish / Subscribe**: This is asynchronous, similar to what you mentioned as an event notification, where no response is expected. It's ideal for scenarios where multiple services might be interested in an event, and you don't need a direct response.

2. **Request / Response**: This is synchronous and can be done over HTTP or through a message broker. I prefer HTTP for this due to its simplicity and directness, especially for straightforward request-response interactions.

3. **Request / Reply**: Here, a request is sent asynchronously, and a message is sent back for the reply asynchronously. A message broker is usually used for this to facilitate decoupled communication.

**Note**: In this context `synchronous` simple means that we will have to wait for the response. 


---

#### Communication between microservices
Microservices can communicate with each other using 

1. HTTP / GRPC end-points
2. Message brokers

In order to decide which mechanism to use, we must consider whether the communication needs to be `synchronous` or `asynchronous`. If the communication needs to be synchronous, i.e. the message sender needs to wait for the response (from another microservice), then HTTP / GRPC mechanism is more suitable. 

However, if the communication is `asynchronous` i.e. the sender is not expecting an immediate response (or no response at all) then message brokers are the better option.


---

#### API Gateway

For microservices‑based applications, an API gateway acts as a single point of entry into the system. API Gateway is a kind of middleman which sits between the clients and the services. It may perform the following actions

- Redirect requests to appropriate services.
- Combine responses from multiple services and send back to client as a unified response.
- Perform translations between protocols e.g. the client may expect a RESTful JSON response whereas some services may be using gRPC protocol.
- Implement security policies i.e. perform Authentication, Authorization, access control, rate-limiting, encryption etc.

A single application may employ multiple API gateways eg. there could be separate API gateways for web clients, mobile application clients, and public API clients.


---

#### Eventual consistency

In distributed systems, two data-stores may temporarily become out-of-sync due to network delays between replications. Eventual consistency says that all data will become in-sync eventually, but there is no guarantee exactly when. Data-stores and replicas are updated asynchronously.

In contrast to **Eventual Consistency** there is also **Strong Consistency**. Strong consistency says that data-stores and their replicas will always have the most up-to-date data. This can be achieved but it can result in performance penalties because all data-stores and replicas will need to be updated synchronously.


---

#### CAP Theorem

**CAP** stands for the following.

**Consistency**: Consistency means that all clients see the same data at the same time, no matter which node they connect. For this to happen, whenever data is written to one node, it must be instantly forwarded or replicated to all the other nodes in the system before the write is deemed *successful*.

**Availability**: Availability means that any client making a request for data gets a response, even if one or more nodes are down. Another way to state this—all working nodes in the distributed system return a valid response for any request, without exception.

**Partition tolerance**: A partition is a communications break within a distributed system—a lost or temporarily delayed connection between two nodes. Partition tolerance means that the cluster must continue to work despite any number of communication breakdowns between nodes in the system.

CAP theorem states that In a distributed data store, at the time of network partition you have to chose either Consistency or Availability and cannot get both.

If we choose *Consistency*, the network may be unavailable when changes are being applied to all data-stores and replicas. Conversely, if we choose *Availability*, data between different data-stores and replicas may become inconsistent temporarily, at least until changes are applied to all of them asynchronously (i.e. **Eventual consistency**). 

**Side note**: Traditional SQL databases prioritise *Consistency* in this situation and NoSQL databases prioritise *Availability*.


---

#### Data synchronisation

Imagine that multiple instances of a microservice a running in a network, each with their own database. There are multiple mechanisms we can use to keep data between these databases consistent.

**Publish-Subscribe pattern**: Services publish events (e.g., data changes) to a message broker. Other instances subscribe to these events and update their databases accordingly. 

- **Advantages**: Loose coupling, scalability, and real-time synchronisation.
- **Disadvantages**: Increased complexity due to message broker management and potential latency.

**Database Replication:** Master-slave replication: A master database instance handles writes, while slave instances replicate the data for read operations.

**Advantages**: Simple setup and performance benefits for read-heavy workloads.
**Disadvantages**: Potential latency for writes and challenges in maintaining consistency across multiple replicas.

##### Types of data replication

**Asynchronous replication**: Updates are propagated asynchronously, reducing write latency but increasing potential inconsistency.

**Synchronous replication**: Updates are propagated synchronously, ensuring consistency but potentially impacting write performance.


---


#### Saga Pattern

Consider a scenario where a single business transaction spans multiple services. Because each service has their own isolated databases, it is not possible perform ACID transactions. This also means automatic database rollback options are not available and any rollback logic must be implemented manually.

Saga pattern splits the overall transaction into a series of local transactions. There are two ways to coordinate sagas:

1. **Choreography** - each local transaction publishes domain events that trigger local transactions in other services.
2. **Orchestration** - an orchestrator (object) tells the participants what local transactions to execute.

**Scenario**: Consider the following scenario: We have two services *Order service* and *Customer service*. *Order service* maintains the list of orders and *Customer service* maintains details about customers including their credit limit. 

##### Using Choreography technique (Async communication)

The following steps will be performed in their given order

1. *Order service* receives the request to book a new order.
2. Order is created in the *Order service* database with the status `PENDING`.
3. A message is published on the *Order Events Channel* in the message-broker that a new order is created.
4. *Customer service* listens for this event. On receiving the event the *Customer service* reverses the credit for the customer.
5. The reserving of the customer's credit may succeed or fail. The result of this database action is published on the *Customer Events channel*.
6. The *Order service* listens to this event. On receiving this event, the *Customer service* may do one of two things
	- In case the customer credit reservation was successful, service will mark the status of the order as `CREDIT_CONFIRMED`.
	- In case the customer credit reservation fails, service will mark the order status as `REJECTED`.


##### Using Orchestration technique (Sync communication)

In this technique, there is a single *Orchestrator service*. This service is responsible for sending commands to all other relevant services. If any of the services fail to perform the command, the orchestrator service will be responsible to sending compensation commands to the all the services which had successfully completed their command.

In our example, the *Order service* is the *Orchestrator service*. It is responsible for sending `RESERVE_CREDIT` command, to the *Customer service*. If the *Customer service* fails to reserve credit for the customer, the *Order service* will need to perform compensation actions in its own data-store to revert the data it previously stored for the new order.  

**Important Note**: The communication between services in orchestration will need to be synchronous. This is because the *Orchestrator service* must wait for a single command to complete before it sends the command to the next service in the chain. Remember that we should not use message-brokers for synchronous communication between services.


##### Which technique to choose?

For simpler workflows, choreography technique may be sufficient. However, if the workflows are more complex, i.e. require interaction between multiple services, the orchestration technique is preferred.


---
