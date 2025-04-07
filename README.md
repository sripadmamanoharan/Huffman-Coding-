Huffman Coding – Final Project
Lossless Text Compression & Decompression using C++

Overview
This project implements the Huffman Coding algorithm for compressing and decompressing text files. It is a lossless data compression method where frequently occurring characters are assigned shorter binary codes.

Built using C++, the project includes two main modules:

Compression

Decompression

Execution was done on:

macOS using Xcode

Linux (CentOS) on Google Cloud Platform (GCP)

Features
Calculates character frequencies in the input file

Builds a Huffman tree for optimal binary encoding

Encodes text into compressed .hzip format

Decodes .hzip back to original text

Works with large text files

Cross-platform: macOS and Linux

Technologies Used
C++

Xcode (macOS)

g++ Compiler (Linux)

Makefile for build automation

Google Cloud Platform (GCP)

CentOS

File Structure
css
Copy
Edit
Compression/
├── main.cpp
├── huffman.cpp
├── test.txt
├── output.hzip
├── Makefile

Decompression/
├── main.cpp
├── huffman.cpp
├── input.hzip
├── output.txt
├── Makefile
