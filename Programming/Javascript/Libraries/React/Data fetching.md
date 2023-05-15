```bash
$ npm i react-query
```


#### Fetch Records
```ts
import { useQuery } from "react-query"
import { BaseLayout } from "@/layouts/BaseLayout"
import { Users } from "@/lib/api"
import { IUser } from "@/lib/types"

export default function About() {
  const users = useQuery<IUser[], Error>("users", Users.GetAll)

  return (
    <BaseLayout>
      <h1 className="text-xl mb-2">About Us</h1>
      <>
        {users.isLoading && <span className="text-sm">Loading...</span>}
      </>

      <>
        {users.isError && <span className="text-sm text-red-400">
	        {users.error.message}
	    </span>}
      </>

      <>
        {users.data?.map(user => (
          <div className="flex flex-row space-x-5 text-sm py-2" key={user.id}>
            <div className="flex-1">{user.name}</div>
            <div>{user.email}</div>
          </div>
        ))}
      </>
    </BaseLayout>
  )
}
```

```ts
const GetAll = async () => {
  const res = await fetch("https://jsonplaceholder.typicode.com/users")
  if (!res.ok) {
    throw new Error("Failed to fetch users")
  }

  return res.json()
}

export const Users = {
  GetAll,
}
```

```ts
export interface IUser {
  id: string
  name: string
  email: string
}
```
