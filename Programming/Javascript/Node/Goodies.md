#### Native sleep function

```js
import { setTimeout } from "node:timers/promises";

async function main() {
  console.log("Starting...");
  await setTimeout(1_000);
  console.log("Done");
}
```


---

#### Colored console output

```js
import { styleText } from "node:util";
const warning = styleText(["bgRed", "black"], " This is a warning ");
console.log(warning);
```

**Note**: This requires NodeJS v21 minimum.

