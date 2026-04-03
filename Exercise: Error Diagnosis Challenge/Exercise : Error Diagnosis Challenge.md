
Exercise:Error Diagnosis Challenge


**Error Scenario:** Scenario 2: Stack Overflow (Java)  
**Context:** Recursive Factorial Calculation

---

## Error Analysis: `java.lang.StackOverflowError`

### **Error Description**
A `StackOverflowError` occurs when the application exhausts the memory allocated for the **Call Stack**. Each time a method is called, a new "stack frame" is created to store local variables and return addresses. If recursion continues without a stopping point, these frames fill the stack's limited capacity, leading to an immediate crash.



### **Root Cause**
The provided `FactorialCalculator` fails due to **infinite recursion**. Specifically:
1.  **Missing Base Case:** The function lacks an `if` statement to terminate the process when the input reaches 0 or 1.
2.  **Negative Progression:** Because there is no stop condition, the function calls itself with increasingly smaller negative numbers (5, 4, ... 0, -1, -2...), creating an endless chain of stack frames.

### **Suggested Solution**
Implement a base case to return 1 when `num` is 0 or 1, and add a safety check for negative inputs.

```java
public static int calculateFactorial(int num) {
    // Safety check for invalid input
    if (num < 0) throw new IllegalArgumentException("Number must be non-negative");

    // Base case: 0! and 1! are both 1
    if (num <= 1) {
        return 1;
    }
    
    // Recursive step
    return num * calculateFactorial(num - 1);
}
Reflection Questions
AI vs. Online Documentation: While online docs define the error, the AI provided a structural perspective of the stack as a finite physical resource, which clarifies why deep recursion is risky in Java.

Manual Diagnosis Challenges: Without the repetitive stack trace (1000+ lines of the same method call), it would be difficult to distinguish between a logic error and a genuine system out-of-memory issue.

Preventative Coding: In the future, I would implement Input Validation at the start of recursive methods to ensure the input cannot bypass the base case.

Journal: 3 Key Learnings for Error Diagnosis
The Stack is Finite: I learned that while the "Heap" (where objects live) can be large, the "Stack" is quite small and easily overwhelmed by recursive depth.

Trace Patterns: A stack trace with a single repeating line is the "signature" of a recursion bug.

Iteration Security: For simple mathematical functions in Java, using a for loop is often more memory-resilient than recursion because it operates within a single stack frame.