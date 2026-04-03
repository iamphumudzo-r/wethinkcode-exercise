Exercise: README and User Guide Documentation
# Final Submission: API Documentation Exercise

**Target Endpoint:** User Registration (`POST /api/users/register`)  
**Format:** Markdown, OpenAPI (YAML), and Developer Guide

---

## Part 1: Comprehensive Endpoint Documentation (Prompt 1)

### Endpoint: `POST /api/users/register`

#### 1. Purpose
This endpoint allows new users to create an account within the system. It handles data validation, password hashing, and triggers a verification email process.

#### 2. Request Parameters (Body - JSON)
| Field | Type | Required | Description |
| :--- | :--- | :--- | :--- |
| `username` | String | **Yes** | Unique handle for the user (min 3 chars). |
| `email` | String | **Yes** | Primary contact email (must be valid format). |
| `password` | String | **Yes** | Security credential (min 8 chars). |

#### 3. Response Format
* **Success (201 Created):**
    ```json
    {
      "message": "User registered successfully",
      "user": {
        "id": 101,
        "username": "phumudzo_dev",
        "email": "phumudzo@example.com",
        "created_at": "2026-04-03T07:24:11Z",
        "role": "user"
      }
    }
    ```
* **Error (409 Conflict):** Used when the username or email is already taken.
* **Error (400 Bad Request):** Used for validation failures (weak password, invalid email).

#### 4. Authentication & Security
* **Authentication:** None (Public endpoint).
* **Security:** Passwords are encrypted using `bcrypt` before storage.

---

## Part 2: API Reference Conversion (Prompt 2 - OpenAPI)

Converting this documentation to **OpenAPI/Swagger** allows for the generation of interactive documentation like the `/docs` page used in FastAPI.

```yaml
openapi: 3.0.0
info:
  title: User Registration API
  version: 1.0.0
paths:
  /api/users/register:
    post:
      summary: Register a new user
      requestBody:
        required: true
        content:
          application/json:
            schema:
              type: object
              required: [username, email, password]
              properties:
                username: { type: string, minLength: 3 }
                email: { type: string, format: email }
                password: { type: string, minLength: 8 }
      responses:
        '201':
          description: Created
        '400':
          description: Validation Error
        '409':
          description: User Already Exists


Part 3: Developer Usage Guide (Prompt 3)
Quick Start: Integrating User Registration
Target Audience: Frontend/Mobile Developers
Tone: Technical & Instructional
1. Formatting Requests
All requests must be sent as application/json. Ensure the email field is sanitized and validated on the client side to reduce 400 Bad Request errors.
2. Handling Response Logic
A 201 response indicates the record is created. Note that the user will remain in a "pending" state until they click the link in the confirmation email triggered by this endpoint.
3. Python Integration Example
Python
import requests

def register_new_user(name, mail, pwd):
    url = "[http://127.0.0.1:5000/api/users/register](http://127.0.0.1:5000/api/users/register)"
    payload = {"username": name, "email": mail, "password": pwd}
    
    response = requests.post(url, json=payload)
    
    if response.status_code == 201:
        return "Success: " + response.json()['message']
    return "Error: " + response.json()['message']


Journal: 3 Key Learnings for API Documentation
Semantic Status Codes: I learned that using specific codes like 409 Conflict is superior to a generic 400 error because it tells the developer exactly why the request failed (duplicate data vs. bad syntax).
Documentation as a Contract: Converting to OpenAPI showed me that documentation is a "contract" that ensures the backend and frontend are synchronized on data types and schemas.
Automation Readiness: By keeping documentation structured, I can use tools to automatically generate client-side libraries, significantly speeding up the overall development cycle.
Part 4: Build and Configuration Documentation
1. Project Infrastructure Overview
The Task Manager project uses Gradle as its build automation tool, supporting both POSIX-compliant (Linux/macOS) and Windows environments.
2. Technical Prerequisites
To successfully build and run the application, the following environment variables must be configured:
JAVA_HOME: Must point to a valid Java installation directory (JDK 11+).
PATH: Must include the Java binary directory so the java command is accessible.
3. Build & Execution Guide (from README.md)
The project includes a pre-configured README.md that provides standard entry points for development tasks:
Build Project: Compiles the source code and packages the application.
Run Application: Executes the CLI with specific arguments. Note that arguments containing spaces must be enclosed in single quotes within the double-quoted --args string.
Run Tests: Executes the JUnit 5 test suite with integrated logging for passed and failed events.

Journal: 3 Key Learnings for Build Documentation
Environment Resilience: I learned that the Gradle Wrapper (gradlew) is essential for cross-platform consistency, as it manages the build environment independently of the user's local Gradle installation.
Explicit JVM Configuration: By reviewing gradlew.bat, I saw that the project defaults to specific memory settings (-Xmx64m) to ensure it runs efficiently on low-resource systems.
Dependency Transparency: The build.gradle.kts file acts as the ultimate "Manifest" for the project. It told me exactly which libraries are used for testing (AssertJ, Mockito) versus production (GSON), which is information not found in the .java files alone.

