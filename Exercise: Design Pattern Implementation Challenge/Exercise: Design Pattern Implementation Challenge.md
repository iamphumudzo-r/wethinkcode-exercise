
# Exercise : Design Pattern Implementation Challenge


**Pattern Selected:** Strategy Pattern  
**Language:** JavaScript  
**Refactoring Target:** `calculateShippingCost` (Shipping Logic)

---

## Part 1: Pattern Analysis & Opportunity Identification

### 1. The Problem: "Conditional Bloat"
The original `calculateShippingCost` function was a "God Function" that used deeply nested `if-else` blocks to manage three different concerns simultaneously: destination-based rates, shipping method logic, and varying dimensional weight rules. 

* **Maintenance Risk:** Any change to a single country's rate or a specific shipping method's surcharge required modifying the entire function, increasing the risk of regression bugs.
* **Violated Principle:** The code violated the **Open/Closed Principle**; it was not closed for modification whenever a new shipping provider or rule was added.



---

## Part 2: Refactored Implementation

I encapsulated each shipping method into its own "Strategy" class, allowing the main calculator to delegate logic to interchangeable objects.

### 1. Strategy Interface & Concrete Classes
```javascript
// Base Strategy
class ShippingStrategy {
  calculate(packageDetails, destination) {
    throw new Error("Method 'calculate' must be implemented");
  }
}

// Strategy A: Standard Shipping
class StandardShipping extends ShippingStrategy {
  calculate({ weight, length, width, height }, destination) {
    const rates = { 'USA': 2.5, 'Canada': 3.5, 'Mexico': 4.0 };
    let cost = weight * (rates[destination] || 4.5);
    
    // Standard-specific dimensional rules
    if (weight < 2 && (length * width * height) > 1000) cost += 5.0;
    return cost;
  }
}

// Strategy B: Express Shipping
class ExpressShipping extends ShippingStrategy {
  calculate({ weight, length, width, height }, destination) {
    const rates = { 'USA': 4.5, 'Canada': 5.5, 'Mexico': 6.0 };
    let cost = weight * (rates[destination] || 7.5);
    
    // Express-specific dimensional rules
    if ((length * width * height) > 5000) cost += 15.0;
    return cost;
  }
}
2. The Context Class (The Orchestrator)
JavaScript
class ShippingCalculator {
  constructor(strategy) {
    this.strategy = strategy;
  }

  setStrategy(strategy) {
    this.strategy = strategy;
  }

  calculate(packageDetails, destination) {
    const cost = this.strategy.calculate(packageDetails, destination);
    return typeof cost === 'number' ? cost.toFixed(2) : cost;
  }
}
Part 3: Benefits & Reflection
Improved Maintainability: Each shipping logic is now isolated. If "Express" rules change, the "Standard" class remains untouched.

Extensibility: Adding an "Overnight" or "International" strategy now only requires creating a new class rather than rewriting existing conditional logic.

Testability: I can now write isolated unit tests for StandardShipping without needing to trigger every possible branch of a massive if-else statement.

Journal: 3 Key Learnings for Design Patterns
Polymorphism over Conditionals: I learned that complex branching logic is often a "code smell" indicating that a polymorphic strategy would be more robust.

Architectural Separation: Patterns allow us to separate the "What" (calculating a cost) from the "How" (the specific algorithm used), which is vital for scaling projects like my Macro Finance Network.

The Open/Closed Principle: By using the Strategy pattern, I've made the system "Open for Extension" (new methods) but "Closed for Modification" (stable core logic).