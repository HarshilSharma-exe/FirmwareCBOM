# FirmwareCBOM — Architecture

## Pipeline

```
firmware source files
        │
        ▼
  FirmwareLoader (directory traversal, part of CryptoScanner)
        │
        ▼
  CryptoScanner ──► CryptoComponent objects
        │
        ▼
  RiskAnalyzer ◄──► CryptoDatabase
        │
        ▼
  CBOMGenerator ──► cbom.json + report.txt
```

## Why the responsibilities are separated

A common beginner mistake is to put file reading, keyword matching, risk lookup, and
JSON output all inside `main()`. FirmwareCBOM deliberately separates these into distinct
classes with single responsibilities:

- **`CryptoScanner`** only knows how to find keywords in text. It has no opinion about
  whether an algorithm is safe.
- **`CryptoDatabase`** only knows facts about algorithms (risk score, deprecation,
  recommendation). It has no idea what firmware is being scanned.
- **`RiskAnalyzer`** combines the two: it takes what the scanner found and asks the
  database what it means, then produces a verdict.
- **`CBOMGenerator`** only knows how to serialize a list of already-analyzed components.

This separation means each class can be tested, replaced, or extended independently.
For example, adding binary firmware support later only requires a new scanner
implementation (e.g. `ELFScanner`) — the database, analyzer, and generator stay unchanged.

## Firmware Cryptographic Health Index (FCHI)

The current implementation computes FCHI as:

```
FCHI = 100 - normalize(average_risk_score) * 100
```

where `average_risk_score` is the mean of each detected component's 1–5 risk score from
the `CryptoDatabase`, normalized to a 0.0–1.0 range. This is intentionally simple for the
MVP. The research-stage version described in the original project proposal extends this to:

```
FCHI = f(A, K, D, P, E)
```

where `A` = algorithm security, `K` = key-strength factor, `D` = deprecated-algorithm
factor, `P` = post-quantum readiness, `E` = exposure factor.

## Planned extensions (see README roadmap)

- Polymorphic `CryptoAlgorithm` hierarchy (`AES`, `RSA`, `ECC`, `SHA`, `MLKEM`, `MLDSA`)
- `RiskStrategy` Strategy-pattern hierarchy for evaluating the same firmware under
  different security models (basic / quantum / IoT-specific)
- Binary firmware analysis (`ELFScanner`, `BinaryScanner`)
- 
