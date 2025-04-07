#  Huffman Coding – Lossless Text Compression Project

**Final Project | Indiana State University**  
**By:** Shri Padmavathi Manoharan & Venkata Parupudi

---

## Overview

This project implements **Huffman Coding**, a well-known algorithm for **lossless data compression**. The main objective is to compress and decompress large text files efficiently using **C++**, applying frequency-based binary encoding for characters.

The project is executed on both **macOS (Xcode)** and **Linux (CentOS on Google Cloud VM)** environments.

---

## Features

- Character frequency calculation  
- Huffman Tree construction  
- Binary code generation for each character  
- Text compression into `.hzip` file format  
- Decompression to recover original text  
- Supports large files  
- Runs on macOS and Linux

---

##  File Structure

```
HuffmanCoding/
├── Compression/
│   ├── src/
│   │   ├── main.cpp
│   │   └── huffman.cpp
│   ├── test.txt
│   ├── output.hzip
│   └── Makefile
├── Decompression/
│   ├── src/
│   │   ├── main.cpp
│   │   └── huffman.cpp
│   ├── input.hzip
│   ├── output.txt
│   └── Makefile
```

---

##  How to Run

###  On macOS (Xcode)

1. Open project in Xcode  
2. Update scheme arguments with:
   ```
   -f /path/to/test.txt -o /path/to/output.hzip -s
   ```
3. Build and run for compression or decompression.

---

###  On Linux (GCP / Terminal)

1. Compile:
   ```bash
   g++ src/main.cpp src/huffman.cpp -o compress
   ./compress -f test.txt -o output.hzip -s
   ```

2. Decompress:
   ```bash
   g++ src/main.cpp src/huffman.cpp -o decompress
   ./decompress -f output.hzip -o output.txt -s
   ```

---

## Sample Results

- **Input File:** 500 KB plain text  
- **Compressed Output:** ~180 KB  
- **Decompressed Output:** Perfect match with original text ✅

---

##  Contributors

- **Shri Padmavathi Manoharan** – Compression module implementation  
- **Venkata Parupudi** – Decompression module implementation

