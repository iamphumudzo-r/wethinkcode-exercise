Exercise Part 1: Task Creation and Status Updates

1. Main Components Involved:TaskManagerCli (The Waiter):

 The presentation layer that handles the terminal interface, parses user input arguments, and passes the "order" to the manager.

TaskManager (The Chef): The central orchestrator that contains the business logic. It takes raw strings from the CLI, formats dates, creates the domain objects, and commands the storage layer.

Task (The Recipe): The domain model representing the actual data structure, handling its own internal metadata (like createdAt timestamps).

TaskStorage (The Pantry): The persistence layer holding an in-memory Map of all tasks and handling file I/O operations.

2. Execution Flow:

Creation Flow: The user types a command (create 'Fix Code') $\rightarrow$ TaskManagerCli parses the strings $\rightarrow$ calls TaskManager.createTask() $\rightarrow$ A new Task object is instantiated (generating a UUID) $\rightarrow$ Passed to TaskStorage.addTask() $\rightarrow$ TaskStorage adds it to its internal map and immediately calls save() to write to disk.

Update Flow: The user types a command (status <id> done) $\rightarrow$ TaskManagerCli extracts the ID and status $\rightarrow$ calls TaskManager.updateTaskStatus() $\rightarrow$ Retrieves a reference to the existing Task from the TaskStorage map $\rightarrow$ Mutates the task object directly in memory $\rightarrow$ Calls TaskStorage.save().

3. Data Storage and Retrieval:

Data is stored locally in a tasks.json file. The application uses the Google Gson library to convert Java objects to JSON. Crucially, it uses an "In-Memory State" model: TaskStorage holds a master Map of all tasks in RAM. Whenever a change is made, the save() method serializes the entire map and completely overwrites the tasks.json file. It also relies on custom Gson adapters to safely serialize LocalDateTime objects.

4. Interesting Design Patterns Discovered:The Partial Update Pattern:

 Instead of writing a dozen different setters (e.g., setPriority, setTitle), the system creates a temporary "dummy" Task object holding only the new values. It passes this dummy to task.update(updates), which intelligently copies only the non-null fields over to the real task. This is a highly scalable way to handle edits.

Exercise Part 2: Task Prioritization System

1. Initial Understanding vs. Discovered Reality:

Initial Guess: I assumed the system took a numeric input (1-4) and directly assigned it to a task, perhaps using the TaskPriorityManager to handle the conversion.

Discovered Reality: The integer-to-state conversion is handled natively by the TaskPriority Enum or the TaskManager itself. The TaskPriorityManager is likely reserved for complex sorting or scoring, not basic assignment.

2. Key Insights from Guided Questions:

Error Handling Differences: The creation flow and the update flow handle invalid data differently. Creation is often forgiving (defaulting to a standard priority), while updates are strict to prevent data corruption.

The "Ghost Task" Pattern: 
The Guided AI pointed out how the system handles updates by instantiating a brand-new "dummy" Task with the new priority, and passing that to the storage layer. This reinforces the partial-update pattern I discovered in Part 1.

3. Practical Modification (Adding a new Priority Level):

Adding a new priority like CRITICAL (5) requires touching multiple layers: The Enum (model/TaskPriority.java), the presentation layer validation (cli/TaskManagerCli.java), the orchestrator conversion (app/TaskManager.java), and potentially the sorting logic (util/TaskPriorityManager.java).

Exercise Part 3: Mapping Data Flow (Task Completion)

1. Data Flow Diagram (Task Completion):

User Types Command: status 1234-abcd done$\downarrow$CLI Parses Input: TaskManagerCli extracts ID (1234-abcd) and Status (done).$\downarrow$Manager Orchestrates: TaskManager.updateTaskStatus() finds task via storage.getTask().$\downarrow$State Change: Task object is mutated. setStatus(DONE) is called, which triggers markAsDone() to inject the completedAt timestamp.$\downarrow$Persistence: TaskStorage.save() is called, serializing the entire modified in-memory map to tasks.json.

2. State Changes During Completion:

When a task is marked as complete, two distinct state changes occur within the Task object:The TaskStatus enum property changes from TODO / IN_PROGRESS to DONE.The completedAt metadata property, which was previously null, is populated with the current LocalDateTime.(Note: If the task is reverted to IN_PROGRESS, the system must actively set completedAt back to null to prevent data inconsistencies).

3. Potential Points of Failure:Invalid ID: 

If the user provides a UUID that doesn't exist in the TaskStorage map, the update will fail silently or throw a Null Pointer Exception if not caught.Missing Try/Catch Blocks: Through guided questioning, I discovered the createTask method lacks robust exception handling. If a user inputs an invalid priority number (e.g., 9), the TaskPriority.fromValue() method throws an IllegalArgumentException which crashes the application instead of returning a graceful error.

4. How Changes are Persisted:

Changes are persisted using an "Overwrite All" strategy. The TaskStorage class maintains the single source of truth in RAM (Map<String, Task> tasks). When a single task's state changes, the save() method uses Google Gson to convert the entire map into a JSON string and completely overwrites the existing tasks.json file.


Exercise Part 4: Reflection and Presentation


Title: Decoding the Java Task Manager

1. Introduction (The Starting Point)
The Hook: Transitioning from building single-file C++ logic to exploring a structured Java enterprise application.

Initial Misconceptions: Opening the project and assuming it was raw Java with all the logic in one place.

The First Breakthrough: Discovering the Gradle build system and realizing the project relies heavily on a structured architecture and external libraries (like Gson and Apache Commons CLI).

2. High-Level Architecture (The Mental Model)
Separation of Concerns: How the AI helped me visualize the architecture using the "Waiter, Chef, and Pantry" model to understand data flow.

The Waiter (Presentation): TaskManagerCli.java takes the order.

The Chef (Orchestrator): TaskManager.java processes the logic.

The Recipe (Domain): Task.java holds the data and rules.

The Pantry (Persistence): TaskStorage.java handles the JSON file.

3. Tracing the Three Key Features
Task Creation (The Overwrite Strategy):

Process: Traced the flow from the CLI down to the storage layer.

Discovery: Discovered that the app doesn't append single tasks to a file. It keeps a master Map in memory and completely overwrites tasks.json upon every creation.

Task Prioritization (The Ghost Manager):

Process: Explored how integer inputs (1-4) become priority states.

Discovery: The AI pair-programmer tricked me into looking for a TaskPriorityManager that didn't exist. This taught me that the TaskPriority Enum cleanly handles its own mapping. I also found a critical missing try/catch block that would crash the app on invalid inputs!

Task Completion (Domain Self-Management):

Process: Mapped the state change when a task is marked DONE.

Discovery: Realized that setting a status also triggers metadata changes (like updating the completedAt timestamp), proving why we shouldn't use raw setters.

4. An Interesting Design Pattern: "The Ghost Task"
The Problem: How do you update just one field (like priority) without accidentally erasing the task's title or due date?

The Solution (Partial Update Pattern): I found that the TaskManager creates a brand new, empty "dummy" task with a temporary title, assigns it the new priority, and passes it to the update method. The original task then intelligently copies over only the non-null fields from the ghost task.

5. Challenges & The Power of AI Prompting
The Challenge: Letting go of the urge to put business logic inside the data models, and learning how to read across multiple files to find the true execution path.

The Prompt Strategy: The "Guided Questions" prompt was the most valuable tool. Instead of asking the AI, "What does this do?" and getting a lazy answer, I told it to act as a senior developer and quiz me.

The Result: It forced me to actually read the updateTaskPriority error handling and discover bugs on my own, rather than just reading an AI summary.

6. Conclusion
Final Takeaway: Approaching an unfamiliar codebase is less about reading every line of code, and more about identifying the boundaries between presentation, orchestration, and storage.