# Evaluate Deployment Logs (C++)

A C++17 application that processes deployment logs stored in a file, validates their structure and content, and generates a summary of successful deployments, failed deployments, and invalid records.

---

## Features

- Parses deployment logs from a file (`json.log`)
- Validates JSON using the **nlohmann/json** library
- Validates deployment IDs using **std::regex**
- Handles malformed JSON safely using exception handling
- Detects:
  - Invalid deployment IDs
  - Invalid deployment statuses
  - Missing required fields
  - Incorrect data types
  - Malformed JSON
- Produces a summary report

---

## Deployment ID Rules

A valid deployment ID must:

- Begin with `d-`
- Be followed by exactly **10 lowercase alphanumeric characters**

Example:

```
d-123456abcd
```

Regex used:

```regex
^d-[a-z0-9]{10}$
```

---

## Valid Status Values

- Success
- Fail

Any other value is treated as an error.

---

## Example Input (`json.log`)

```json
{"deployment_id":"d-123456abcd","status":"Success"}
{"deployment_id":"d-098765efgh","status":"Fail"}
{"deployment_id":"d-abcdef1234","status":"Running"}
{"deployment_id":"d-ABCDEF1234","status":"Success"}
```

---

## Example Output

```text
Success: 1
Failed : 1
Error  : 2
```

---

## Project Structure

```
.
├── EvaluateDeployment.cpp
├── Header.h
├── json.log
└── README.md
```

---

## Technologies Used

- C++17
- STL
- std::regex
- File I/O
- Exception Handling
- nlohmann/json

---

## How It Works

1. Read each line from `json.log`
2. Parse the JSON record
3. Validate the deployment ID
4. Validate the deployment status
5. Update counters
6. Print the final summary

---

## Complexity

| Operation | Complexity |
|----------|------------|
| Reading Logs | O(n) |
| JSON Parsing | O(n) |
| Regex Validation | O(1) per log |
| Overall | O(n) |

where **n** is the number of deployment log entries.

---

## Sample Output

```text
Success: 5
Failed : 4
Error  : 22
```

---

## Learning Objectives

This project demonstrates:

- Modern C++17 programming
- JSON parsing
- Regular expressions
- File processing
- Exception handling
- Defensive programming
- Input validation
