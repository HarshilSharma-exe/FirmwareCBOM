# 🛡️ FirmwareCBOM

### 🔐 Cryptographic Bill of Materials (CBOM) Generation & Risk Assessment for IoT Firmware

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=rect&color=0:0F2027,50:203A43,100:2C5364&height=180&section=header&text=FirmwareCBOM&fontSize=48&fontColor=55E6C1&animation=fadeIn&fontAlignY=45&desc=Discover%20Cryptography.%20Build%20the%20CBOM.%20Assess%20Security%20Risk.&descSize=16&descAlignY=72" width="100%" alt="FirmwareCBOM project banner"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++17"/>
  <img src="https://img.shields.io/badge/Paradigm-OOP%20(4%20Pillars)-7C3AED?style=for-the-badge" alt="OOP"/>
  <img src="https://img.shields.io/badge/Security-NIST%20Standards-0F766E?style=for-the-badge" alt="NIST"/>
  <img src="https://img.shields.io/badge/Output-JSON%20CBOM-EA580C?style=for-the-badge" alt="JSON"/>
  <img src="https://img.shields.io/badge/Status-Fully%20Functional-10B981?style=for-the-badge" alt="Status"/>
</p>

---

## 🌟 Project Overview

**FirmwareCBOM** is an educational, object-oriented C++17 framework designed to inspect IoT firmware source-code files, identify recognizable cryptographic algorithms, maintain an organized database of cryptographic security standards, evaluate security risks using explainable rules, and generate a standardized JSON **Cryptographic Bill of Materials (CBOM)** report.

### Core Processing Pipeline

```
[FirmwareLoader] ──> Reads source code file safely (Abstraction)
       │
       ▼
[CryptoScanner]  ──> Scans text & extracts cryptographic references (Encapsulation)
       │
       ▼
[CryptoComponent]──> Shared data structure for each detection
       │
       ▼
[CryptoDatabase] ──> Queries authoritative guidance: NIST / RFC (Information Hiding)
       │
       ▼
[RiskAnalyzer]   ──> Evaluates security risks via Polymorphic Rules Engine (Polymorphism)
       │
       ▼
[CBOMGenerator]  ──> Serializes inventory & findings to valid JSON (RFC 8259)
       │
       ▼
[cbom_report.json]
```

---

## 👥 Equal 4-Member Division & Viva Responsibilities

The project is equally distributed among all four team members (**Navneet**, **Harshil**, **Aditya**, and **Shivansh**). Each member owns an essential feature, writes approximately equal lines of code, and has their own **Object-Oriented Programming (OOP) concepts** to defend in front of the teacher:

| Member | Module & Feature | Assigned Files | OOP Concepts to Defend |
|---|---|---|---|
| **Navneet** | **Loader Subsystem & Core Pipeline** | `include/BaseLoader.h`<br>`include/FirmwareLoader.h`<br>`src/FirmwareLoader.cpp`<br>`main.cpp`<br>`tests/loader_tests.cpp` | **Abstraction & Inheritance:**<br>Created abstract base class `BaseLoader` with pure virtual method `loadFile()`, extended by `FirmwareLoader`. Coordinates high-level pipeline. |
| **Harshil** | **Scanner & Pattern Matching Engine** | `include/BaseScanner.h`<br>`include/CryptoScanner.h`<br>`src/CryptoScanner.cpp`<br>`tests/scanner_tests.cpp` | **Encapsulation & Inheritance:**<br>Extends `BaseScanner`. Encapsulates regex tokenization, boundary detection, line tracking, and key-size parsing. |
| **Aditya** | **NIST Crypto Database & Standardization** | `include/BaseDatabase.h`<br>`include/CryptoDatabase.h`<br>`src/CryptoDatabase.cpp`<br>`tests/database_tests.cpp` | **Encapsulation & Abstraction:**<br>Extends `BaseDatabase`. Encapsulates NIST standards mapping, alias resolver, and case normalization in an anonymous namespace. |
| **Shivansh** | **Polymorphic Risk Engine & CBOM Generator** | `include/RiskRule.h`<br>`include/RiskAnalyzer.h`<br>`src/RiskAnalyzer.cpp`<br>`include/BaseReportGenerator.h`<br>`include/CBOMGenerator.h`<br>`src/CBOMGenerator.cpp`<br>`tests/risk_analyzer_tests.cpp`<br>`tests/report_tests.cpp` | **Runtime Polymorphism & Inheritance:**<br>Implements the Strategy/Rule pattern using an abstract base class `RiskRule` with 5 derived rules and dynamic dispatch (`vtable`). Extends `BaseReportGenerator`. |

---

## 🏛️ All 4 Pillars of OOP (Teacher Defense Guide)

### 1. Encapsulation (Data Hiding & Security)
* **Explained by:** **Harshil & Aditya**
* **In Harshil's module:** `CryptoScanner.cpp` encapsulates regular expression compilation, token boundary detection, and whitespace trimming. Outside code cannot see or corrupt scanner mechanics.
* **In Aditya's module:** `CryptoDatabase.cpp` hides the static hash map of NIST standards and alias normalization inside an anonymous namespace (`namespace { ... }`). External code can only query through the public `findAlgorithm()` method.
* **Const-Correctness:** Member functions that do not alter class state are marked `const` (e.g. `findAlgorithm(...) const`, `assessRisk(...) const`).

### 2. Abstraction (Hiding Complexity Behind Clean Interfaces)
* **Explained by:** **Navneet & Aditya**
* **In Navneet's module:** `BaseLoader.h` exposes a clean interface `loadFile()`. Callers in `main.cpp` do not need to know how file buffers, disk streams, or permissions work.
* **In Aditya's module:** `BaseDatabase.h` abstracts away how cryptographic facts are stored (whether in memory, SQLite, or an API).

### 3. Inheritance (Code Reusability & "is-a" Relationship)
* **Explained by:** **All 4 Members!**
* **Navneet:** `class FirmwareLoader : public BaseLoader`
* **Harshil:** `class CryptoScanner : public BaseScanner`
* **Aditya:** `class CryptoDatabase : public BaseDatabase`
* **Shivansh:** `class LegacyCipherRule : public RiskRule`, `class BrokenHashRule : public RiskRule`, etc., and `class CBOMGenerator : public BaseReportGenerator`

### 4. Polymorphism (Runtime Dynamic Dispatch)
* **Explained by:** **Shivansh**
* **In Shivansh's module (`include/RiskRule.h` and `src/RiskAnalyzer.cpp`):**
  Rules are stored as base pointers: `std::vector<std::unique_ptr<RiskRule>>`. During assessment, `rule->evaluate()` is dynamically resolved via the virtual function table (`vtable`) to the correct derived rule at runtime.

---

## 📜 Cryptographic Standards & Rules Applied

| Algorithm | Category | Starter Guidance & Rule | Severity | Authoritative Reference |
|---|---|---|---|---|
| **AES** | Symmetric Encryption | Modern cipher; requires secure mode (GCM/CCM) and unique IV. Defaults to Manual Review if mode is unstated. | Informational / Manual Review | NIST FIPS 197 / SP 800-38D |
| **DES** | Symmetric Encryption | 56-bit legacy cipher; vulnerable to practical brute-force cracking. | **High** | NIST SP 800-131A Rev. 2 |
| **MD5** | Hash | Collision resistance broken (trivial practical collisions). Unfit for signatures or integrity. | **High** | IETF RFC 6151 / NIST SP 800-131A |
| **SHA-1** | Hash | Weak collision resistance (SHAttered attack). Disallowed for digital signatures. | **Medium** | NIST SP 800-131A Rev. 2 / RFC 6194 |
| **RSA** | Asymmetric Cryptography | Keys < 2048 bits are vulnerable to factorization. Requires OAEP/PSS padding. | **High** (< 2048) / Informational | NIST SP 800-57 Part 1 Rev. 5 |
| **DSA** | Digital Signature | Deprecated for digital signature generation in modern standards. | **Medium** | NIST FIPS 186-5 |
| **ECC** | Asymmetric Cryptography | Elliptic curve cryptography (P-256, Curve25519); parameters must be validated. | Informational / Manual Review | NIST SP 800-186 / FIPS 186-5 |
| **SHA-256** | Hash | Approved 256-bit hash. Note: Digest length is **not** an encryption key. | Informational | NIST FIPS 180-4 |
| **ML-KEM** | Post-Quantum | NIST-standardized module-lattice key-encapsulation mechanism. | Informational | NIST FIPS 203 |
| **ML-DSA** | Post-Quantum | NIST-standardized module-lattice digital signature algorithm. | Informational | NIST FIPS 204 |
| **Unknown** | Unrecognized | Any algorithm not in database is flagged for manual audit rather than assumed safe. | **Manual Review** | Defense-in-depth policy |

---

## 💻 How to Build and Run on macOS / Linux

### 1. Compile the Main Program
```bash
clang++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/*.cpp -o firmwarecbom
```

### 2. Run on Sample Firmware
```bash
./firmwarecbom
```

**Expected Terminal Output:**
```text
Scan completed.
Components detected: 25
Report saved to cbom_report.json
```

---

## 🎯 Live Viva Demonstration (How to Run Different Files)

FirmwareCBOM dynamically scans **any C++ source file** passed as a command-line argument:

```bash
# 1. Test clean code with NO cryptography (Output: 0 components)
./firmwarecbom samples/clean_math.cpp

# 2. Test legacy insecure code (Output: 4 components, DES & MD5 flagged High)
./firmwarecbom samples/insecure_firmware.cpp

# 3. Test modern post-quantum firmware (Output: 4 components, ML-KEM & ML-DSA)
./firmwarecbom samples/modern_firmware.cpp

# 4. Test comprehensive firmware (Output: 25 components)
./firmwarecbom sample.cpp
```

---

## 🧪 How Each Member Runs Their Unit Test in the Viva

When the professor asks each student to run their specific part live:

* **Navneet runs (Loader & Abstraction):**
  ```bash
  clang++ -std=c++17 -Wall -Wextra -Iinclude tests/loader_tests.cpp src/FirmwareLoader.cpp -o test_loader && ./test_loader && rm -f test_loader
  ```
* **Harshil runs (Scanner & Pattern Matching):**
  ```bash
  clang++ -std=c++17 -Wall -Wextra -Iinclude tests/scanner_tests.cpp src/CryptoScanner.cpp -o test_scanner && ./test_scanner && rm -f test_scanner
  ```
* **Aditya runs (Database & NIST Standards):**
  ```bash
  clang++ -std=c++17 -Wall -Wextra -Iinclude tests/database_tests.cpp src/CryptoDatabase.cpp -o test_database && ./test_database && rm -f test_database
  ```
* **Shivansh runs (Risk Engine & Polymorphism):**
  ```bash
  clang++ -std=c++17 -Wall -Wextra -Iinclude tests/risk_analyzer_tests.cpp src/RiskAnalyzer.cpp -o test_risk && ./test_risk && rm -f test_risk
  ```

---

## 📊 Sample Generated JSON Output (`cbom_report.json`)

```json
{
  "schemaVersion": "1.0",
  "components": [
    {
      "algorithmName": "AES",
      "category": "Symmetric Encryption",
      "usage": "Encryption",
      "keySizeBits": 256,
      "sourceFile": "sample.cpp",
      "lineNumber": 18,
      "evidence": "// Reference 1: AES with 256-bit key"
    },
    {
      "algorithmName": "SHA-256",
      "category": "Hash",
      "usage": "Hashing",
      "keySizeBits": null,
      "sourceFile": "sample.cpp",
      "lineNumber": 27,
      "evidence": "// Reference 2: SHA-256 Hash for Secure Boot verification"
    }
  ],
  "findings": [
    {
      "algorithmName": "DES",
      "severity": "High",
      "reason": "DES utilizes an insecure 56-bit effective key length vulnerable to practical brute-force recovery (NIST SP 800-131A).",
      "recommendation": "Deprecate immediately and migrate to AES-128 or AES-256.",
      "sourceFile": "sample.cpp",
      "lineNumber": 42
    },
    {
      "algorithmName": "MD5",
      "severity": "High",
      "reason": "MD5 has severe collision vulnerabilities allowing rapid practical forgery (RFC 6151).",
      "recommendation": "Do not use for security purposes. Migrate immediately to SHA-256 or SHA-3.",
      "sourceFile": "sample.cpp",
      "lineNumber": 37
    }
  ]
}
```

---

## 🎓 Viva Q&A Cheat Sheet

1. **Why `std::optional<int>` instead of `-1` for key size?**
   > *In C++17, `std::optional` explicitly models presence or absence. Hashes (like SHA-256) produce digests and do not use keys. Using `-1` is an unsafe magic number. `std::optional` serializes cleanly to JSON `null`.*
2. **What happens if an unknown cipher is detected?**
   > *`CryptoDatabase` returns `std::nullopt`, and `RiskAnalyzer` assigns `"severity": "Manual Review"`. In security, unknown components must never be assumed safe.*
3. **Where is Polymorphism in your code?**
   > *In `src/RiskAnalyzer.cpp` and `include/RiskRule.h`. An abstract base class `RiskRule` is extended by 5 derived rule classes. `RiskAnalyzer` iterates over `std::vector<std::unique_ptr<RiskRule>>` and invokes `rule->evaluate()` polymorphically via the `vtable`.*

---

<p align="center">
  <b>FirmwareCBOM</b> • <i>Object-Oriented Cryptographic Bill of Materials Framework</i>
</p>
