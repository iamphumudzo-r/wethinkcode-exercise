#Exercise : Function Decomposition Challenge

**Language Implementation:** Java (`CustomerDataProcessor.java`)  
**Refactoring Target:** `processCustomerData` pipeline

---

## Part 1: Identification of Responsibilities

The original `processCustomerData` function was identified as a "God Function" containing over 300 lines of entangled logic. I identified five distinct responsibilities that required extraction to meet the Single Responsibility Principle:

1.  **Deduplication Management:** Loading and checking against existing system records.
2.  **Source-Specific Preprocessing:** Normalizing data based on its origin (CSV, API, or Manual).
3.  **Identity Validation:** Enforcing strict formats for emails and phone numbers.
4.  **Field Normalization:** Formatting names, addresses, and dates into system-standard structures.
5.  **Persistence Orchestration:** Mapping validated data to entities and handling database transactions.



---

## Part 2: Decomposition Plan & Helper Functions

I extracted the nested logic into private helper functions with clear names to improve the readability of the main execution flow.

### 1. Identity & Deduplication Helper
This function isolates the complex logic of checking both the current batch and the database for duplicates.
```java
private boolean isDuplicate(String email, Set<String> existingEmails, List<Map<String, Object>> currentBatch) {
    String normalizedEmail = email.toLowerCase();
    if (existingEmails.contains(normalizedEmail)) return true;
    return currentBatch.stream().anyMatch(r -> normalizedEmail.equals(r.get("email")));
}
2. Address Normalization Helper
This handles the conditional logic for different address formats (String vs. Map) and standardizes city/state casing.

Java
private Map<String, Object> normalizeAddress(Map<String, Object> rawAddress) {
    Map<String, Object> cleanAddress = new HashMap<>();
    cleanAddress.put("city", capitalizeWords(rawAddress.getOrDefault("city", "").toString()));
    cleanAddress.put("state", rawAddress.getOrDefault("state", "").toString().toUpperCase());
    return cleanAddress;
}
Part 3: The Refactored Main Function (The Orchestrator)
The main method now serves as a high-level Orchestrator, making the business logic visible at a glance without the clutter of implementation details.

Java
public Map<String, Object> processCustomerData(List<Map<String, Object>> rawData, 
                                             String source, 
                                             CustomerProcessingOptions options) {
    // 1. Setup Phase
    DeduplicationSets globalSets = loadDeduplicationData(options);
    
    // 2. Transformation & Validation Phase
    for (Map<String, Object> record : rawData) {
        if (reachedErrorThreshold(options, result)) break;

        RecordResult recordResult = validateAndTransform(record, source, globalSets, options);
        updateInternalState(result, recordResult);
    }

    // 3. Persistence Phase
    if (options.isSaveToDatabase()) {
        persistValidRecords(validRecords, source);
    }

    return generateProcessingReport(startTime, result);
}
Part 4: Reflection & Benefits
Readability: By moving try-catch blocks and deep nested if statements into helpers, the main pipeline logic is now self-documenting.

Maintainability: If the email validation rules change, I only need to update the isValidEmail helper rather than searching through a 300-line function.

Reusability: The normalizeAddress and capitalizeWords functions are now independent and can be reused in other modules, such as a User Profile update page.

Challenge: The most difficult aspect was maintaining the state of errorCounts. I resolved this by introducing a RecordResult object to carry both data and error metadata between functions.

Journal: 3 Key Learnings for Decomposition
The Orchestrator Pattern: A main function should describe what is happening; helper functions should describe how it is done.

Isolation of Concerns: Moving I/O operations (like customerRepository.findAll()) into their own methods makes the core logic easier to unit test.

Defensive Copying: I learned that in Java, it is safer to create a new HashMap during transformation to avoid side effects on the original raw data.