
#### To-do
- [ ] Suspense

---

#### `useState`

```tsx
import { useState } from "react"

export const Counter = () => {
  const [count, setCount] = useState(0)
  const increment = () => setCount(count => ++count)
  const decrement = () => setCount(count => --count)

  return (
    <div className="text-sm">
      <button className="bg-gray-100 p-3" onClick={decrement}>Decrement</button>
      <span className="bg-gray-200 px-3 py-3">{count}</span>
      <button className="bg-gray-100 p-3" onClick={increment}>Increment</button>
    </div>
  )
}
```

Any time the value of a state variable changes, React does a re-render. In the following case, React will not perform any re-renders when value for count changes.

```js
export const App = () => {
  let count = 0

  const handleClick = () => {
    count++
    console.log("Count: ", count)
  };

  return (
    <div className="container mx-auto px-4 py-10">
      <button
        className="bg-gray-100 hover:bg-gray-200 px-4 py-2 rounded"
        onClick={handleClick}
      >Count: {count}</button>
    </div>
  )
}
```


---

#### `useEffect`

##### Run Effects on every update
The following code will fire our callback every time the component updates / re-renders.

```tsx
import { useState, useEffect } from "react"

export const Counter = () => {
  const [count, setCount] = useState(0)
  const increment = () => setCount(count => ++count)
  const decrement = () => setCount(count => --count)

  // callback will run every time component re-renders
  useEffect(() => {
    console.log("rendering...")
  })

  return (
    <div className="text-sm">
      <button className="bg-gray-100 p-3" onClick={decrement}>Decrement</button>
      <span className="bg-gray-200 px-3 py-3">{count}</span>
      <button className="bg-gray-100 p-3" onClick={increment}>Increment</button>
    </div>
  )
}
```


##### Run Effects on specific state updates
```js
/**
 * callback will run every time reactive values inside the dependency array
 * updates, in this case "count"
 */ 
useEffect(() => {
  console.log("Updating count");
}, [count]);
```


##### Run Effects only on Mount
```js
/**
 * callback will execute only once during first render of the component  
 * (in production). The component will render twice in development (i.e. strict) 
 * mode.
 */
useEffect(() => {
  console.log("Component mounted");
}, []);
```


##### Run Effects on component unmount 
```tsx
import { useState } from "react"
import { Counter } from "@/components/Counter"

export function App() {
  const [showCounter, setShowCounter] = useState(false)
  const toggleShowCounter = () => setShowCounter(show => !show)

  return (
    <div className="container mx-auto p-4">
      <button 
        className="bg-gray-200 text-sm px-3 py-2" 
        onClick={toggleShowCounter}>Toggle Counter
	  </button>
        
      {showCounter && <Counter />}
    </div>
  )
}
```

```tsx
import { useState, useEffect } from "react"

export const Counter = () => {
  const [count, setCount] = useState(0)
  const increment = () => setCount(count => ++count)
  const decrement = () => setCount(count => --count)

  useEffect(() => {
    // run on mount
    console.log("mounting counter")

	// run on unmount
    return () => {
      console.log("counter removed from DOM")
    }
  }, [])

  return (
    <div className="text-sm">
      <button className="bg-gray-100 p-3" onClick={decrement}>Decrement</button>
      <span className="bg-gray-200 px-3 py-3">{count}</span>
      <button className="bg-gray-100 p-3" onClick={increment}>Increment</button>
    </div>
  )
}
```

**Note**: Any time you update state inside the `useEffect` hook, this can lead to infinite re-render cycles. Update runs `useEffect` which then again causes an update. Be careful to avoid this situation.


---

#### `useContext`

We can define a context on a parent Component. All components within the provider of the context will have access to value provided using the `useContext` Hook. We will no longer need to pass values / functions down through multiple levels of components.

```tsx
import { useState } from "react"
import { ThemeContext, Theme } from "@/lib/context/themeContext"
import { Form } from "@/components/Form"

export function App() {
  const [theme, setTheme] = useState<Theme>("light")
  const toggleDark = () => setTheme(theme => theme === "light" ? "dark" : "light")

  return (
    <ThemeContext.Provider value={theme}>
      <div className="container mx-auto p-4">
        <div>
          <button
            className="block px-3 py-2 bg-gray-200 text-sm"
            onClick={toggleDark}
          >Toggle Dark theme</button>

          <div>
            <Form />
          </div>
        </div>
      </div>
    </ThemeContext.Provider>
  )
}
```

```ts
import { createContext } from "react"

export type Theme = "light" | "dark"
export const ThemeContext = createContext<Theme>("light")
```

```tsx
import { useContext } from "react"
import { ThemeContext } from "@/lib/context/themeContext"

export const Form = () => {
  const theme = useContext(ThemeContext)

  return (
    <div className="p-5">
      {theme === "light" && <span className="bg-gray-100 text-gray-800">Light theme variant</span>}
      {theme === "dark" && <span className="bg-gray-800 text-gray-100">Dark theme variant</span>}
    </div>
  )
}
```


---

#### `useRef`

This hook lets us store information which isn't used for rendering e.g. `DOM` elements, timeout Ids etc.  Updating the current value of this hook **does not** trigger a re-render.

```js
import { useRef } from "react"

export function App() {
  const buttonRef = useRef(null)

  const handleClick = () => {
    // access element from DOM
    console.log("button clicked", buttonRef.current)
  }

  return (
    <div className="container mx-auto p-4">
      <h1>Hello world</h1>
      <button
        className="bg-gray-200 text-sm px-3 py-2"
        ref={buttonRef}
        onClick={handleClick}
      >Click Me</button>
    </div>
  )
}

```


---

#### `useReducer`

```ts
import { produce } from "immer"

export type State = {
  count: number
}

export type Action = 
  | { type: "increment", payload: number }
  | { type: "decrement" }

export const initState: State = {
  count: 0,
}

export function reducer(state: State, action: Action): State {
  switch (action.type) {
    case "increment":
      return produce(state, draft => {
        draft.count += action.payload
      })

    case "decrement":
      return produce(state, draft => {
        draft.count -= 1
      })
  }
}
```

```tsx
import { useReducer } from "react"
import { reducer, initState } from "@/lib/reducers/counterReducer"

export const Counter = () => {
  const [state, dispatch] = useReducer(reducer, initState)

  return (
    <div className="text-sm">
      <button
        className="bg-gray-100 p-3"
        onClick={() => dispatch({ type: "decrement" })}>Decrement</button>

      <span className="bg-gray-200 px-3 py-3">{state.count}</span>
      <button
        className="bg-gray-100 p-3"
        onClick={() => dispatch({ type: "increment", payload: 2 })}>Increment</button>
    </div>
  )
}
```


---

#### `useMemo`

```tsx
import { useState, useMemo } from "react"

export const App = () => {
  const [count, setCount] = useState(0)
  const expensiveCount = useMemo(() => {
    return count ** 2
  }, [count])

  return (
    <div className="container mx-auto px-4 py-10">
      <button
        className="bg-gray-100 hover:bg-gray-200 px-4 py-2 text-sm rounded"
        onClick={() => setCount(count + 1)}
      >+</button>

      <span className="bg-gray-100 px-5 py-2">{expensiveCount}</span>
    </div>
  )
}
```


---

#### `useCallback`

```tsx
import { useState, useCallback } from "react"
import { Button } from "@/components/Button"

export function App() {
  const [count, setCount] = useState(0)

  const updateCount = useCallback(() => {
    console.log(`Count ${count} updated to ${count + 1}`)
    setCount(count => count + 1)
  }, [setCount])

  return (
    <div className="container mx-auto px-4 py-10">
      <Button count={count} setCount={updateCount} />
    </div>
  )
}
```

```tsx
import { FC } from "react"

type Props = {
  count: number
  setCount: (callback: (count: number) => void) => void
}

export const Button: FC<Props> = ({ count, setCount }) => {
  return (
    <button
      className="bg-gray-100 hover:bg-gray-200 px-4 py-2 text-sm rounded"
      onClick={() => setCount(c => ++c)}
    >Count {count}</button>
  )
}
```


---

#### Custom React Hooks

```tsx
import { useState } from "react"

type UseLocalstorageState = {
  userId: string
  token: string
}

const initState: () => UseLocalstorageState = () => ({
  userId: localStorage.getItem("app.userId") ?? "",
  token: localStorage.getItem("app.token") ?? "",
})

export function useLocalstorage() {
  const [localState, setLocalStateBasic] = useState<UseLocalstorageState>(initState())
  const setLocalState = (state: Required<UseLocalstorageState>) => {
    setLocalStateBasic(state)

    /**
     * dont need to use useEffect here because this inner function is not a 
     * react component
     */
    localStorage.setItem("app.userId", state.userId)
    localStorage.setItem("app.token", state.token)
  }

  return { localState, setLocalState }
}
```

```tsx
import { useLocalstorage } from "@/lib/hooks/useLocalstorage"

export function App() {
  const { localState, setLocalState } = useLocalstorage()
  const populate = () => setLocalState({ userId: "100", token: "abc123" })

  return (
    <div className="container mx-auto px-4 py-10">
      <div>
        <button 
          className="bg-gray-200 px-3 py-2 text-sm"
          onClick={populate}  
        >Populate</button>
      </div>
      <div>
        <h1>UserId: {localState.userId} </h1>
        <h2>Token: {localState.token}</h2>
      </div>
    </div>
  )
}
```