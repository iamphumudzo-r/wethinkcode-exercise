# Exercise: Learning a New Programming Language with AI (C++ to Java)


**Source Language:** C++  
**Target Language:** Java  

---

## Part 1: Learning Journey Plan

### 1. Learning Goals
* **Goal 1:** Build a multi-threaded Crypto Price Monitor using Java's Object-Oriented principles.
* **Goal 2:** Develop a REST API for a village intranet project using the Spring Boot framework.
* **Goal 3:** Understand the JVM's Garbage Collection (GC) mechanism to replace manual C++ resource management.

### 2. Structured Learning Plan

| Phase | Prerequisites | Learning Steps | Verification Activity |
| :--- | :--- | :--- | :--- |
| **1: The JVM & Objects** | C++ OOP Basics | JVM vs. Native, Everything as a Class, Primitive vs. Reference Types | Write "Hello World" and explain the `public static void main` syntax. |
| **2: Memory & Safety** | C++ Pointers/RAII | Garbage Collection, Interfaces, Exceptions, Packages | Refactor `Virtualmouse` into a Java class without a destructor. |
| **3: Collections & Generics** | C++ STL | ArrayList/HashMap, Generics vs. Templates, Lambdas, Streams | Build a program to sort/filter crypto trade history using Streams. |
| **4: Networking & Build** | Linux CLI | Maven/Gradle, Multi-threading, HTTP Clients, JUnit | Create a tool that fetches BTC prices via API and saves to a local file. |

---

## Part 2: Conceptual Understanding & Implementation

### 1. Philosophical Differences
* **C++ ("Trust the Programmer"):** Manual memory management. Errors often lead to segmentation faults from uninitialized pointers.
* **Java ("Protect the Programmer"):** The JVM sits between the code and hardware, managing memory automatically to prevent system crashes from "bad" pointers.

### 2. Step 2 & 3: Java Implementation (`VirtualMouse`)
Everything in Java resides in a single `.java` file, utilizing the Garbage Collector instead of a manual destructor.

```java
public class VirtualMouse {
    private String status;  // Reference Type
    private int clickCount; // Primitive Type

    public VirtualMouse() {
        this.status = "Disconnected";
        this.clickCount = 0;
    }

    public void leftClick() {
        this.clickCount++;
        System.out.println("Click performed. Total: " + clickCount);
    }
}
Journal: 3 Key Learnings for Step 2 & 3
Safety over Speed: Java's null is a predictable state, preventing the random "garbage memory" crashes common in C++.

Stack vs. Heap: Java strictly separates primitives (stack) for speed and objects (heap) accessed via references.

End of the Destructor: The JVM tracks references and cleans up unreachable objects automatically, removing the need for manual cleanup code.

3. Step 4: Verification Implementation (PriceTracker)
Java
public class PriceTracker {
    private double currentPrice; // Primitive
    private String cryptoName;   // Reference

    public PriceTracker(String name, double initialPrice) {
        this.cryptoName = name;
        this.currentPrice = initialPrice;
    }

    public void updatePrice(double newPrice) {
        this.currentPrice = newPrice;
        System.out.println(cryptoName + " updated to: $" + currentPrice);
    }
}
Journal: 3 Key Learnings for Step 4
Implicit Pointers: Java references are essentially pointers, but the hidden * syntax produces cleaner code.

Predictable Defaults: Uninitialized references default to null, avoiding C++ "garbage memory" issues.

Automatic Cleanup: No manual "free" code is required for objects; the Garbage Collector handles it.

Part 3: Advanced Prompting Techniques
1. Using Context (C++ vs. Java)
Comparison: Javaâs ArrayList is the equivalent of std::vector.

Difference: std::vector can store objects directly; ArrayList stores references, adding a layer of indirection for easier management at a minor performance cost.

2. Learning Through Teaching
Explanation: In Java, everything is an object passed by reference (except primitives). The JVM tracks usage and cleans up memory automatically, though external resources like network sockets still require manual closing.

Part 4: Mini-Project (Crypto Price Monitor)
Project Specification
Component A: PriceEntry class to hold the data.

Component B: Scanner loop for terminal-based user input.

Component C: ArrayList to store price history.

Final Reflection
Surprise: The amount of boilerplate (e.g., public static void main) compared to the directness of C++.

C++ Influence: Understanding pointers made Java "references" immediately intuitive; they function like smart pointers that don't require manual deletion.