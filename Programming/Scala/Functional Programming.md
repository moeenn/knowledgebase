
#### Definitions

##### Referential transparency
An expression `e` is referentially transparent if for all programs `p`, all occurrences of `e` in `p`  
can be replaced by the result of evaluating `e` without affecting the meaning of `p`.  The **substitution model** provides a way to test whether an expression  is referentially transparent.  

##### Side effect
A side effect is something a function does aside from simply  returning a result.  
  
##### Procedures
Procedure is often used to refer to some parameterized chunk of code that may have side effects.  
##### Higher-order functions
Higher-order functions are functions that take other functions as arguments and may themselves  return functions as their output.  
  
##### Tail-position call
A call is said to be in tail position if the caller does nothing other than return the value of the recursive call. If a recursive function is tail-call optimized, we prevent the risk of a stack overflow.  Tail recursion ensures the stack does not grow with each recursive call.

##### Monomorphic vs Polymorphic functions
A monomorphic functions, or functions that  operate on only one type of data. A polymorphic function, sometimes called a generic function.  

