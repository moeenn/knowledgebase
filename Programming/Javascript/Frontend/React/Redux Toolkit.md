```bash
$ npm install redux react-redux @reduxjs/toolkit
```

Configure Redux Store

```js
/* file: src/Lib/Store/index.js */
import { configureStore } from '@reduxjs/toolkit'

export const store = configureStore({
  reducer: {},
})
```

Provide the Redux Store to React

```js
/* file: src/main.js */
import React from 'react'
import ReactDOM from 'react-dom/client'
import { Provider } from 'react-redux'

import { App }  from '@/App'
import { store } from '@/lib/store'
import './assets/css/global.css'

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <Provider store={store}>
      <App />
    </Provider>
  </React.StrictMode>
)
```

Import the `Provider` from React Redux in `main.js`. Add `redux` store to the `provider`.

Create a Redux State Slice

```js
import { createSlice } from "@reduxjs/toolkit";

const initialState = {
    value: 0
}

export const counterSlice = createSlice({
    name: "counter",
    initialState,
    reducers: {
        up: (state, action) => {
            state.value += action.payload
        },
        down: (state, action) => {
            state.value -= action.payload
        }
    }
})

export const { up , down } = counterSlice.actions;
```

Add a new file named `src/store/counterSlice.js`. In that file, import the `createSlice` from `Redux Toolkit`.

Creating a slice requires a string name to identify the slice, an initial state value, and one or more reducer functions to define how the state can be updated. Once a slice is created, we can export the generated Redux action creators and the reducer function for the whole slice.


##### Update Redux Store
```js
import { configureStore } from "@reduxjs/toolkit";
import { counterSlice } from "./counterSlice";

export const store = configureStore({
    reducer: {
        counter: counterSlice.reducer
    }
})
```

Import the `counterSlice` and add it in the `reducer`.


##### Use Redux State and Actions in React Components
```js
import { useDispatch, useSelector } from 'react-redux';
import { up, down } from '../Store/counterSlice';

export const Counter = () => {

    const dispatch = useDispatch()
    const data = useSelector(state => state.counter.value)

    return (
        <>
            <div> {data} </div>
            <div>
                <button onClick={() => dispatch(up(1))}> + </button>
                <button onClick={() => dispatch(down(1))}> - </button>
            </div>
        </>
    )
}
```

Now we can use the React-Redux hooks to let React components interact with the Redux store. We can read data from the store with `useSelector`, and dispatch actions using `useDispatch`.