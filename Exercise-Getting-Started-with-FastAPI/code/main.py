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
    """Create a new to-do item"""
    global id_counter
    id_counter += 1
    new_todo = TodoItem(id=id_counter, **todo.dict())
    todo_db[id_counter] = new_todo
    return new_todo

@app.get("/todos/", response_model=List[TodoItem])
async def list_todos(
    status_filter: Optional[TodoStatus] = Query(None, alias="status", description="Filter by completed/pending")
):
    """List all to-do items with optional status filtering"""
    results = list(todo_db.values())
    if status_filter:
        is_completed = status_filter == TodoStatus.completed
        results = [t for t in results if t.completed == is_completed]
    return results

@app.patch("/todos/{todo_id}/complete", response_model=TodoItem)
async def mark_complete(todo_id: int):
    """Mark a specific to-do item as completed"""
    if todo_id not in todo_db:
        raise HTTPException(status_code=404, detail=f"Task {todo_id} not found")
    
    todo_db[todo_id].completed = True
    return todo_db[todo_id]

@app.delete("/todos/{todo_id}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_todo(todo_id: int):
    """Delete a to-do item"""
    if todo_id not in todo_db:
        raise HTTPException(status_code=404, detail=f"Task {todo_id} not found")
    
    del todo_db[todo_id]
    return None

# To run: uvicorn main:app --reload