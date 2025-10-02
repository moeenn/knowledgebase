
Event Sourcing is an architectural pattern for building stateful applications by capturing and storing all changes to an application's data as a sequence of immutable events, rather than storing the current state directly. Instead of updating a database record (e.g., changing a user's balance from $100 to $150), you append an event like "DepositMade: $50" to a log.


---

#### How Event Sourcing Works in Practice

Consider an e-commerce order system:

1. **Event Capture**: A user places an order → Append "OrderPlaced" event with details (e.g., items, total).
2. **Further Changes**: User cancels → Append "OrderCancelled" event.
3. **State Derivation**: To check order status, replay all events for that aggregate (e.g., Order ID): Start from empty state, apply "OrderPlaced" (status: pending), then "OrderCancelled" (status: cancelled).

**Note**: Events are typically JSON-serialized with metadata like timestamp, version etc.


---

#### Benefits and drawbacks

The biggest benefit of this approach is audit trail which helps with Auditability and Compliance.

Drawbacks are as follows:

- **Complexity**: Managing event streams, versioning (e.g., schema evolution), and replays adds overhead.
- **Storage Growth**: Event logs can balloon; requires pruning or archiving strategies.
- **Query Performance**: Naïve replays are slow for long histories—mitigate with snapshots.
- **Learning Curve**: Shifts mindset from CRUD to event thinking; not suited for simple apps.

