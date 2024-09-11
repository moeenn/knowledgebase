
**Event**: A signal that some domain event has occurred. No response is expected in case of an event.

**Command**: A command is request for an action to be performed. A response is expected in case of a command.


---

##### Components of EDA

**Producer**: Creates the event.

**Broker**: Events are submitted to the broker. It is the responsibility of the broker to route the event to the appropriate consumers.

**Consumer**: Events are processed by the consumers.


---

#### Benefits

**Decoupling** (not dependent on other services): Services don't communicate directly and therefore don't need to know about details of other services. 

**Scalability**: During times of high load, there is a risk that services may crash. Message brokers can add persistence to messages. This means that when a service is down, incoming messages to the service will not be lost. This allows the system to scale. However, introduction of a message broker add overhead to the system and each message will take longer to process.

