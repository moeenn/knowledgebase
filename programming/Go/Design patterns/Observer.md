
Type: Behavioral

```go
type Message string

type Subscriber interface {
	GetId() int
	GetLastMessage() Message
	Update(Message)
}

type Publisher interface {
	Subscribe(Subscriber)
	Unsubscribe(Subscriber)
	Notify(Message)
}

type ExampleSubscriber struct {
	id          int
	lastMessage Message
}

func NewExampleSubscriber(id int) *ExampleSubscriber {
	return &ExampleSubscriber{
		id:          id,
		lastMessage: "",
	}
}

func (s ExampleSubscriber) GetId() int {
	return s.id
}

func (s ExampleSubscriber) GetLastMessage() Message {
	return s.lastMessage
}

func (s *ExampleSubscriber) Update(message Message) {
	s.lastMessage = message
	fmt.Printf("[%d] %s\n", s.id, message)
}

type ExamplePublisher struct {
	subscribers []Subscriber
}

func (p *ExamplePublisher) Subscribe(sub Subscriber) {
	p.subscribers = append(p.subscribers, sub)
}

func (p ExamplePublisher) findSubscriberById(id int) int {
	for i := 0; i < len(p.subscribers); i++ {
		if p.subscribers[i].GetId() == id {
			return i
		}
	}

	return -1
}

func (p *ExamplePublisher) Unsubscribe(sub Subscriber) {
	idx := p.findSubscriberById(sub.GetId())
	if idx == -1 {
		return
	}

	p.subscribers = append(p.subscribers[:idx], p.subscribers[idx+1:]...)
}

func (p *ExamplePublisher) Notify(message Message) {
	for _, sub := range p.subscribers {
		sub.Update(message)
	}
}

func main() {
	subOne := NewExampleSubscriber(1)
	subTwo := NewExampleSubscriber(2)

	pub := ExamplePublisher{}
	pub.Subscribe(subOne)
	pub.Subscribe(subTwo)

	pub.Notify("Hello there")
}
```