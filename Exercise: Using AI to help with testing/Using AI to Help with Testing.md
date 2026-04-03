Exercise : Using AI to Help with Testing


**Language Implementation:** Java (`TaskPriorityManager.java`)  
[cite_start]**Testing Framework:** JUnit 5 / AssertJ [cite: 1]

---

## Part 1: Test Planning & Behavior Analysis

### 1.1 Behavior Analysis
After analyzing the `calculateTaskScore` function, the following core behaviors were identified for verification:
* **Base Weighting:** Each priority level must map to its correct multiplier (e.g., URGENT = 40).
* **Temporal Scaling:** Scores must increase as `dueDate` approaches, with a maximum boost for overdue items.
* **State Penalties:** Completion status (`DONE`) must significantly reduce the score to deprioritize finished work.
* **Metadata Recognition:** Specific tags like "blocker" must trigger a flat score increase.

### 1.2 Structured Test Plan
* **Unit Tests (High Priority):** * Verify individual scoring factors (Priority, Tags, Status) in isolation.
    * Test date boundaries: Exactly today, 48 hours out, and 7 days out.
* **Integration Tests (Medium Priority):** * Verify that `getTopPriorityTasks` correctly invokes the scoring and sorting logic to return a truncated, ordered list.
* [cite_start]**Dependencies:** Requires `JUnit 5` and `AssertJ` as defined in `build.gradle.kts`[cite: 1].

---

## Part 2: Refined Unit Testing

### 2.1 Improved Test for Due Date Calculation
A robust test avoids checking internal variables and instead focuses on the final output for a specific input state.



```java
@Test
void testCalculateScore_DueInTwoDays() {
    // Setup: Task due in exactly 48 hours from now
    LocalDateTime twoDaysFromNow = LocalDateTime.now().plusDays(2);
    Task task = new Task("Critical Fix", "Repairing leak", TaskPriority.MEDIUM, twoDaysFromNow, List.of());
    
    // Logic: Base(2*10) + DueWithin2Days(15) = 35
    int score = TaskPriorityManager.calculateTaskScore(task);
    
    // Assert: Use fluent AssertJ assertions for readability [cite: 1]
    assertThat(score).isEqualTo(35);
}
Part 3: Test-Driven Development (TDD)
3.1 New Feature: User Assignment Boost (+12)
Process:

Red: Wrote a test asserting that a task with isAssignedToMe = true scores 12 points higher than a baseline task.

Green: Implemented the minimal logic in calculateTaskScore to check assignment status.

Refactor: Verified the boost does not override the DONE status penalty.

3.2 Bug Fix: Days Since Update
Bug: The use of ChronoUnit.DAYS can return 0 for updates made earlier on the same calendar day, missing the "Recent Update" boost.
Fix: Adjusted the test to use a 2-hour-old timestamp and ensured the code correctly identifies it as < 1 day.

Part 4: Integration Testing
4.1 Full Workflow Verification
This test ensures that the TaskPriorityManager functions correctly as a cohesive system.

Java
@Test
void testFullWorkflow_SortingAndLimiting() {
    Task lowTask = new Task("Low", "Desc", TaskPriority.LOW, null, List.of()); // Score 10
    Task urgentTask = new Task("Urgent", "Desc", TaskPriority.URGENT, null, List.of()); // Score 40
    
    List<Task> pool = List.of(lowTask, urgentTask);
    
    // Integration: Score -> Sort -> Limit
    List<Task> topTasks = TaskPriorityManager.getTopPriorityTasks(pool, 1);
    
    assertThat(topTasks).hasSize(1);
    assertThat(topTasks.get(0).getTitle()).isEqualTo("Urgent");
}
Journal: 3 Key Learnings for Testing
Outcomes over Implementation: I learned that testing the result of the calculateTaskScore is more maintainable than testing the individual if statements inside it.

Boundary Awareness: Date-based algorithms are prone to "Off-by-one" errors; testing the exact transition between "Due Today" and "Due in 2 Days" is critical.

TDD as a Safety Net: Using TDD for the "User Assignment" feature ensured I didn't introduce regression bugs into the existing priority weighting logic.