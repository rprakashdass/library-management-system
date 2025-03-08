# Library Management System

## 📌 Overview
The **Library Management System** is a C++ application that allows users to efficiently manage books and members within a library. It provides features for adding, removing, searching, and issuing books to members, ensuring a streamlined library experience.

## ✨ Features
- 📖 **Book Management**: Add, remove, and search books by ID or title.
- 🧑‍💼 **Member Management**: Add, remove, and search members by ID or name.
- 🔄 **Book Issuing & Returning**: Issue books to members and return them.
- 📚 **View All Records**: Display all books and members in the library.
- 🔍 **Search Functionality**: Find books and members using various criteria.

## 🛠️ Technologies Used
- **C++**: Core programming language.
- **Standard Template Library (STL)**: Utilized for efficient data structures (`unordered_map`).
- **Object-Oriented Programming (OOP)**: Implemented for modularity and maintainability.

## 🚀 Getting Started
### Prerequisites
Ensure you have the following installed on your system:
- C++ Compiler (G++ / Clang / MSVC)
- Any C++ IDE (VS Code, Code::Blocks, Dev-C++)

### Installation & Compilation
1. **Clone the Repository**
   ```sh
   git clone https://github.com/your-username/library-management-system.git
   cd library-management-system
   ```

2. **Compile the Program**
   ```sh
   g++ -o library library.cpp
   ```

3. **Run the Program**
   ```sh
   ./library
   ```

## 📖 Usage
Upon running the program, the following options will be displayed:
```
Enter 1 for add book
Enter 2 for add member
Enter 3 for issue book to member
Enter 4 for return book from member
Enter 5 to search book by ID
Enter 6 to search book by name
Enter 7 to search member by ID
Enter 8 to search member by name
Enter 9 to delete a book by ID
Enter 10 to delete a book by name
Enter 11 to delete a member
Enter 12 to delete a member by name
Enter 13 to show all books
Enter 14 to show all members
Enter 0 to exit
```
Select an option and follow the prompts to manage the library efficiently.

## 🔗 Future Improvements
- 📝 Implement a database system for persistent storage.
- 🌐 Develop a graphical user interface (GUI) for a better user experience.
- 📊 Add book availability tracking and late return penalties.

## 🤝 Contributing
Contributions are welcome! Feel free to fork the repository and submit pull requests.

## 📄 License
This project is licensed under the **MIT License**.
