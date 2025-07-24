Handing large numbers can be problematic in dynamic / scripting languages. In JS we use the `bigint` type.

```ts
const largeNumber: bigint = 2381023981203981203918320312039n
const anotherLargeNumber: bigint = BigInt("56666666666666666666666666666666667")
```

**Note**: The `BigInt` function also accepts `number` as input parameter. However, that would defeat the purpose of using `bigint` and that should be avoided. 

**Note**: In case a very large number is required to be transmitted over-the-wire encoded in JSON, use `string` type to encode the number. This will ensure that number precision is not lost.

```ts
const rawData = `{ "number": "699999999999999999999999999999997" }`
const parsed: { number: string } = JSON.parse(rawData)

const parsedNumber: bigint = BigInt(parsed.number)
console.log(parsedNumber.toString())
```


---

#### JSON and BigInt
One big limitation of `bigint` is that it cannot be encoded to `json` by default. One option is to override the `toJSON` method on `BigInt.prototype`.

```ts
BigInt.prototype.toJSON = function () {
  return this.toString()
}
```

The above option is not very typescript-friendly. Also, we need to ensure that this logic executes before anything else in our application, which can be a pain. Another option which may work better is as follows.

```ts
class BigNumber {
  public readonly value: bigint

  constructor(value: string | bigint) {
    this.value = BigInt(value)
  }

  add(other: BigNumber): BigNumber {
    const result = this.value + other.value
    return new BigNumber(result)
  }

  subtract(other: BigNumber): BigNumber {
    const result = this.value - other.value
    return new BigNumber(result)
  }

  multiply(other: BigNumber): BigNumber {
    const result = this.value * other.value
    return new BigNumber(result)
  }

  divide(other: BigNumber): BigNumber {
    const result = this.value / other.value
    return new BigNumber(result)
  }

  toString(): string {
    return this.value.toString()
  }

  // this method is important because it will make our class JSON serializable.
  toJSON() {
    return this.value.toString()
  }
}
```