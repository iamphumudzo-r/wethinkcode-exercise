Final Submission: Understanding What to Change with AI

**Student:** Phumudzo Ramawa  
**Focus Areas:** Readability (Java), Refactoring (Python), Duplication (JavaScript)  
**Environment:** Linux Mint / Java 11 / Python 3.9

---

## Exercise 1: Code Readability Improvement (Java)

The original `UserMgr` class contained several "code smells" typical of rapid prototyping, including cryptic naming and security vulnerabilities.

### AI-Identified Issues
* **Cryptic Naming:** Methods like `a()` and `f()` and variables like `un` and `pw` fail to communicate intent.
* **Security Risk:** Using string concatenation for SQL queries creates a high risk for **SQL Injection**.
* **Lack of Encapsulation:** The validation logic was tightly coupled with the database logic.

### Refactored Logic
The AI suggested renaming the class to `UserManager` and the methods to `registerUser` and `findUserByUsername`. It also recommended using `PreparedStatement` to handle database interactions securely.

---

## Exercise 2: Function Refactoring (Python)

The `process_orders` function was identified as a "God Function" because it handled validation, pricing, inventory, and shipping in a single block.

### Refactoring Strategy: Functional Decomposition
The AI recommended breaking the logic into focused, testable helper functions:
1.  **`is_inventory_available()`**: Validates stock levels.
2.  **`apply_customer_discounts()`**: Isolates pricing logic.
3.  **`calculate_shipping_and_tax()`**: Handles logistics and financial rules.



### Insight
By separating these concerns, each component can be updated or tested independently without risking the entire order flow.

---

## Exercise 3: Code Duplication Detection (JavaScript)

The `calculateUserStatistics` function repeated nearly identical loop structures for age, income, and score.

### Consolidation Pattern
The AI suggested using a **Higher-Order Function** to replace the repetitive loops:
* **Refactor:** A generic `getAverage(data, property)` and `getMax(data, property)` function.
* **Benefit:** This reduces the code length by 60% and eliminates "copy-paste" errors where a developer might update the logic for 'age' but forget to update 'income'.

---

## Reflection Questions

* **Most Useful Strategy:** **Function Refactoring**. Breaking down large functions is the most effective way to manage the complexity of my **Macro Finance Network** project.
* **Surprising Improvements:** I had not considered that renaming the data class from `U` to `User` would significantly improve the readability of the collections (e.g., `List<User>` vs `List<U>`).
* **Safeguards:** Before implementing any AI-suggested refactoring in a production environment, I must ensure that my **Unit Tests** (from previous exercises) are passing to confirm that the behavior remains identical.

---

## Journal: 3 Key Learnings for Refactoring
1.  **Intent-Based Naming:** I learned that naming methods based on their *action* (e.g., `registerUser`) makes code self-documenting and reduces the need for comments.
2.  **Single Responsibility Principle:** A function should do one thing. If a function is longer than one screen, it is likely a candidate for refactoring.
3.  **DRY (Don't Repeat Yourself):** Duplicate logic is a maintenance liability. Generic utility functions are the best way to handle repetitive data patterns safely.