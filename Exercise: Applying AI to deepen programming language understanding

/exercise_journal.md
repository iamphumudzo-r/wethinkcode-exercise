# Exercise: Applying AI to Deepen Programming Language Understanding


## Activity 1: Idiomatic Code Transformation

### 1. Idiomatic Suggestions
* **Encapsulation & Safety:** In modern C++, we use smart pointers to manage resources like the `Display*`. Validating the display via a constructor is more idiomatic than repeating `nullptr` checks.
* **Precision Timing:** C++14 allows for **chrono literals** (e.g., `50ms`), which makes timing logic significantly more readable.
* **Constant Correctness:** Methods that do not modify the object’s state should be marked `const`.

### 2. Side-by-Side Comparison

| Old Version | Improved Idiomatic Version |
| :--- | :--- |
| `void Virtualmouse::leftClick()` | `void Virtualmouse::leftClick() const` |
| `if (display == nullptr) return;` | `if (!display) return;` |
| `std::this_thread::sleep_for(std::chrono::milliseconds(getRandomInt(50, 150)));` | `using namespace std::chrono_literals;`<br>`std::this_thread::sleep_for(getRandomInt(50, 150) * 1ms);` |

### 3. Key Learnings (Journal)
1. **Readability:** Using `50ms` instead of nested constructors makes code intent immediate.
2. **Resource Entry:** Validating core pointers at the constructor level is cleaner than defensive checks in every function.
3. **Local Namespaces:** Scoping `using namespace std::chrono_literals` inside a function avoids polluting the global header files.

---

## Activity 2: Code Quality Detective

### 1. Code Smells Identified
* **Manual Cleanup:** Calling `XCloseDisplay` manually in the destructor is prone to errors if the object is copied.
* **Garbage Pointers:** The uninitialized `display` pointer in the constructor leads to "undefined behavior" rather than a safe `nullptr`.
* **Out Parameters:** Passing `int &x` is functional but less modern than returning a `struct`.

### 2. Code Review Checklist
- [ ] Are all pointers initialized to `nullptr` in the constructor?
- [ ] Can this manual cleanup be replaced by RAII/Smart Pointers?
- [ ] Am I passing strings by `const std::string&` to avoid copies?

### 3. Key Learnings (Journal)
1. **Uninitialized State:** I learned that an "empty" constructor leaves pointers with random memory addresses, making `if(p != nullptr)` checks fail.
2. **RAII Safety:** Wrapping C-style cleanup functions in C++ objects prevents leaks during crashes.
3. **Reference Efficiency:** Passing by `const &` is a vital habit for performance when handling strings.

---

## Activity 3: Understanding Language Feature (Smart Pointers)

### 1. Practical Use Cases
1. **Automating X11 Cleanup:** Using `unique_ptr` with a custom deleter to handle `XCloseDisplay`.
2. **Ownership:** Clearly defining which class "owns" a piece of memory.
3. **Exception Safety:** Ensuring memory is freed even if the program hits an error mid-loop.

### 2. Key Learnings (Journal)
1. **Ownership Thinking:** `unique_ptr` isn't just a tool; it's a way of designing code around who is responsible for a resource.
2. **Custom Deleters:** Smart pointers work with old C libraries by providing a specific cleanup function.
3. **Stack Unwinding:** I realized that smart pointers clean up automatically as the stack clears, which is much safer than manual `delete` calls.
