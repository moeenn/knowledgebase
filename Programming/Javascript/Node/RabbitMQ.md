#### Installation

```
$ npm install amqplib
$ npm install -D @types/amqplib
```


#### RPC Example

```json
{
	"scripts": {
	    "dev:client": "tsc-watch --onSuccess 'node build/client.js'",
	    "dev:server": "tsc-watch --onSuccess 'node build/server.js'",
	    "build": "npx tsc",
	    "start:client": "NODE_ENV=production node build/client.js",
	    "start:server": "NODE_ENV=production node build/server.js"
    }
}
```

```ts
// file: client.ts
import "module-alias/register"
import { RabbitMQService } from "@/broker/rabbitmqService"
import { rabbitmqConfig } from "@/config/rabbitmqConfig"
import { TestQueue } from "@/queues/testQueues"

async function client(): Promise<void> {
  await RabbitMQService.connect(rabbitmqConfig.queueURL)
  await TestQueue.init({ isClient: true })

  const res = await TestQueue.sendTestMessage({ message: "hello world" })
  console.log("result", res)

  RabbitMQService.disconnect()
}

client().catch(console.error)
```

```ts
// file: server.ts
import { RabbitMQService } from "@/broker/rabbitmqService"
import { rabbitmqConfig } from "@/config/rabbitmqConfig"
import { TestQueue } from "@/queues/testQueues"

async function server(): Promise<void> {
  await RabbitMQService.connect(rabbitmqConfig.queueURL)
  await TestQueue.init({ isClient: false })

  TestQueue.processTestMessages(async (message) => {
    return {
      result: "This is a message from the server",
      received: message.message,
    }
  })
}

server().catch(console.error)
```

```ts
// file: rabbitmqConfig.ts
export const rabbitmqConfig = {
  queueURL: "amqp://guest:guest@localhost:5672",
  defaultClientPrefetchCount: 1,
}
```

```ts
// file: rabbitmqService.ts
import amqp, { Connection, Channel } from "amqplib"

type IRabbitMQService = {
  connection: Connection | null
  channel: Channel | null
  connect: (url: string) => Promise<void>
  encodeMessage: (message: Record<string, unknown>) => Buffer
  disconnect: () => Promise<void>
}

export const RabbitMQService: IRabbitMQService = {
  connection: null,
  channel: null,

  async connect(url: string): Promise<void> {
    this.connection = await amqp.connect(url)
    this.channel = await this.connection.createChannel()
  },

  encodeMessage(message) {
    return Buffer.from(JSON.stringify(message))
  },

  async disconnect() {
    if (this.connection) {
      await this.connection.close()
    }
  },
}
```

```ts
// file: messageBroker.ts
import crypto from "node:crypto"
import { RabbitMQService } from "./rabbitmqService"
import { rabbitmqConfig } from "@/config/rabbitmqConfig"

export const MessageBroker = {
  async initQueue(
    queueName: string,
    isClient: boolean,
    isDurable = true,
  ): Promise<void> {
    if (!RabbitMQService.channel) {
      throw new Error("no connection established with rabbitmq")
    }

    await RabbitMQService.channel.assertQueue(queueName, { durable: isDurable })
    if (isClient) {
      await RabbitMQService.channel.prefetch(
        rabbitmqConfig.defaultClientPrefetchCount,
      )
    }
  },

  /**
   * transmit message to the server and await response.
   * Note: Only call this function on the client, and never on the server.
   */
  async clientEmitAndListenResponse<T>(
    queueName: string,
    content: Record<string, unknown>,
  ): Promise<T> {
    if (!RabbitMQService.channel) {
      throw new Error("no connection established with rabbitmq")
    }

    const responseQueue = await RabbitMQService.channel.assertQueue("", {
      exclusive: true,
    })
    const correlationId = crypto.randomUUID()

    RabbitMQService.channel.sendToQueue(
      queueName,
      RabbitMQService.encodeMessage(content),
      {
        correlationId,
        replyTo: responseQueue.queue,
      },
    )

    return new Promise((resolve) => {
      RabbitMQService.channel?.consume(responseQueue.queue, async (message) => {
        if (!message) return

        if (message.properties.correlationId === correlationId) {
          const data = JSON.parse(message.content.toString()) as T
          RabbitMQService.channel?.ack(message)

          /** free resources */
          await RabbitMQService.channel?.cancel(message.fields.consumerTag)
          await RabbitMQService.channel?.deleteQueue(responseQueue.queue)

          resolve(data)
        }
      })
    })
  },

  serverProcessIncomingMessages<T, E extends Record<string, unknown>>(
    queueName: string,
    processCallback: (message: T) => Promise<E>,
  ) {
    if (!RabbitMQService.channel) {
      throw new Error("no connection established with rabbitmq")
    }

    RabbitMQService.channel?.consume(queueName, async (message) => {
      if (!message) return

      const data = JSON.parse(message.content.toString()) as T
      RabbitMQService.channel?.ack(message)
      const reply = await processCallback(data)

      RabbitMQService.channel?.sendToQueue(
        message.properties.replyTo,
        RabbitMQService.encodeMessage(reply),
        {
          correlationId: message.properties.correlationId,
        },
      )
    })
  },
}
```

```ts
// file: testQueue.ts
import { MessageBroker } from "@/broker/messageBroker"

export type TestMessagePayload = {
  message: string
}

export type TestMessageResult = {
  result: string
  received: string
}

export const TestQueue = {
  queueNames: {
    test: "test",
  },

  async init(args: { isClient: boolean }) {
    for (const name of Object.values(this.queueNames)) {
      await MessageBroker.initQueue(name, args.isClient)
    }
  },

  async sendTestMessage(
    content: TestMessagePayload,
  ): Promise<TestMessageResult> {
    return await MessageBroker.clientEmitAndListenResponse<TestMessageResult>(
      this.queueNames.test,
      content,
    )
  },

  processTestMessages(
    processCallback: (
      message: TestMessagePayload,
    ) => Promise<TestMessageResult>,
  ): void {
    MessageBroker.serverProcessIncomingMessages(
      this.queueNames.test,
      processCallback,
    )
  },
}
```