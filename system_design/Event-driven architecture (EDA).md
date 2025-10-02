
**Event**: A signal that some domain event has occurred. No response is expected in case of an event.

**Command**: A command is request for an action to be performed. A response is expected in case of a command.


---

##### Components of EDA

**Producer**: Creates the event.

**Broker**: Events are submitted to the broker. It is the responsibility of the broker to route the event to the appropriate consumers. Generally, this will be achieved through **Kafka, RabbitMQ or Redis Streams**.

**Topic**: Events are tagged with metadata that describes the event, called a "Topic". Application users can register their interest in events related to a given topic by subscribing to that topic. Applications can use wildcards to subscribe to a group of topics that have similar topic strings.

**Consumer**: Events are processed by the consumers.

**Note**: Producers have no knowledge of the consumers and consumers have no knowledge of the producers. This maintains decoupling.


---

#### Other concepts

**Event Mesh**: It is a network of interconnected event brokers that share consumer topic subscription information and route messages among themselves so they can be passed along to subscribers.

**Deferred execution**: This property is inherent in EDA because of asynchronous communication. Publishers don't wait for the processing of the send messages, which will be processed only when received by a subscriber.

**Eventual Consistency**: Due to deferred execution, it is unlikely that different components of our system will be perfectly in-sync at all times. But, we can be sure that they will eventually become in-sync. E.g. Say we have an event that causes a cascade of events in 5 different services, and these events require updates to the databases of each of these services. These databases won't be in-sync when the processing of the overall event is in-progress. However, when all the services have processed the events, we can be sure that all these databases will reflect the same picture.

**Orchestration vs Choreography**: 
Orchestration refers to the request/response (i.e. Synchronous) model of communication between services. Choreography refers to the event-driven (i.e. Asynchronous) model of communication between services.

**Note**: Choreography is more flexible because it follows the **Open/Closed** principle more closely i.e. if the system needs to be extended and more actions need to be performed on existing events, we don't need to change the existing code and simply add new subscribers to existing events. 


---

#### Benefits

**Decoupling** (not dependent on other services): Services don't communicate directly and therefore don't need to know about details of other services. 

**Scalability**: During times of high load, there is a risk that services may crash. Message brokers can add persistence to messages. This means that when a service is down, incoming messages to the service will not be lost. This allows the system to scale. However, introduction of a message broker add overhead to the system and each message will take longer to process.

**Real-time Processing**: Systems can react to events as they happen, enabling immediate responses rather than waiting for batches of transactions. 

**Fault-tolerance and resiliency**: The system can continue to operate even when instances of services are down. 
- The message broker ensures that messages are not lost during this window (i.e. **enable buffering of events**) and will be processed by the same or another instance of the service.
- Due to decoupling, crashing of one service will not cause cascade of crashes in other related services.


---

#### Error handling 
Implement robust error handling mechanisms, including message retries and dead-letter queues, to ensure reliable event processing.

**Dead-letter Queue (DLQ)**: Malformed messages which cannot be processed by the consumers can clog-up the queues. DLQs hold such messages so they can be later processed or discarded.