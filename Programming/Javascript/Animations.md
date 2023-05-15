```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="style.css">
  <script src="index.js" defer></script>
  <title>Web Animations</title>
</head>
<body>
  <div class="circle one"></div>
  <div class="circle two"></div>
  <div class="circle three"></div>
  <div class="circle four"></div>
</body>
</html>
```

```js
function animate(element, delay) {
  const animation = element.animate([
    { transform: 'translate(0, 0)' },
    { transform: 'translate(calc(25vw - 2rem), 5rem)' },
    { transform: 'translate(calc(50vw - 2rem), 0' },
    { transform: 'translate(calc(75vw - 2rem), -5rem)' },
    { transform: 'translate(calc(100vw - 2rem), 0)' },
  ],
    {
      duration: 700,
      iterations: Infinity,
      direction: 'alternate',
      easing: 'ease-in-out',
      fill: 'forwards',
      delay,
    });
}

function main() {
  const names = ['one', 'two', 'three', 'four'];
  let init = 100,
    step = 75,
    delay = 0;

  names.forEach((name, index) => {
    delay = (index === 0) ? init : delay + step;
    const circle = document.querySelector(`.circle.${name}`);
    animate(circle, delay);
  });
}

window.onload = main;
```

```css
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  outline: none;
  border: none;
}

body {
  display: flex;
  flex-direction: column;
  justify-content: center;
  width: 100vw;
  height: 100vh;
  background-color: rgb(26, 24, 24);
}

.circle {
  background-color: rgb(116, 116, 116);
  border-radius: 100%;
  height: 2rem;
  width: 2rem;
}
```