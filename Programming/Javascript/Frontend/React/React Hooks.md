#### `useState`
```js
import { useState } from "react";

const App = () => {
  const [count, setCount] = useState(0);

  return (
    <div className="container mx-auto px-4 py-10">
      <button 
        className="bg-gray-100 hover:bg-gray-200 rounded px-4 py-2 text-sm"
        onClick={() => setCount(count + 1)}
      >Count: {count}</button>
    </div>
  )
};

export default App
```

Any time the value of a state variable changes, React does a re-render. In the following case, React will not perform any re-renders when value for count changes.

```js
const App = () => {
  let count = 0;

  const handleClick = () => {
    count++;
    console.log("Count: ", count);
  };

  return (
    <div className="container mx-auto px-4 py-10">
      <button
        className="bg-gray-100 hover:bg-gray-200 px-4 py-2 rounded"
        onClick={handleClick}
      >Count: {count}</button>
    </div>
  );
};

export default App
```


---

#### `useEffect`

##### Run Effects on every update
The following code will fire our callback every time the component updates / re-renders.

```js
import { useState, useEffect } from "react";

const App = () => {
  const [count, setCount] = useState(0);

  useEffect(() => {
    console.log("Updating component");
  });

  return (
    <div className="container mx-auto px-4 py-10">
      <button 
        className="bg-gray-100 hover:bg-gray-200 rounded px-4 py-2 text-sm"
        onClick={() => setCount(count + 1)}
      >Count: {count}</button>
    </div>
  )
};

export default App
```


##### Run Effects on specific state updates
```js
useEffect(() => {
  console.log("Updating count");
}, [count]);
```


##### Run Effects only on Mount
```js
useEffect(() => {
  console.log("Component mounted");
}, []);
```


##### Run Effects on Un-mount
```js
import { useState, useEffect } from "react";

const App = () => {
  const [basic, setBasic] = useState(false);

  if (basic) {
    return (
      <h1 className="text-xl my-2">You selected basic</h1>
    );
  }

  return (
    <Child setBasic={setBasic} />
  );
};

const Child = ({ setBasic }) => {
  const [count, setCount] = useState(0);

  useEffect(() => {
    return () => {
      console.log("Component unmounted");
    };
  }, []);

  return (
    <div className="container mx-auto px-4 py-10">
      <button
        className="bg-gray-100 hover:bg-gray-200 rounded px-4 py-2 text-sm"
        onClick={() => setCount(count + 1)}
      >Count: {count}</button>

      <button
        className="bg-gray-100 hover:bg-gray-200 rounded px-4 py-2 text-sm"
        onClick={() => setBasic(true)}
      >Set Basic</button>
    </div>
  );
};

export default App
```

**Note**: Any time you update state inside the `useEffect` hook, this can lead to infinite re-render cycles. Update runs `useEffect` which then again causes an update. Be careful to avoid this situation.


---

#### `useContext`
We can define a context on a parent Component. All components within the provider of the context will have access to value provided using the UseContext Hook. We will no longer need to pass values / functions down through multiple levels of components.

```js
/* file: App.jsx */
import { useState, useContext } from "react";
import MessageContext from "../providers/MessageContext";

import Navbar from "./Navbar";
import Banner from "./Banner";

const App = () => {
  const [message, setMessage] = useState("Hello from context");

  return (
    <div className="container mx-auto px-4">
      <UserContext.Provider value={{message, setMessage}}>
        <Navbar />
        <Banner />
      </UserContext.Provider>
    </div>
  );
};

export default App
```

```js
/* file: MessageContext.js */ 
import { createContext } from "react";

const MessageContext = createContext(null);
export default MessageContext;
```

```js
/* file: Navbar.jsx */ 
import { useContext } from "react";
import MessageContext from "../providers/MessageContext";

const Navbar = () => {
  const { message } = useContext(MessageContext);

  return (
    <div className="border-b border-gray-100 py-5">
      <span>Logo</span>
      <span>{message}</span>
    </div>
  );
};

export default Navbar;
```

```js
/* file: Banner.jsx */ 
import { useContext } from "react";
import MessageContext from "../providers/MessageContext";

const Banner = () => {
  const { message, setMessage } = useContext(MessageContext);

  const handleClick = () => {
    setMessage("A new message");
  };

  return (
    <div className="bg-gray-100 py-10 flex flex-col justify-center">
      <h1 className="inline-block text-2-xl m-auto">{message}</h1>
      <button
        className="bg-gray-200 hover:bg-gray-300 px-4 py-2 text-sm rounded"
        onClick={handleClick}
      >Update Message</button>
    </div>
  );
};

export default Banner;
```


---

#### `useRef`
```js
import { useRef } from "react";

const App = () => {
  const btn = useRef(null);

  const handleClick = () => {
    console.log("Button", btn.current);
  };

  return (
    <div className="container mx-auto px-4 py-10">
      <button
        ref={btn}
        className="bg-gray-100 hover:bg-gray-200 px-4 py-2 text-sm rounded"
        onClick={handleClick}
      >Click</button>
    </div>
  );
};

export default App
```


---

#### `useReducer`
```js
import { useReducer } from "react";

const reducer = (state, action) => {
  switch (action.type) {
    case "increment":
      return state + 1;

    case "decrement":
      return state - 1;

    default:
      throw new Error("Invalid action type provided");
  }
};

const App = () => {
  const [count, dispatch] = useReducer(reducer, 0);

  const handleIncrement = () => {
    dispatch({
      type: "increment"
    });
  }

  const handleDecrement = () => {
    dispatch({
      type: "decrement"
    });
  }

  return (
    <div className="container mx-auto px-4 py-10">
      <button
        className="bg-gray-100 hover:bg-gray-200 px-4 py-2 text-sm rounded"
        onClick={handleIncrement}
      >+</button>

      <span className="bg-gray-100 px-5 py-2">{count}</span>

      <button
        className="bg-gray-100 hover:bg-gray-200 px-4 py-2 text-sm rounded"
        onClick={handleDecrement}
      >-</button>
    </div>
  );
};

export default App
```


---

#### `useMemo`
```js
import { useState, useMemo } from "react";

const App = () => {
  const [count, setCount] = useState(0);
  const expensiveCount = useMemo(() => {
    return count ** 2;
  }, [count]);

  return (
    <div className="container mx-auto px-4 py-10">
      <button
        className="bg-gray-100 hover:bg-gray-200 px-4 py-2 text-sm rounded"
        onClick={() => setCount(count + 1)}
      >+</button>

      <span className="bg-gray-100 px-5 py-2">{expensiveCount}</span>
    </div>
  );
};

export default App
```


---

#### `useCallback`
```js
import { useState, useCallback } from "react";

const App = () => {
  const [count, setCount] = useState(0);

  const updateCount = useCallback(() => {
    console.log(`Count ${count} updated to ${count + 1}`);
    setCount(count => count + 1);
  });

  return (
    <div className="container mx-auto px-4 py-10">
      <Button count={count} setCount={updateCount} />
    </div>
  );
};

const Button = ({ count, setCount }) => {
  return (
    <button
      className="bg-gray-100 hover:bg-gray-200 px-4 py-2 text-sm rounded"
      onClick={() => setCount(count + 1)}
    >Count {count}</button>
  );
};

export default App
```


---

#### Custom React Hooks

```js
import { useState, useEffect } from "react";
import getUser from "../api/getUser";

const useDisplayName = () => {
  const [displayName, setDisplayName] = useState();

  useEffect(async () => {
    const user = await getUser();
    setDisplayName(user.name);
  }, []);

  return displayName;
};

const App = () => {
  const displayName = useDisplayName();

  return (
    <div className="container mx-auto px-4 py-10">
      <p className="text-xl">{displayName}</p>
    </div>
  );
};

export default App
```