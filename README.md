# 🔐 FirmwareCBOM

<p align="center">

# 🛡️ FirmwareCBOM

### An Object-Oriented Framework for Cryptographic Inventory, Risk Assessment & Post-Quantum Readiness of IoT Firmware

<br>

![C++](https://img.shields.io/badge/C++-OOP-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![Cybersecurity](https://img.shields.io/badge/Cybersecurity-Firmware-red?style=for-the-badge\&logo=hackthebox\&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Security-00A86B?style=for-the-badge)
![CBOM](https://img.shields.io/badge/CBOM-Cryptographic%20Inventory-8A2BE2?style=for-the-badge)
![PQC](https://img.shields.io/badge/PQC-Ready-orange?style=for-the-badge)

</p>

---

## 🌟 Overview

**FirmwareCBOM** is an Object-Oriented framework designed to analyze IoT firmware and identify the **cryptographic components** present inside it.

The system creates a **Cryptographic Bill of Materials (CBOM)** and evaluates the security status of detected cryptographic algorithms.

The project focuses on answering a simple but important question:

> 🔍 **What cryptographic components are present in IoT firmware, and what is their security status?**

Unlike a traditional **SBOM (Software Bill of Materials)**, which focuses on software components and dependencies, a **CBOM** focuses specifically on cryptographic components.

---

# 🎯 Problem Statement

Modern IoT firmware can contain many cryptographic mechanisms, including:

* 🔐 AES
* 🔑 RSA
* 🔏 ECDSA / ECC
* #️⃣ SHA-256
* ⚠️ SHA-1
* 🚨 MD5
* 🔓 DES

However, developers may not always have a clear inventory of which cryptographic mechanisms are being used inside their firmware.

This creates challenges when:

* Identifying weak cryptographic algorithms
* Detecting deprecated algorithms
* Understanding cryptographic dependencies
* Assessing firmware security
* Preparing for post-quantum cryptography
* Planning cryptographic migration

**FirmwareCBOM** addresses this problem by automatically scanning firmware source files and generating a structured cryptographic inventory.

---

# 💡 What is CBOM?

### SBOM vs CBOM

| 📦 SBOM                    | 🔐 CBOM                               |
| -------------------------- | ------------------------------------- |
| Software Bill of Materials | Cryptographic Bill of Materials       |
| Tracks software components | Tracks cryptographic components       |
| Libraries & dependencies   | Algorithms & cryptographic mechanisms |
| Software-focused           | Security & cryptography-focused       |

### FirmwareCBOM asks:

```text
┌─────────────────────────────────────────────┐
│          What cryptography is used?         │
├─────────────────────────────────────────────┤
│                                             │
│  🔐 Which algorithms are present?           │
│  🔑 What key sizes are being used?          │
│  ⚠️ Are any algorithms deprecated?          │
│  🛡️ What is the security risk?              │
│  ⚛️ Is the firmware quantum-ready?          │
│                                             │
└─────────────────────────────────────────────┘
```

---

# 🚀 Core Workflow

```text
                  📁 FIRMWARE
                       │
                       ▼
              ┌─────────────────┐
              │ Firmware Loader │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
              │  Crypto Scanner │
              └────────┬────────┘
                       │
                       ▼
             ┌───────────────────┐
             │ Crypto Components │
             └─────────┬─────────┘
                       │
                       ▼
              ┌─────────────────┐
              │ Crypto Database │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
              │  Risk Analyzer  │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
              │ CBOM Generator  │
              └────────┬────────┘
                       │
                       ▼
                📊 SECURITY REPORT
```

---

# ✨ Key Features

## 🔍 1. Firmware Analysis

FirmwareCBOM analyzes firmware represented through source files, configuration files, or simulated firmware inputs.

The initial version focuses on source-level analysis rather than complex binary reverse engineering.

Example:

```text
firmware/
│
├── sensor.cpp
├── communication.cpp
├── authentication.cpp
├── storage.cpp
└── config.txt
```

---

## 🔐 2. Cryptographic Component Detection

The scanner searches firmware files for known cryptographic components.

Example:

```cpp
AES256_encrypt(data, key);

SHA256(data);

RSA_verify(signature);

MD5(data);
```

The scanner identifies the cryptographic mechanisms and adds them to the project inventory.

---

## 📦 3. Cryptographic Inventory

Detected components are represented as objects.

Example:

```text
Algorithm: AES-256
Type: Symmetric Encryption
Key Size: 256
Source: communication.cpp
```

This allows the system to maintain structured information about every detected cryptographic component.

---

# ⚠️ 4. Risk Assessment

After detecting an algorithm, FirmwareCBOM evaluates its security status.

Example:

| Algorithm   | Risk     | Status     |
| ----------- | -------- | ---------- |
| 🟢 AES-256  | LOW      | Safe       |
| 🟢 SHA-256  | LOW      | Safe       |
| 🟡 AES-128  | LOW      | Acceptable |
| 🟠 RSA-2048 | MEDIUM   | Classical  |
| 🔴 SHA-1    | HIGH     | Weak       |
| 🚨 MD5      | CRITICAL | Weak       |
| 🚨 DES      | CRITICAL | Weak       |

The system separates two important responsibilities:

```text
Crypto Scanner
      │
      └── "What did I find?"

           ↓

Crypto Database
      │
      └── "What does it mean?"
```

---

# 📋 5. CBOM Generation

FirmwareCBOM generates a structured CBOM describing the cryptographic components detected in firmware.

Example:

```json
{
  "firmware": "SmartSensor_v1.2",
  "cryptography": [
    {
      "algorithm": "AES-256",
      "type": "encryption",
      "risk": "LOW"
    },
    {
      "algorithm": "SHA-1",
      "type": "hash",
      "risk": "HIGH"
    }
  ]
}
```

This makes the cryptographic information easier to inspect and use for security assessment.

---

# ⚛️ 6. Post-Quantum Readiness

A major future direction of FirmwareCBOM is **Post-Quantum Cryptography (PQC)**.

Some classical public-key algorithms may become vulnerable to future quantum computing threats.

FirmwareCBOM can therefore classify cryptographic algorithms according to their quantum-readiness.

Example:

```text
Algorithm       Quantum Risk
──────────────────────────────
RSA-2048        🔴 HIGH
ECDSA           🔴 HIGH
AES-256         🟠 MODERATE
SHA-256         🟢 LOW
```

The system can then provide migration recommendations.

```text
RSA
 │
 ▼
PQC Migration
 │
 └──► ML-KEM / ML-DSA
```

---

# 🧠 Firmware Cryptographic Health Index

## FCHI

One of the proposed research components of FirmwareCBOM is the:

### **Firmware Cryptographic Health Index**

**FCHI**

The index provides an overall indication of the cryptographic health of firmware.

It can consider factors such as:

```text
┌──────────────────────────────┐
│ Firmware Cryptographic       │
│ Health Index (FCHI)          │
├──────────────────────────────┤
│                              │
│ 🔐 Algorithm Security        │
│ 🔑 Key Strength              │
│ ⚠️ Deprecated Algorithms     │
│ 📦 Crypto Components         │
│ ⚛️ PQC Readiness             │
│ 🌐 Component Exposure        │
│                              │
└──────────────────────────────┘
```

Conceptually:

```text
FCHI = f(A, K, D, P, E)
```

Where:

* **A** = Algorithm security
* **K** = Key-strength factor
* **D** = Deprecated algorithm factor
* **P** = Post-quantum readiness
* **E** = Exposure factor

---

# 🏗️ System Architecture

The overall architecture is designed around Object-Oriented Programming.

```text
                         FirmwareCBOM
                              │
             ┌────────────────┼────────────────┐
             │                │                │
             ▼                ▼                ▼
     FirmwareLoader     CryptoScanner    ReportGenerator
                              │
                              ▼
                       CryptoComponent
                              │
                    ┌─────────┼─────────┐
                    │         │         │
                    ▼         ▼         ▼
                   AES       RSA       SHA
                              │
                              ▼
                       RiskAnalyzer
                              │
                              ▼
                      CryptoDatabase
                              │
                              ▼
                       RiskAssessment
```

---

# 💻 Object-Oriented Design

FirmwareCBOM is designed specifically as an OOP project.

## 🧱 Classes

Some of the major classes include:

```text
CryptoAlgorithm
      │
      ├── AES
      ├── RSA
      ├── ECC
      ├── SHA
      ├── ML-KEM
      └── ML-DSA
```

Other major components include:

```text
FirmwareLoader
CryptoScanner
CryptoComponent
CryptoDatabase
RiskAnalyzer
CBOMGenerator
```

---

# 🧬 Inheritance & Polymorphism

The project uses an abstract base class:

```cpp
class CryptoAlgorithm {
public:

    virtual string getName() const = 0;

    virtual string getType() const = 0;

    virtual int getSecurityLevel() const = 0;

    virtual ~CryptoAlgorithm() {}
};
```

Specific algorithms can inherit from it:

```text
             CryptoAlgorithm
                    │
        ┌───────────┼───────────┐
        ▼           ▼           ▼
       AES         RSA         SHA
```

This allows new cryptographic algorithms to be added without changing the entire framework.

---

# 🎯 Strategy Pattern

The project can also use the **Strategy Pattern** for different risk-analysis methods.

```text
              RiskStrategy
                   │
        ┌──────────┼──────────┐
        ▼          ▼          ▼
 BasicRisk    QuantumRisk   IoTRisk
 Strategy      Strategy     Strategy
```

This allows the same firmware to be evaluated using different security models.

---

# 📂 Project Structure

```text
FirmwareCBOM/
│
├── 📁 firmware/
│   ├── sensor.cpp
│   ├── communication.cpp
│   ├── authentication.cpp
│   ├── storage.cpp
│   └── config.txt
│
├── 📁 src/
│   ├── FirmwareLoader
│   ├── CryptoScanner
│   ├── CryptoComponent
│   ├── CryptoDatabase
│   ├── RiskAnalyzer
│   └── CBOMGenerator
│
├── 📁 output/
│   └── generated CBOM / reports
│
├── 📁 tools/
│
├── 📄 main.cpp
├── 📄 README.md
└── 📄 requirements.txt
```

---

# 🔄 How FirmwareCBOM Works

### Step 1️⃣ — Load Firmware

The system receives firmware source files.

```text
📁 Firmware
     ↓
FirmwareLoader
```

### Step 2️⃣ — Scan Firmware

The CryptoScanner searches for known cryptographic patterns.

```text
AES
RSA
SHA
MD5
ECDSA
...
```

### Step 3️⃣ — Create Components

Every detected algorithm becomes a cryptographic component.

```text
CryptoComponent
├── Algorithm
├── Type
├── Key Size
└── Source File
```

### Step 4️⃣ — Check Database

The component is compared against cryptographic security information.

```text
Algorithm
     ↓
CryptoDatabase
     ↓
Risk / Status / Recommendation
```

### Step 5️⃣ — Analyze Risk

RiskAnalyzer assigns a security level.

```text
🟢 LOW
🟡 MEDIUM
🟠 HIGH
🔴 CRITICAL
```

### Step 6️⃣ — Generate CBOM

The final cryptographic inventory is generated.

```text
Firmware
   ↓
CBOM
   ↓
Security Report
```

---

# 🧪 Example Firmware

A simulated firmware file might contain:

```cpp
#include <crypto.h>

void authenticate()
{
    RSA_verify(signature);

    SHA256(data);
}

void encryptData()
{
    AES256_encrypt(data, key);
}
```

FirmwareCBOM can identify:

```text
🔍 Detected Components

┌────────────┬─────────────────────┐
│ Algorithm  │ Type                │
├────────────┼─────────────────────┤
│ RSA        │ Public Key Crypto   │
│ SHA-256    │ Hash                │
│ AES-256    │ Encryption          │
└────────────┴─────────────────────┘
```

---

# 📊 Example Security Report

```text
╔══════════════════════════════════════╗
║       FIRMWARE SECURITY REPORT       ║
╠══════════════════════════════════════╣
║ Firmware: SmartSensor_v1.2           ║
║                                      ║
║ Components Detected: 4               ║
║                                      ║
║ 🟢 AES-256       LOW                 ║
║ 🟢 SHA-256       LOW                 ║
║ 🟠 RSA-2048      MEDIUM              ║
║ 🔴 SHA-1         HIGH                ║
║                                      ║
║ Overall Status: NEEDS REVIEW         ║
╚══════════════════════════════════════╝
```

---

# 🛠️ Technology Stack

| Technology            | Purpose                           |
| --------------------- | --------------------------------- |
| 💻 **C++**            | Main programming language         |
| 🧱 **OOP**            | System architecture               |
| 📂 **File Handling**  | Firmware/source analysis          |
| 📦 **STL**            | Data structures & utilities       |
| 🔐 **Cryptography**   | Algorithm identification          |
| 🛡️ **Cybersecurity** | Risk assessment                   |
| 📋 **CBOM**           | Cryptographic inventory           |
| ⚛️ **PQC**            | Future quantum-readiness analysis |

---

# 🎓 OOP Concepts Demonstrated

FirmwareCBOM provides practical implementation of:

* 🧱 Classes & Objects
* 🔒 Encapsulation
* 🧬 Inheritance
* 🔄 Polymorphism
* 🎯 Abstraction
* 🏗️ Constructors
* 📦 STL Containers
* ⚠️ Exception Handling
* 🎯 Strategy Pattern
* 🏭 Factory Pattern

---

# 📈 Development Roadmap

## 🟢 Version 1 — Basic Project

```text
Source Firmware
      ↓
Crypto Scanner
      ↓
Crypto Inventory
      ↓
Simple CBOM
```

Focus:

* Classes
* Objects
* Encapsulation
* File handling
* STL
* Constructors

---

## 🟡 Version 2 — OOP Framework

```text
Firmware
    ↓
Scanner
    ↓
Crypto Objects
    ↓
Risk Analyzer
    ↓
CBOM Generator
```

Add:

* Inheritance
* Polymorphism
* Abstract classes
* Factory Pattern
* Strategy Pattern
* Exception handling

---

## 🔴 Version 3 — Research Prototype

```text
Crypto Risk Score
        +
FCHI
        +
Quantum Readiness
        +
PQC Migration
```

This turns the basic academic project into a more advanced research prototype.

---

# 🔬 Experimental Evaluation

For research evaluation, FirmwareCBOM can be tested against a controlled collection of simulated firmware projects.

Example:

```text
Firmware-01
Firmware-02
Firmware-03
...
Firmware-50
```

Each firmware sample can contain different combinations of:

```text
AES
RSA
ECC
SHA
MD5
SHA-1
DES
```

The system can then evaluate:

| Metric                  | Purpose                         |
| ----------------------- | ------------------------------- |
| 🎯 Detection Accuracy   | Correctly identified algorithms |
| ❌ False Positives       | Incorrect detections            |
| 🔎 False Negatives      | Missed components               |
| ⏱️ Scanning Time        | Performance                     |
| 💾 Memory Usage         | Resource consumption            |
| 📋 CBOM Generation Time | Report performance              |
| ⚠️ Risk Classification  | Security assessment             |
| ⚛️ PQC Recommendations  | Migration assessment            |

---

# 📊 Research Comparison

The proposed evaluation can compare:

```text
┌─────────────────────┐
│   Basic Scanner     │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│    FirmwareCBOM     │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│ FirmwareCBOM + FCHI │
└─────────────────────┘
```

This provides a way to evaluate how additional security-analysis layers improve the system.

---

# ⚠️ Current Scope & Limitations

The initial version focuses on **source-level or simulated firmware analysis**.

It does **not** attempt to perform complete binary reverse engineering.

Therefore, the project should not claim to be a complete firmware CBOM extractor in its initial form.

Future versions can introduce:

```text
ELF Scanner
     ↓
Binary Scanner
     ↓
Firmware Analysis
     ↓
Disassembly
     ↓
Advanced CBOM
```

---

# 🚀 Future Scope

The architecture is designed so that advanced modules can be added later.

### 🔍 Advanced Firmware Analysis

* Binary firmware analysis
* `.ELF` scanning
* `.BIN` analysis
* `.HEX` analysis
* Firmware disassembly
* Symbol analysis

### 🔐 Advanced Cryptographic Analysis

* More algorithms
* Key-size analysis
* Cryptographic dependency mapping
* Advanced risk scoring

### ⚛️ Post-Quantum Security

* PQC readiness assessment
* Quantum vulnerability classification
* Migration recommendations
* ML-KEM integration
* ML-DSA integration

### 📊 Security Intelligence

* Firmware Cryptographic Health Index
* Advanced security reports
* Risk visualization
* Comparative firmware analysis

---

# 🎯 Project Goals

The main goals of FirmwareCBOM are:

```text
🔍 Identify
    ↓
📦 Inventory
    ↓
⚠️ Assess
    ↓
📋 Document
    ↓
🛡️ Improve
```

Specifically:

1. 🔍 Detect cryptographic components.
2. 📦 Create a cryptographic inventory.
3. ⚠️ Identify weak or deprecated algorithms.
4. 📊 Assess firmware cryptographic risk.
5. 📋 Generate a CBOM.
6. ⚛️ Evaluate post-quantum readiness.
7. 🚀 Provide a foundation for future firmware security research.

---

# 📚 Project Research Direction

The eventual research direction of the project is:

### **FirmwareCBOM: An Object-Oriented Framework for Cryptographic Inventory, Risk Assessment, and Post-Quantum Readiness of IoT Firmware**

Potential contributions include:

* 🧱 An extensible OOP architecture
* 🔍 Automated cryptographic component identification
* 📊 Firmware Cryptographic Health Index
* ⚛️ Quantum-readiness assessment
* 🔄 PQC migration recommendations
* 🧪 Experimental evaluation using controlled firmware samples

---

# 👥 Project Type

🎓 **Academic / BTech Project**

### Domains

```text
💻 Computer Science
        +
🔐 Cybersecurity
        +
⚙️ Firmware
        +
🌐 IoT
        +
⚛️ Post-Quantum Cryptography
```

---

# 🛡️ Security Philosophy

> **You cannot secure what you cannot see.**

FirmwareCBOM aims to make the cryptographic components hidden inside firmware **visible, identifiable, and assessable**.

---

# 🌈 Final Architecture

```text
                    🔐 FirmwareCBOM
                          │
                          ▼
                  📁 Firmware Input
                          │
                          ▼
                 🔍 Firmware Scanner
                          │
                          ▼
                🧩 Crypto Components
                          │
                          ▼
                 🗄️ Crypto Database
                          │
                          ▼
                  ⚠️ Risk Analyzer
                          │
             ┌────────────┴────────────┐
             ▼                         ▼
       📊 Risk Score             ⚛️ PQC Readiness
             │                         │
             └────────────┬────────────┘
                          ▼
                    📋 CBOM Report
                          │
                          ▼
                 🛡️ Security Insight
```

---

## ⭐ FirmwareCBOM

### 🔐 Discover Cryptography

### 📦 Build the CBOM

### ⚠️ Assess the Risk

### ⚛️ Prepare for the Quantum Future

<p align="center">

**Built with C++ • Object-Oriented Design • Cybersecurity • IoT**

</p>

---

<p align="center">

⭐ If you find this project interesting, consider giving it a star!

</p>
