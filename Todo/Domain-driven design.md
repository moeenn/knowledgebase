
##### Core domain
Primary area of operation for business. E.g. Netflix video streaming

#### Sub-domains
Areas of operation which are ancillary to the core domain and support its operations. Sub-domains should be defined by consulting business/domain experts.

E.g. Billing, Recommendations etc.


##### Key parts of domains
E.g. 
- Billing
    - Subscribers 
    - Accounts
    - Payment details
    - Subscription plans

- Video Streaming
    - Viewers

- Recommendations
    - Subscribers

Some domain parts may appear in multiple sub-domains. Their names can be different in each sub-domain.


##### Context map

1. Which domains communicate with each other?
2. How they communicate?
3. Direction of communication?

E.g.
- Video streaming needs to determine what video quality to show to the user.
- Video quality depends on the user's current subscription.
- Subscription information is outside the (bounded) context of the video steaming domain.
- Video streaming domain will need to reach out to the Billing domain to obtain relevant subscription information.


##### Domain objects

Two types
1. Entities: 
    - Mutable i.e. properties can change over time
    - Have unique IDs. They are linked to their real-world counterparts. Eg. Billing::Subscriber 
2. Value objects:
    - Immutable. If change is required, create a new value object
    - Not unique. Two value objects can have the same value
    - An entity can have multiple value objects as properties
    - Value objects can contain additional validation logic
    - Eg. Email, Date-of-Birth


##### Anti-corruption layer
We must ensure that Domain entities are not polluted with information outside their domain's bounded context. Anti-corruption layer ensures that data flowing between different domains is converted to the domain's relevant Entity. All domains will have their own anti-corruption layers around them.

E.g.
The Subscriber in the Billing domain and the Viewer in the Video streaming domain
refer to the same person. Video streaming domain's anti-corruption layer will convert Subscriber entity to Viewer entity when data is received from the Subscription domain.


##### Business invariant
Business rules which must always remain true, no matter the changes being made to the system.


##### Aggregates
- It is a group of several entities and value objects.
- Aggregates have unique IDs.
- Aggregates are responsible for maintaining Business invariants.

Eg.
Order aggregate may contain
- Customer 			(Entity)
- Products ordered		(Entity)
- Order price			(Value object)
- Shipping address		(Value object)


##### Transactional boundary
Every time changes are made to an aggregate, they should be committed or rolled back from the database. 


##### Repositories
The persistence layer for our Aggregates.


##### Services
Contain additional business logic, which either doesn't fit in a single aggregate or spans multiple aggregates.


	

