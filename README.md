**Custom Programming Language Interpreter**
Overview
This project is a simple interpreter for a custom programming language, implemented in C++. The language supports basic arithmetic operations, variable assignments, and print statements. It also includes functionality for parsing and executing expressions, handling variables, and outputting results.
Features
- Variable Assignments: Assign values to variables using standard syntax (e.g., `x = 10 + 5;`).
- Arithmetic Operations: Support for addition, subtraction, multiplication, and division (e.g., `y = 3 * (2 + 4);`).
- Print Statements: Output the value of expressions and variables (e.g., `print(x);`).
- Custom Grammar: Defined using BNF for flexibility and extendability.
Getting Started
Prerequisites
 - A C++ compiler supporting C++14 or later (e.g., GCC, Clang). - CMake (optional, for building the project). - Git (optional, for version control). 
Project Structure
 . ├── src │   ├── main.cpp        # Entry point of the interpreter │   ├── lexer.cpp       # Lexer implementation │   ├── parser.cpp      # Parser implementation │   ├── ast.hpp         # AST node definitions │   ├── token.hpp       # Token type and structure definitions ├── include             # Header files (optional) │   ├── Lexer.hpp │   ├── Parser.hpp ├── tests               # Unit tests (optional) ├── CMakeLists.txt      # CMake build configuration (optional) └── README.md           # Project documentation 
Installation
Clone the repository:
git clone https://github.com/yourusername/your-repo-name.git cd your-repo-name
Compile the project:
g++ -std=c++14 -o my_program src/main.cpp src/lexer.cpp src/parser.cpp -Iinclude
Alternatively, if using CMake:
mkdir build cd build cmake .. make
Usage
Create a source file containing your custom language code, such as `source.txt`:
x = 10 + 5; print(x);
Run the interpreter with the source file as an argument:
./my_program source.txt
Expected output:
15
Extending the Language
The language can be extended by modifying the grammar and updating the lexer and parser components:
1. Grammar Updates: Modify the BNF grammar to introduce new syntax or features.
2. Lexer Updates: Adjust the lexer to recognize new tokens.
3. Parser Updates: Extend the parser to handle new syntax rules and generate appropriate AST nodes.

Contact
 For any questions, feel free to contact: - Abhijeet Jha: (mail id: abhijeetjha911@gmail.com) - GitHub: [Abhijeetcode911]((https://github.com/Abhijeetcode911)) 
