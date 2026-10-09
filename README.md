 
# FirmwareCBOM

### An Object-Oriented Framework for Cryptographic Inventory and Risk Assessment of IoT Firmware

FirmwareCBOM is a collaborative C++ project developed by a team of four students to explore the identification, documentation, and security assessment of cryptographic components in Internet of Things (IoT) firmware.

Our goal is to develop a modular framework that identifies cryptographic components, generates a Cryptographic Bill of Materials (CBOM), and helps assess potential cryptographic security risks.

**Project status:** Early development — initial C++ OOP prototype implemented; automated scanning and reporting are planned.

---

## Team Members

This project is being developed collaboratively by four team members.

| Member | Name | Primary Responsibility |
|---|---|---|
| Member 1 | [Name] | Core OOP design and component modelling |
| Member 2 | [Name] | Firmware file handling and cryptographic scanning |
| Member 3 | [Name] | Cryptographic information and risk assessment |
| Member 4 | [Name] | CBOM generation, testing, documentation and integration |

*Responsibilities may evolve as the project develops. All team members will contribute to understanding, reviewing, and integrating the complete system.*

---

## 1. About the Project

Firmware is the software embedded in devices such as smart cameras, Wi-Fi routers, connected sensors, and smart locks.

Firmware may use cryptographic algorithms to protect data, authenticate users, verify software integrity, and secure communications.

A Cryptographic Bill of Materials (CBOM) is an inventory of cryptographic components used by a software system.

FirmwareCBOM aims to explore how such an inventory can be created and used to identify components that may require further security review.

## 2. Problem Statement

Cryptographic components can be difficult to track when firmware projects contain multiple algorithms or have incomplete documentation.

Developers need ways to identify cryptographic components, understand where they are used, assess relevant security concerns, and plan necessary updates.

Our project aims to simplify this process through a modular C++ application.

## 3. Project Objectives

- Identify cryptographic algorithms in supported firmware inputs.
- Represent detected components using object-oriented C++ classes.
- Generate a structured Cryptographic Bill of Materials.
- Assess potential risks using documented security rules.
- Provide recommendations for components requiring review.
- Explore future support for post-quantum cryptography (PQC) readiness.

## 4. Planned System Architecture

The proposed workflow consists of the following modules:

1. **Firmware Loader:** Reads supported input files.
2. **Crypto Scanner:** Searches for recognizable cryptographic algorithm references.
3. **Crypto Component Model:** Stores information about detected components.
4. **Crypto Database:** Maintains algorithm information and assessment rules.
5. **Risk Analyzer:** Evaluates components against the defined rules.
6. **CBOM Generator:** Produces a structured inventory and summary report.

These modules represent the planned architecture; not all modules have been implemented.

## 5. Technology Stack

- C++
- Object-Oriented Programming
- STL and file handling
- Clang / Apple Clang
- Visual Studio Code
- Git and GitHub

## 6. Current Progress

### Initial OOP prototype

The team has begun learning the project fundamentals and developing its initial C++ implementation.

The current prototype includes:

- A `CryptoComponent` class.
- Attributes for algorithm name, component type, and key-size information.
- A `display()` method.
- Separate demonstration objects for AES, RSA, and SHA-256.
- Successful execution of the demonstration program.

### Development status

| Feature | Status |
|---|---|
| Project definition and initial design | In progress |
| Basic `CryptoComponent` class | Implemented |
| Demonstration objects | Implemented |
| Automated file scanning | Planned |
| CBOM generation | Planned |
| Risk assessment | Planned |
| Structured report output | Planned |
| PQC readiness assessment | Future extension |

## 7. Development Roadmap

### Phase 1 — Foundation
- Establish the project structure.
- Implement the initial OOP model.
- Improve class design and encapsulation.

### Phase 2 — Cryptographic Detection
- Implement file input.
- Build the initial scanner.
- Identify supported cryptographic algorithm references.

### Phase 3 — CBOM Generation
- Store detected components.
- Generate a structured inventory.
- Validate report output using sample inputs.

### Phase 4 — Risk Assessment
- Define documented assessment rules.
- Identify components requiring security review.
- Generate recommendations and risk summaries.

### Phase 5 — Evaluation and Extensions
- Test using controlled sample firmware-related inputs.
- Measure detection accuracy and false positives.
- Explore binary firmware analysis and PQC readiness.

## 8. Project Structure

The initial implementation is intentionally simple:

```text
FirmwareCBOM/
├── main.cpp
├── README.md
└── .gitignore
```

As development progresses, the codebase will be organized into separate source and header files for the project's modules.

## 9. Collaboration Workflow

The team uses GitHub to maintain a shared codebase and document development progress.

Our intended workflow is:

1. Select a task or feature.
2. Implement and test the changes.
3. Commit changes with a meaningful message.
4. Review and integrate the work.
5. Update the README and roadmap when appropriate.

## 10. Learning Objectives

This project provides practical experience with:

- Classes and objects
- Encapsulation and constructors
- Inheritance and polymorphism
- File handling and STL containers
- Modular software design
- Git and collaborative development
- Basic testing and security assessment

## 11. Disclaimer

FirmwareCBOM is an educational project under development. The initial prototype is not a complete firmware security scanner or a security certification tool.

The presence of an algorithm name alone does not establish whether a system is secure. A meaningful assessment requires consideration of the algorithm's purpose, implementation, configuration, key management, and threat model.

---

**Built collaboratively, one feature at a time.**
