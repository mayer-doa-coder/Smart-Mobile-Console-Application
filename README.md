# Smart Mobile Console Application

A feature-rich C++ console application that simulates a mobile phone with contact management, messaging, calculator functions, and interactive games.

## Overview

The Smart Mobile Console Application is an object-oriented C++ program that demonstrates various programming concepts including polymorphism, templates, file I/O, and interactive user interfaces. The application provides a menu-driven interface for managing contacts, sending messages, performing calculations, and playing games.

## Features

### Contact Management
- **Add Contacts**: Store contact information with names and phone numbers
- **List Contacts**: View all saved contacts with their details
- **Persistent Storage**: Save contacts to files and load them later
- **Message History**: Track all messages sent and received per contact

### Messaging System
- **Send Messages**: Send text messages between contacts
- **View Messages**: Display message history for any contact
- **Automatic Message Storage**: Messages are automatically saved for both sender and recipient

### Calculator Functions
- **Basic Calculator**: Performs addition operations
- **Scientific Calculator**: Performs multiplication operations
- **Result History**: Store and display calculation results with descriptions
- **Switchable Modes**: Change between calculator types on-the-fly

### Interactive Games
- **Tic-Tac-Toe**: Classic two-player board game
- **Number Guessing Game**: Guess a random number between 1 and 100
- **Rock, Paper, Scissors**: Play against the computer with replay option

### File Operations
- **Save Contacts**: Export contact list to text files
- **Load Contacts**: Import contacts from previously saved files
- **Custom File Naming**: Choose your own filenames for data persistence

## Architecture

### Design Patterns & Principles

**Object-Oriented Design**
- Encapsulation of data and methods within classes
- Abstraction through pure virtual base classes
- Polymorphism for games and calculators
- Friend classes for controlled access to private members

**Template Programming**
- Generic `Pair<T1, T2>` template class for storing key-value pairs
- Type-safe storage of calculator results

**Inheritance Hierarchy**
```
Game (Abstract Base)
├── TicTacToe
├── NumberGuessingGame
└── RockPaperScissorsGame

Calculator (Abstract Base)
├── BasicCalculator
└── ScientificCalculator
```

**Key Classes**
- `MobilePhone`: Central controller managing all phone features
- `Contact`: Represents a contact with messaging capabilities
- `Message`: Encapsulates message data
- `Pair<T1, T2>`: Generic template for storing paired data
- `Game`: Abstract base class for all games
- `Calculator`: Abstract base class for calculator types

## Data Flow

```
User Input → Main Menu
    ↓
MobilePhone Controller
    ↓
┌────────────┬──────────────┬────────────┬──────────┐
│  Contacts  │   Messages   │ Calculator │  Games   │
└────────────┴──────────────┴────────────┴──────────┘
    ↓              ↓              ↓           ↓
File I/O      Message Store   Results     Game Logic
```

**Contact Management Flow**
1. User adds contact → Stored in vector
2. User saves contacts → Written to file via `operator<<`
3. User loads contacts → Read from file via `operator>>`

**Messaging Flow**
1. Sender sends message → Message object created
2. Message added to sender's history
3. Message delivered to recipient's history
4. Messages persisted in memory (not file)

**Calculator Flow**
1. User selects calculator type → Polymorphic pointer set
2. User inputs operands → `calculate()` called
3. Result computed → Stored in `Pair<string, double>` vector

## Tech Stack

- **Language**: C++ (C++11 or later recommended)
- **Standard Library Components**:
  - `iostream`: Input/output operations
  - `vector`: Dynamic arrays for storage
  - `fstream`: File I/O operations
  - `string`: String handling
  - `ctime`: Random number seeding
  - `cstdlib`: Random number generation

- **Compiler Compatibility**: GCC, Clang, MSVC
- **Platform**: Cross-platform (Windows, Linux, macOS)

## Project Structure

```
Smart-Mobile-Console-Application/
│
├── main.cpp              # Main application file with all classes and logic
├── oi.cpp                # Additional implementation file
├── output/               # Directory for output files
│   ├── oi.txt           # Output file
│   └── taw.txt          # Output file
└── README.md            # This file
```

### Code Organization

**main.cpp** contains:
- Template classes (`Pair`)
- Core classes (`Message`, `Contact`, `MobilePhone`)
- Abstract base classes (`Game`, `Calculator`)
- Concrete implementations (`TicTacToe`, `NumberGuessingGame`, `RockPaperScissorsGame`)
- Calculator implementations (`BasicCalculator`, `ScientificCalculator`)
- Main menu loop and user interface

## Prerequisites

### Required
- **C++ Compiler** with C++11 support or later:
  - GCC 4.8.1+
  - Clang 3.3+
  - MSVC 2015+
- **Standard C++ Library**

### Optional
- **Make** or **CMake** for build automation
- **Git** for version control

## Quick Start

### Windows (Using MinGW/GCC)
```powershell
# Compile the program
g++ -std=c++11 main.cpp -o SmartMobile.exe

# Run the application
.\SmartMobile.exe
```

### Windows (Using MSVC)
```powershell
# Compile with MSVC
cl /EHsc /std:c++14 main.cpp /Fe:SmartMobile.exe

# Run the application
.\SmartMobile.exe
```

### Linux/macOS
```bash
# Compile the program
g++ -std=c++11 main.cpp -o SmartMobile

# Run the application
./SmartMobile
```

## Configuration

### Customization Options

**Random Number Generation**
- Modify `NumberGuessingGame` constructor to change the range:
  ```cpp
  numberToGuess = rand() % 100 + 1;  // Change 100 to your max value
  ```

**Calculator Operations**
- Extend `BasicCalculator` or `ScientificCalculator` to add more operations
- Implement additional calculator types by inheriting from `Calculator`

**Game Difficulty**
- Tic-Tac-Toe: Implement AI for single-player mode
- Number Guessing: Add attempt limits or difficulty levels

**File Paths**
- Default: User-specified filenames
- Modify `saveContactsToFile()` and `loadContactsFromFile()` for default paths

## Building the Project

### Using G++ (Recommended)
```bash
# Basic compilation
g++ -std=c++11 main.cpp -o SmartMobile

# With optimizations
g++ -std=c++11 -O2 main.cpp -o SmartMobile

# With debugging symbols
g++ -std=c++11 -g main.cpp -o SmartMobile

# With warnings enabled
g++ -std=c++11 -Wall -Wextra main.cpp -o SmartMobile
```

### Using CMake (Optional)

Create a `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.10)
project(SmartMobile)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SmartMobile main.cpp oi.cpp)
```

Build commands:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Using Makefile (Optional)

Create a `Makefile`:
```makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = SmartMobile
SOURCES = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all clean
```

Build:
```bash
make
```

### Sample Test Session
```
1. Add Contact: "John" / "123-456-7890"
2. Add Contact: "Jane" / "098-765-4321"
3. List Contacts (verify both appear)
4. Send Message: John → Jane: "Hello!"
5. View Messages for Jane (verify message received)
6. Set Basic Calculator
7. Calculate: 5 + 3 = 8
8. Save Contacts to "contacts.txt"
9. Exit and restart
10. Load Contacts from "contacts.txt"
11. Verify contacts restored
```

## Contributing

Contributions are welcome! Here's how you can help:

### Reporting Bugs
1. Check if the bug has already been reported
2. Create a detailed issue with:
   - Steps to reproduce
   - Expected vs actual behavior
   - System information (OS, compiler version)

### Suggesting Enhancements
1. Open an issue describing the enhancement
2. Explain the use case and benefits
3. Provide examples if possible

### Code Contributions
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Make your changes following the coding style
4. Test thoroughly
5. Commit with clear messages (`git commit -m 'Add AmazingFeature'`)
6. Push to your branch (`git push origin feature/AmazingFeature`)
7. Open a Pull Request

### Coding Standards
- Follow C++ best practices
- Use meaningful variable and function names
- Add comments for complex logic
- Maintain consistent indentation (4 spaces)
- Avoid memory leaks (proper resource management)

### Enhancement Ideas
- Add SMS timestamp functionality
- Implement contact search/filter
- Add more calculator operations (subtraction, division, power, etc.)
- Create additional games (Hangman, Snake, etc.)
- Add data encryption for saved files
- Implement contact grouping/categories
- Add multimedia message support simulation
- Create unit tests framework
- Add configuration file support

## Troubleshooting

### Compilation Issues

**Problem**: `error: 'nullptr' was not declared in this scope`
```
Solution: Use C++11 or later compiler flag
g++ -std=c++11 main.cpp -o SmartMobile
```

**Problem**: Linker errors
```
Solution: Ensure all source files are included in compilation
g++ -std=c++11 main.cpp oi.cpp -o SmartMobile
```

**Problem**: `cannot open source file "iostream"`
```
Solution: Ensure C++ standard library is properly installed
```

### Runtime Issues

**Problem**: File not found when loading contacts
```
Solution: 
- Verify the file exists in the current directory
- Use absolute paths if needed
- Check file permissions
```

**Problem**: Random number generation produces same sequence
```
Solution: The program uses time-based seeding. If running multiple 
instances quickly, they may produce similar sequences. This is 
normal behavior.
```

**Problem**: Input buffer issues after numeric input
```
Solution: The program uses cin.ignore() to clear buffer. If issues 
persist, check that all input operations properly clear the buffer.
```

**Problem**: Messages not appearing after sending
```
Solution: Ensure both sender and recipient contacts exist with exact 
name matching (case-sensitive).
```

### Performance Considerations

- **Large Contact Lists**: Linear search is used. For very large lists (1000+ contacts), consider implementing indexed search.
- **Memory Usage**: All contacts and messages are stored in memory. For production use, consider database integration.
- **File Size**: Text-based storage can be inefficient for large datasets. Consider binary format for optimization.

## License

This project is provided as-is for educational purposes. You are free to:
- Use the code for learning
- Modify and extend functionality
- Share with others
- Use in academic projects

**Note**: If you plan to use this in a commercial application, please add an appropriate open-source license (MIT, GPL, Apache, etc.) to the repository.

## Contact & Support

### Getting Help
- Open an issue for bugs or questions
- Check existing issues for similar problems
- Review the code comments for implementation details

### Project Maintainers
- For questions about specific implementations, refer to inline code documentation
- For feature requests, open an issue with detailed description

### Community
- Share your enhancements and modifications
- Help others by answering questions in issues
- Contribute to documentation improvements

## Acknowledgments

### Design Inspiration
- Classic mobile phone interfaces
- Console-based application design patterns
- Object-oriented programming principles

### Educational Value
This project demonstrates:
- **OOP Principles**: Encapsulation, inheritance, polymorphism
- **Template Programming**: Generic programming with C++ templates
- **Memory Management**: Proper use of pointers and dynamic allocation
- **File I/O**: Reading and writing structured data
- **User Interface**: Console-based menu systems
- **Data Structures**: Vectors for dynamic collections
- **Operator Overloading**: Stream operators for custom types

### Built With
- C++ Standard Library
- Object-Oriented Design Patterns
- Modern C++ best practices

---

**Version**: 1.0  
**Last Updated**: December 30, 2025  
**Status**: Active Development

---

*For more information about C++ programming and best practices, visit [cppreference.com](https://en.cppreference.com/) and [isocpp.org](https://isocpp.org/).*
