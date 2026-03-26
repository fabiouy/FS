# File System Emulator 🖥️

A DOS-style file system emulator with command-line interface, built in C++. This project simulates fundamental file system operations including directory navigation, file creation/deletion, and basic file management.

## 📋 Overview

This is an **Operating Systems** educational project that emulates a hierarchical file system similar to DOS. It provides a command-line interface where users can interact with a virtual file system, perform common operations, and understand how operating systems manage files and directories.

## ✨ Features

- 📁 **Directory Navigation** - Create, delete, and navigate directories
- 📄 **File Management** - Create and delete files
- 🔍 **Directory Listing** - View contents of directories
- 📍 **Path Management** - Handle absolute and relative paths
- 💾 **In-Memory Storage** - File system stored in memory
- 🖱️ **Interactive CLI** - User-friendly command-line interface

## 🛠️ Build Instructions

### Prerequisites
- C++ Compiler (GCC, Clang, or MSVC)
- C++17 or later

### Compilation

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o fs_emulator
```

### Running

```bash
./fs_emulator
```

## 📖 Usage

Commands:
- mkdir <directory> - Create a new directory
- cd <directory> - Change current directory
- ls - List directory contents
- touch <filename> - Create a new file
- rm <filename> - Delete a file
- exit - Exit the emulator

## 📁 Project Structure

- main.cpp - Main program
- FS.h - File system header
- README.md - Documentation

## 🔧 Technical Details

- Language: C++17
- Data Structures: Vectors and maps for file/directory management
- Memory: In-memory file system representation

## 📚 Educational Value

Learn about file system architecture and OS concepts.

## 👨‍💼 Author

Fabio Ramirez (fabiouy) - December 2020

## 📄 License

Educational and learning purposes.

Happy Learning! 🎓