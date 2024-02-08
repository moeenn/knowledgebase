#### Arrays
```java
/* includes arrays utility methods */
import java.util.Arrays; 

public class Main {
  public static void main(String[] args) {
    /**
     *  declare empty fix-sized array: all element will have default value 
     *  i.e. 0 in case of ints
    */
    int[] evenNumbers = new int[5];

    /* declare array with values */
    int[] nums = {1,2,3,4,5};

    /**
     *  we cannot directly print-out the contents of and array, we must
     *  use the helper method
    */
    System.out.println(nums);                  /* [I@2626b418 */
    System.out.println(Arrays.toString(nums)); /* [1, 2, 3, 4, 5] */

    /* get length of array */
    System.out.println(nums.length);

    /* range-based for-loop */
    for (int n : evenNumbers ) {
      System.out.println(n);
    }

    /* using streams */
    Arrays.stream(nums).forEach(System.out::println);

	/** accessing elements */
	int[] nums = {1,2,3,4,5};

	try {
		int n = nums[10];
		System.out.println(n);
	} catch (ArrayIndexOutOfBoundsException ex) {
		System.out.printf("error: %s\n", ex.getMessage());
	}
  }
}
```


##### Two-dimensional Arrays
```java
/* includes arrays utility methods */
import java.util.Arrays; 

public class Main {
  public static void main(String[] args) {
    int[][] matrix = {
      {10, 20, 30},
      {40, 50, 60},
      {70, 80, 90},
    };

    /* print directly */
    System.out.println(Arrays.deepToString(matrix));

    /* range based for-loop */
    for (int[] row : matrix) {
      for (int n : row ) {
        System.out.println(n);
      }
    }
  }
}
```


---

#### ArrayList
```java
/**
 *  List is a generic interface. Java provides multiple implementation of 
 *  this interface. ArrayList is one of them
*/
import java.util.List;
import java.util.ArrayList;

public class Main {
  public static void main(String[] args) {

    List<Integer> nums = new ArrayList<>() {
      {
        add(10);
        add(20);
        add(30);
      }
    };

    /* get size of an array list */
    System.out.println(nums.size());

    /* range loop through list elements */
    for (Integer n : nums) {
      System.out.println(n);
    }

    /* loop using streams */
    nums.forEach(System.out::println);

    /* check if array contains a value */
    System.out.println(nums.contains(20));

    /** 
     * get value at specific index: will throw IndexOutOfBoundsException 
     * if out of bounds 
     */
    System.out.println(nums.get(2));
  }
}
```


---

#### Stack & Vector
```java
/**
 *  non-thread-safe implementation is called Stack
 *  if thread-safety is needed, use Vector instead (has the same interface
 *  as Stack)
*/
import java.util.Stack;

public class Main {
  public static void main(String[] args) {
	Stack<Integer> nums = new Stack<>() {
		{
			push(10);
			push(20);
			push(30);
		}
	};
	
    /* get size of stack */
    System.out.println(nums.size());

    /* view the top-most element in the stack */
    System.out.println(nums.peek());

    /* remove and return the top element from the stack */
    Integer top = nums.pop();
    System.out.println(top);

    /* check if stack is empty */
    System.out.println(nums.empty());
  }
}
```


---

#### Queue & LinkedList
```java
/**
 *  Queue is an interface. Java provides multiple implementations of this 
 *  interface including LinkedList and PriorityQueue
*/
import java.util.Queue;
import java.util.LinkedList;

public class Main {
  public static void main(String[] args) {
	Queue<Person> people = new LinkedList<>() {
		{
			add(new Person("Admin", 30));
			add(new Person("User", 20));
			add(new Person("Customer", 50));
		}
	};

	/* get the element at the start of the queue */
	System.out.println(people.peek());

	/* remove and return first element from the queue */
	Person first = people.poll();
	System.out.println(first);

	/* get size of the queue */
	System.out.println(people.size());
  }
}
```

```java
/**
 *  LinkedList is a implementation of a double-linked list i.e. each node
 *  has a reference to the previous and the next node.
*/
import java.util.LinkedList;
import java.util.ListIterator;

public class Main {
  public static void main(String[] args) {
    LinkedList<Person> persons = new LinkedList<>() {
      {
        add(new Person("Admin", 30));
        add(new Person("User", 28));
      }
    };

    /* add element at start of the linked list */
    persons.addFirst(new Person("Super admin", 35));

    /* add element at specified index */
    persons.add(2, new Person("Customer", 18));

    /* get the iterator object */
    ListIterator<Person> it = persons.listIterator();

    /* loop forward using iterators */
    while(it.hasNext()) {
      System.out.println(it.next());
    }

    /* loop backwards using iterators */
    while(it.hasPrevious()) {
      System.out.println(it.previous());
    }
  }
}
```


---

#### Sets
```java
/**
 *  Sets can only contain unique elements (i.e. no duplication of elements). 
 *  Set is an interface. Java provides different implementations of this 
 *  interface.
 * 
 *  HashSet (backed by HashMap) = Doesn't preserve order of elements
 *  TreeSet (backed by TreeMap) = Preserves order of elements
*/
import java.util.Set;
import java.util.HashSet;

public class Main {
  public static void main(String[] args) {
    Set<String> colors = new HashSet<>();
    colors.add("red");
    colors.add("blue");
    colors.add("green");

    /* this will do nothing, wont throw either */
    colors.add("red");

    /* remove and element from set */
    colors.remove("blue");
    
    /* range loop throug all elements */
    for (String c : colors) {
      System.out.println(c);
    }

    /* loop using streams */
    colors.forEach(System.out::println);
  }
}
```


##### Sets with custom classes
```java
import java.util.Set;
import java.util.HashSet;

public class Main {
  public static void main(String[] args) {
    Set<Color> colors = new HashSet<>();
    colors.add(new Color("red"));
    colors.add(new Color("green"));
    colors.add(new Color("blue"));

    /**
     *  adding a duplicate element will actually add a duplicate element
     *  because by default Java doesn't know how to compare equality of 
     *  custom classes
     * 
     *  We must implement equals and hashCode methods on our class to ensure
     *  uniqueness works properly 
    */
    colors.add(new Color("green"));

    colors.forEach(System.out::println);
  }
}
```

```java
import java.util.Objects;

public class Color {
  public String name;

  public Color(String name) {
    this.name = name;
  }

  @Override
  public String toString() {
    return "Color [name=" + name + "]";
  }

  @Override
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || getClass() != o.getClass())
      return false;

    Color c = (Color) o;
    return Objects.equals(this.name, c.name);
  }

  @Override
  public int hashCode() {
    return Objects.hash(name);
  }
}
```


---

#### Maps
```java
/**
 *  Map is an interface. Java provides a large number of implementations for
 *  this interface. HashMap is one of these implementations.
*/
import java.util.Map;
import java.util.HashMap;

public class Main {
  public static void main(String[] args) {
    Map<Integer, Person> map = new HashMap<>();
    map.put(1, new Person("Admin"));
    map.put(2, new Person("Client"));
    map.put(3, new Person("User"));

    /* this will overwrite the previous entry at key 2 */
    map.put(2, new Person("Clientx"));

    /* remove element from map */
    map.remove(3);

    /* get size of map */
    System.out.println(map.size());

    /* get a value by key */
    System.out.println(map.get(2));

    /* check if map includes a key value, returns boolean */
    System.out.println(map.containsKey(1));

    /* get all map keys */
    System.out.println(map.keySet());

    /* loop through map */
    map.entrySet().forEach(System.out::println);

    /* loop through map with lambda */
    map.entrySet().forEach(
      p -> System.out.printf("%d %s\n", p.getKey(), p.getValue())
    );

    /* loop through map with lambda */
    map.forEach((k, v) -> {
      System.out.println(k + " " + v);
    });
  }
}
```

