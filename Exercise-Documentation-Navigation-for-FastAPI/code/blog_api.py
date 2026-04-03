
from fastapi import FastAPI, Depends, HTTPException, status
from pydantic import BaseModel
from typing import List, Optional
from datetime import datetime

app = FastAPI(title="WTC Blog API - Documentation Challenge")

# --- 1. SCHEMAS (Based on Pydantic Docs) ---
class Comment(BaseModel):
    user: str
    content: str
    timestamp: datetime = datetime.now()

class PostBase(BaseModel):
    title: str
    content: str
    author: str

class Post(PostBase):
    id: int
    comments: List[Comment] = []

# --- 2. MOCK DATABASE ---
blog_db = {}
id_counter = 0

# --- 3. DEPENDENCIES (Based on Security Docs) ---
async def verify_auth(api_key: str = "vhembe_secure_key"):
    # Simple placeholder for the OAuth2 flow recommended in docs
    if api_key != "vhembe_secure_key":
        raise HTTPException(status_code=401, detail="Unauthorized")
    return api_key

# --- 4. ROUTES (CRUD Operations) ---

@app.post("/posts/", response_model=Post, status_code=status.HTTP_201_CREATED)
async def create_post(post: PostBase, auth=Depends(verify_auth)):
    global id_counter
    id_counter += 1
    new_post = Post(id=id_counter, **post.dict())
    blog_db[id_counter] = new_post
    return new_post

@app.get("/posts/", response_model=List[Post])
async def search_posts(q: Optional[str] = None):
    """Basic search functionality as requested in Part 4"""
    posts = list(blog_db.values())
    if q:
        return [p for p in posts if q.lower() in p.title.lower()]
    return posts

@app.post("/posts/{post_id}/comments", response_model=Comment)
async def add_comment(post_id: int, comment: Comment):
    if post_id not in blog_db:
        raise HTTPException(status_code=404, detail="Post not found")
    blog_db[post_id].comments.append(comment)
    return comment