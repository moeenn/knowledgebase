```
# installation
$ sudo apt-get install php

# starting dev server
$ php -S localhost:5000
```

```php
<?php echo("Hello World"); ?>
```


---

#### Variables
```php
$name = "Admin";
$age = 45;
$flag = True;

// string interpolation
$message = "My name is {$name} and I am {$age} years old and it is {$flag} that he hates people"; 

// string concatenation
$full_message = "Hello, " . $message;
```

**Note**: The type of a variable can be found using the function `gettype()` or `var_dump()`.


##### Multi-line strings

```php
$query = <<<EOD
CREATE TABLE IF NOT EXISTS users 
(
  userID INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL,
    userName VARCHAR (256) UNIQUE NOT NULL,
    fullName VARCHAR (256) NOT NULL,
  password VARCHAR (256) NOT NULL
);
EOD;
```


##### Constants
There doesn’t exist the const keyword in PHP. We can define constants using the define functions. It is a convention to use all uppercase for constants’ names

```php
define('STRING1', 'Hello');
```

**Note**: Constants are Symbols. When we call them we don’t need the Dollar `$` sign.


---

#### Strict Typing
By default variables can be implicitly cast to wrong data types. We can prevent this by adding the following line to our PHP Scripts.

```php
declare(strict_types = 1);
```

**Note**: Strict Types cannot be enabled globally. We must add the above line at the top of every PHP file in our project.


---

#### Arrays

PHP Arrays can hold multiple data types. There are three forms of arrays in PHP
1. Indexed
2. Associative
3. Multidimensional


##### Indexed arrays

```php
$numbers = array(1, 2, 3, 4);
$myArray = ["This", "is", "a", "simple", "array"];

// loop through array
foreach($numbers as $num) {
  echo("{$num} ");
}

// append element
$myArray[] = "Appended";
```

Note: When array elements are accessed through references, they retain their last value after the loop. In the above example, `$num` will hold its last reference value after the `foreach` loop has ended. We must do the following.

```php
unset($num);
```


##### Associative arrays
```php
$details = [
  "name" => "Akiva Jones",
  "age" => 34,
  "occupation" => "Jonas Killer"
];

// adding key-values
$details["hobbies"] = "Paragliding";

// access by key
echo($details["age"]);

// loop through
foreach ($details as $key => $value) {
  echo("{$key} - {$value}");
}

// loop through with references
foreach ($details as $key => &$value) {
  echo("{$key} - {$value}");
}

// check if key exists in array
$arr = [
	"name" => "ascasac",
    "age" => 30,
];

echo array_key_exists("age", $arr); // 1

// multi-dimention arrays
$twoDimentional = [
	[12,23,34,45],
	[45,23,56,78],
	[67,89,34,65],
	[32,63,86,34]
];

// index row = 2, col = 1 i.e. 56
echo $twoDimentional[2][1]
```


---

#### Loops

```php
// the scope of $i is not limited to the loop
for($i = 0; $i < 10; $i++) {
  echo($i);
}

while($i < 20) {
  echo($i);
  $i++;
}

do {
  echo($i);
  $i++;
} while($i < 30);
```


---

#### Functions

```php
function Power(float $base, float $pow = 2): float {
  return $base ** $pow;
}
```


##### Passing Variables by Reference
By default, PHP will pass variables by value to functions. If we need a function to modify the original variable we can pass variables by Reference. This should help reduce memory usage.

```php
// sandbox.php
<?php declare(strict_types = 1);

function WriteToDoc(string &$data) : void {
  global $output;
  $output = $data;
}

function Double(int &$num) : void {
  $num *= 2;
}

function main() : void {
  $num = 300;
  Double($num);
  
  $msg = "The number is now {$num}";
  WriteToDoc($msg);
}

main();
```

```php
// index.php
<?php 
require_once("sandbox.php"); 
echo($output);
```

Note: Only variables can be passed to functions by Reference. We cannot define data inline as an argument to such a function that accepts arguments by reference. Following will result in errors.

```php
WriteToDoc("This is a message");
```


##### Variadic functions
```php
function total(int ...$nums): float {
  $result = 0;
  foreach ($nums as &$num) {
    $result += $num;
  }
  return (float) $result;
}

function main(): void {
  $sum = total(12, 34, 45, 56, 67);
  Document::Write((string) $sum);
}
```


---

#### Includes and Require

```php
include("sample.txt");
```

Note: If the included file is not found, the application will not crash. It will only throw a warning and render the rest of the page. If we need the application to crash if included file is not found, we can use require

```php
require("sample.txt");
```

In order to further optimize the code, we can prevent re-reading of the included file everywhere it is included

```php
require_once("layout.html");
```


---

#### HTML Templates
PHP code can be mixed in with the HTML markup. There is a clean way of doing this.

```php
$client = [
  'client' => $_SERVER['HTTP_USER_AGENT'],
  'client_ip' => $_SERVER['REMOTE_ADDR'],
  'remote port' => $_SERVER['REMOTE_PORT']
];

<?php if($client): ?>
  <?php foreach($client as $key => $value): ?>
    <tr>
      <td><?php echo($key); ?></td>
      <td><?php echo($value); ?></td>
    </tr>
  <?php endforeach; ?>
<?php endif; ?>
```


---

#### Handling forms

```php
<?php
$target = $_SERVER["PHP_SELF"];
$name = htmlentities($_POST["name"]);
$email = htmlentities($_POST["email"]);
?>

<form method="POST" action="<?php echo($target); ?>">
<fieldset>
  <label for="name">Name</label>
  <input type="text" name="name">
</fieldset>
<fieldset>
  <label for="email">Email</label>
  <input type="email" name="email">
</fieldset>
<input type="submit" value="Submit">
</form>
```

##### Security
HTML Forms are susceptible to Cross Site Scripting (`XSS`) Attacks. Users could enter malicious JavaScript within the document through the input fields. We can convert the input into harmless strings using the `htmlentities` function.

##### Validating Input
When input is received from the user, the first step is to sanitize the input. This removes all illegal characters from the input. Next we validate the entered data.

Following code implements the data validation for Email fields. No `sanitization` has been implemented.

```php
$is_valid = false;

if(filter_has_var(INPUT_POST, 'data')) {
  $is_valid = filter_input(INPUT_POST, 'data', FILTER_VALIDATE_EMAIL);
}

$msg = ($is_valid) ? 'Input is valid' : 'Input is not valid';
```

```php
$data = htmlentities($_POST['data']);

// sanitization returns clean data
$email = filter_var($data, FILTER_SANITIZE_EMAIL);

// validation returns boolean flag
$is_valid = filter_var($email, FILTER_VALIDATE_EMAIL);

$msg = ($is_valid) ? 'Input is valid' : 'Input is not valid';
```


##### Validating Multiple Fields
There is a cleaner way of validating a form using the filter_input_array function. Following code validates a form containing two fields: `data1` and `data2`

```php
$filters = [
	"data1" => FILTER_VALIDATE_EMAIL,
	"data2" => [
		"filter" => FILTER_VALIDATE_INT,
		"options" => [
			"min_range" => 1,
			"max_range" => 100
		],
	]
];

$validated_data = filter_input_array(INPUT_POST, $filters);
```


---

#### Sessions
Sessions provide a mechanism for holding temporary state on the server. Sessions can be used for remembering which users are logged in.

Sessions are different from cookies where the data is stored on the client machine. By default, the variables defined in one PHP file are not accessible from another PHP file (imports notwithstanding).

```php
// index.php
if(isset($_POST['submit'])) {
	// activate session superglobal (i.e. $_SESSION[])
	session_start();

	// create session key-values
	$_SESSION['name'] = htmlentities($_POST['name']);
	$_SESSION['email'] = htmlentities($_POST['email']);

	// redirect
	header('Location: page2.php');
}
```

**Note**: On `page2.php` we will need to activate the session `superglobal` (i.e. `$_SESSION[]`) in order to access the session values.

```php
// delete single variable
unset($_SESSION['name'])

// delete all session variables
session_destroy() 
```


---

#### Cookies
Cookies are used to store data in the client browser. Make sure this data is trivial because cookies can be modified.

```php
// setting cookie
$name = htmlentities($_POST['name']);
$expiration = time() + 3600;    // one hour from now
setcookie('name', $name, $expiration);

// access cookie
if(isset($_COOKIE['name'])) {
	echo $_COOKIE['name'];
}

// updating cookie
setcookie('name', 'Guest', time() + 600);

// delete cookie
setcookie('name', 'Guest', time() - 10 );

// counting total cookies
$cookies  = count($_COOKIE);
```


##### Multiple values inside a cookie

```php
$form_data = [
	'name' => htmlentities($_POST['name']),
	'email' => htmlentities($_POST['email']),
	'location' => htmlentities($_POST['location'])
];

// convert associative array to string
$form_data = serialize($form_data);

// set expiration to 10 minutes
$expiration = time() + 600;

// create cookies
setcookie('form_data', $form_data, $expiration);

// read cookie
$form_data = unserialize($_COOKIE['form_data']);
echo $form_data['name'];
```