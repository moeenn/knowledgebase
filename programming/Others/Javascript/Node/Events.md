
#### Type-safe event emitter

```ts
import crypto from "node:crypto"
import { 
  WonderEventEmitter, 
  defineEventDictionary, 
  defineEvent } from "@grekomp/wonder-event-emitter" 

type AddTaskEventPayload = {
  taskId: string
  text: string
}

type UserLoginEventPayload = {
  userId: string
  email: string
}

type UserLogoutEventPayload = {
  userId: string
}

/** singleton class */
class GlobalEmitter {
  private static emitter = new WonderEventEmitter()
  public static events = defineEventDictionary({
    tasks: {
      added: defineEvent<AddTaskEventPayload>(),
    },
    user: {
      loggedIn: defineEvent<UserLoginEventPayload>(),
      loggedOut: defineEvent<UserLogoutEventPayload>(),
    },
  })

  static get instance(): WonderEventEmitter {
    return GlobalEmitter.emitter
  }
}

function main() {
  GlobalEmitter.instance.on(GlobalEmitter.events.user.loggedIn, (data) => {
    console.log("userID", data.userId)
  })

  GlobalEmitter.instance.emit(GlobalEmitter.events.user.loggedIn, {
    userId: crypto.randomUUID(),
    email: "admin@site.com",
  })
}

main()
```