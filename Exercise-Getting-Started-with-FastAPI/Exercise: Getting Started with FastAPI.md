Exercise: Getting Started with FastAPI

**Language:** Python 3.11+  
**Environment:** Linux Mint (Isolated `.venv`)

---

## Part 1: FastAPI Fundamentals

### 1. Framework Comparison
| Feature | **FastAPI** | **Flask** | **Django** |
| :--- | :--- | :--- | :--- |
| **Philosophy** | Performance & Type Safety | Simplicity & Flexibility | "Batteries Included" |
| **Best For** | High-performance APIs | Small prototypes | Large web platforms |
| **Data Validation** | Automatic (Pydantic) | Manual / Extra libraries | Built-in |
| **Documentation** | Auto-generated (Swagger) | Manual / Extra libraries | Manual / Extra libraries |
| **Speed** | Extremely Fast (Async) | Moderate | Moderate |

### 2. Core Terminology
* **ASGI:** The modern standard for asynchronous Python web servers like Uvicorn.
* **Pydantic:** A library for data validation using Python type hints.
* **Type Hinting:** Syntax that enables FastAPI's automatic validation and documentation.
* **Path/Query Parameters:** Variables captured from the URL path or specified after the `?` in a URL.

### 3. Key Advantages
* **Automatic Docs:** Interactive testing interface at `/docs` out of the box.
* **Performance:** Comparable to Node.js or Go due to async support.
* **Fewer Bugs:** Strict type checking catches errors early, similar to compiled languages.

---

## Part 2 & 3: Implementation Strategy

### Conceptual Shift (C++ to Python)
In C++, a `struct` defines data. In FastAPI, we use a `BaseModel` from Pydantic to define the structure and enforce validation rules.

```python
from pydantic import BaseModel
from datetime import date

class TodoItem(BaseModel):
    title: str
    description: str | None = None
    due_date: date
    completed: bool = False
Journal: 3 Key Learnings for FastAPI Fundamentals
Functional Type Hints: Type hints in FastAPI are the engine for data validation, not just documentation.

Native Async: Built for high-concurrency, making it ideal for real-time systems like crypto monitors.

Instant Testing: The Swagger UI /docs allows for immediate logic verification without a frontend.

Part 4: Exercise Challenge (To-Do List API)
This application implements full CRUD operations with Pydantic validation and status filtering.

Python
from fastapi import FastAPI, HTTPException, Query, status
from pydantic import BaseModel, Field
from datetime import date
from typing import List, Optional
from enum import Enum

app = FastAPI(
    title="To-Do Manager API",
    description="A simple API for managing your tasks, built with FastAPI",
    version="1.0.0"
)

# --- MODELS ---
class TodoStatus(str, Enum):
    completed = "completed"
    pending = "pending"

class TodoItem(BaseModel):
    id: int
    title: str = Field(..., min_length=1, max_length=100)
    description: Optional[str] = Field(None, max_length=500)
    due_date: date
    completed: bool = False

class TodoCreate(BaseModel):
    title: str = Field(..., min_length=1, max_length=100)
    description: Optional[str] = Field(None, max_length=500)
    due_date: date

# --- MOCK DATABASE ---
todo_db = {}
id_counter = 0

# --- ENDPOINTS ---
@app.post("/todos/", response_model=TodoItem, status_code=status.HTTP_201_CREATED)
async def create_todo(todo: TodoCreate):
    global id_counter
    id_counter += 1
    new_todo = TodoItem(id=id_counter, **todo.dict())
    todo_db[id_counter] = new_todo
    return new_todo

@app.get("/todos/", response_model=List[TodoItem])
async def list_todos(
    status_filter: Optional[TodoStatus] = Query(None, alias="status")
):
    results = list(todo_db.values())
    if status_filter:
        is_completed = status_filter == TodoStatus.completed
        results = [t for t in results if t.completed == is_completed]
    return results

@app.patch("/todos/{todo_id}/complete", response_model=TodoItem)
async def mark_complete(todo_id: int):
    if todo_id not in todo_db:
        raise HTTPException(status_code=404, detail=f"Task {todo_id} not found")
    todo_db[todo_id].completed = True
    return todo_db[todo_id]

@app.delete("/todos/{todo_id}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_todo(todo_id: int):
    if todo_id not in todo_db:
        raise HTTPException(status_code=404, detail=f"Task {todo_id} not found")
    del todo_db[todo_id]
    return None
Journal: 3 Key Learnings for the To-Do Challenge
Automated Validation: Field and date types reject invalid data (like strings in date fields) before reaching the business logic.

Input Constraints: Using Enum for filters restricts API input to valid values only.

Development Speed: Building and testing an entire API backend is significantly faster than traditional methods.

Troubleshooting & Linux Environment
Journal: 3 Key Learnings for Path & Environment Management
The Colon Conflict: While Linux allows colons in names, system tools like venv use colons as delimiters. I learned to use dashes or underscores for directory naming.

PEP 668 Protection: Modern Linux distros "lock" the system Python. Using .venv is not just optional but necessary for system stability.

The Shell's Role: I realized the shell parses paths before tools run; naming conventions matter for automated workflows.

Reflection Questions
Effective Strategy: The "Four-Step Strategy" successfully bridged C++ concepts to Python's abstracted runtime.

Surprises: The massive amount of work handled "under the hood" by type hints compared to manual JSON parsing in C++.

C++ Help: My background in memory structure made Pydantic models feel like "smart structs" with built-in validation.

Next Steps: Learning to move from a mock dict database to a persistent one like PostgreSQL.