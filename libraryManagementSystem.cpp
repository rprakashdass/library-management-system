#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>

/* later for robustness of the system
static int ID_FOR_AUTHOR = 1;

class Author{
    private:
    int authorID;
    std::string authorName;
    std::vector<Book> books;
    public:
    Author() : authorID(ID_FOR_AUTHOR){}
    Author(std::string name) : authorID(ID_FOR_AUTHOR), authorName(name) {}
    Author(std::vector<Book> book) {
        books.emplace_back(book);
    }
};
*/

/*
Book:

Attributes: bookID, title, author, isIssued.
Methods: issueBook(), returnBook() - {not needed as library class is managing}.

Member:

Attributes: memberID, name, booksIssued.
Methods: issueBook(), returnBook() - {not needed as library class is managing}.

Library:

Attributes: books (list of books), members (list of members).
Methods: addBook(), removeBook(), searchBook(), issueBook(), returnBook().

        Add methods to:
        Add/remove books.
        Add members.
        Search for books by ID.
        Issue/return books.
*/

// static variables
static int ID_FOR_BOOK = 111;
static int ID_FOR_MEMBER = 111;

class Book{
private:
    int bookID;
    std::string title;
    std::string author;
    bool isIssued = false;
public:
    Book(std::string title) : bookID(ID_FOR_BOOK++), title(title), author("Unknown") {}
    Book( std::string title, std::string author)
    : bookID(ID_FOR_BOOK++), title(title), author(author) {}
    int getBookID() const {return this->bookID;}
    std::string getBookName() const {return this->title;}
    void issueBook(){isIssued = true;}
    void returnBook(){isIssued = false;}
    void showDetails() const {
        std::cout << "Book ID : " << this->bookID << std::endl;
        std::cout << "Book Title : " << this->title << std::endl;
        std::cout << "Book Author : " << this->author << std::endl;
        std::cout << "Book isAvailable : " << ((!this->isIssued) ? "True" : "False") << std::endl;
    }
    ~Book() {
        std::cout << "Book " << title << " destroyed." << std::endl;
    }
};


class Member{
private:
    int memberID;
    std::string name;
    std::vector<Book*> books;
public:
    Member(std::string name) : memberID(ID_FOR_MEMBER++) ,name(name) {}
    void issueBook(Book* book){
        book->issueBook();
        books.emplace_back(book);
    }
    std::string getName() const {
        return this->name;
    }
    int getMemberID(){return this->memberID;}
    void returnBook(Book* book){
        auto it = find(books.begin(), books.end(), book);
        if(it == books.end()) {
            std::cout << "Book not found!" << std::endl;
            return;
        }
        books.erase(it);
        book->returnBook();
        std::cout << "Book successfully returned by user!" << std::endl;
    }
    void showDetails() const {
        std::cout << "Member ID : " << this->memberID << std::endl;
        std::cout << "Member Title : " << this->name << std::endl;
        std::cout << "Books Issued : ";
        if(books.empty()) std::cout << 0;
        std::cout << std::endl;
        for(Book* book : books){
            book->showDetails();
        }
    }
    ~Member(){
        std::cout << "Member " << name << " destroyed." << std::endl;
    }
};

class Library{
private:
    std::unordered_map<int, Book*> books;
    std::unordered_map<int, Member*> members;
public:
    /* Member methods */
    void addMember(std::string name){
        if(name.empty()) {
            std::cout << "Empty member name entered!\n";
            return;
        }
        Member* member = new Member(name);
        int id = member->getMemberID();
        if(members.find(id) != members.end()){
            std::cout << "Member already Added!" << std::endl;
            return;
        }
        members[id] = (member);
        std::cout << "The " << name << "\'s id is " << id << std::endl;
        std::cout << "Member Successfully added!" << std::endl;
    }
    void removeMemberByName(std::string bookName){
        auto it = searchMemberByName(bookName);
        if(it != members.end()){
            members.erase(it);
            std::cout << "Member successfully removed!" << std::endl;
            return;
        }
        std::cout << "Member not found!" << std::endl;
    }
    void removeMemberById(int id) {
        auto it = members.find(id);
        if(it != members.end()){
            members.erase(it);
            std::cout << "Member successfully removed!" << std::endl;
            return;
        }
        std::cout << "Member not found!" << std::endl;
    }
    std::unordered_map<int, Member*>::iterator searchMemberById(int id){
        auto it = members.find(id);
        if(it != members.end()){
            it->second->showDetails();
        }
        return it;
    }
    std::unordered_map<int, Member*>::iterator searchMemberByName(std::string memberName){
        std::unordered_map<int, Member*>::iterator it;
        for(;it != members.end();it++){
            if(it->second->getName() == memberName){
                break;
            }
        }
        return it;
    }
    void issueBook(int memberId, int bookId){
        auto memberIterator = searchMemberById(memberId);
        if(memberIterator == members.end()){
            std::cout << "Member not found!" << std::endl;
            return;
        }
        auto bookIterator = searchBookById(bookId);
        if(bookIterator == books.end()){
            std::cout << "Book not found!" << std::endl;
            return;
        }
        Book* book = bookIterator->second;
        memberIterator->second->issueBook(book);
        std::cout << "Book Successfully issued to the member!" << std::endl;
    }
    void returnBook(int memberId, int bookId){
        auto memberIterator = searchMemberById(memberId);
        if(memberIterator == members.end()){
            std::cout << "Member not found!" << std::endl;
            return;
        }
        auto bookIterator = searchBookById(bookId);
        if(bookIterator == books.end()){
            std::cout << "Book not found!" << std::endl;
            return;
        }
        Book* book = bookIterator->second;
        memberIterator->second->returnBook(book);
        std::cout << "Book Successfully returned to the library!" << std::endl;
    }
    void showMembers() const {
        if(books.empty()){
            std::cout << "Currently there is no member in library\nAdd some  member\n";
            return;
        }
        std::cout << "Members in library " << std::endl;
        for(auto it: members){
            it.second->showDetails();
        }
    }


    /* Book methods */
    void addBook(std::string title, std::string author){
        if(title.empty()) {
            std::cout << "Empty book title entered!\n";
            return;
        }
        Book* book = (author.empty()) ? new Book(title) : new Book(title, author);
        int id = book->getBookID();
        if(books.find(id) != books.end()){
            std::cout << "Book already Added!" << std::endl;
            return;
        }
        books[id] = (book);
        std::cout << "The " << title << "\'s id is " << id << std::endl;
        std::cout << "Book Successfully added!" << std::endl;
    }
    void removeBookByName(std::string bookName){
        auto it = searchBookByName(bookName);
        if(it != books.end()){
            books.erase(it);
            std::cout << "Book successfully removed!" << std::endl;
            return;
        }
        std::cout << "Book not found!" << std::endl;
    }
    void removeBookById(int id) {
        auto it = books.find(id);
        if(it != books.end()){
            books.erase(it);
            std::cout << "Book successfully removed!" << std::endl;
            return;
        }
        std::cout << "Book not found!" << std::endl;
    }
    std::unordered_map<int, Book*>::iterator searchBookById(int id){
        auto it = books.find(id);
        if(it != books.end()){
            it->second->showDetails();
        }
        return it;
    }
    std::unordered_map<int, Book*>::iterator searchBookByName(std::string bookName){
        std::unordered_map<int, Book*>::iterator it;
        for(;it != books.end();it++){
            if(it->second->getBookName() == bookName){
                break;
            }
        }
        return it;
    }
    void showBooks() const {
        if(books.empty()){
            std::cout << "Currently there is no book in library\nSearch for other book\n";
            return;
        }
        std::cout << "Books in Library " << std::endl;
        for(auto it: books){
            it.second->showDetails();
        }
    }

    /* Destructor */
    ~Library(){
        for(auto it: books){
            delete it.second;
            it.second = nullptr;
        }
        for(auto it: members){
            delete it.second;
            it.second = nullptr;
        }
        std::cout << "library destructor called" << std::endl;
    }
};

int main(){

    Library library;

    std::cout << "\nWelcome to the Library Management System\n";
    int choice = 0;
    do{
        std::cout << "\nEnter 1 for add book\n";
        std::cout << "Enter 2 for add member\n";
        std::cout << "Enter 3 for issue book to member\n";
        std::cout << "Enter 4 for return book from member\n";
        std::cout << "Enter 5 to search book by ID\n";
        std::cout << "Enter 6 to search book by name\n";
        std::cout << "Enter 7 to search member by ID\n";
        std::cout << "Enter 8 to search member by name\n";
        std::cout << "Enter 9 to delete a book by ID\n";
        std::cout << "Enter 10 to delete a book by name\n";
        std::cout << "Enter 11 to delete a member\n";
        std::cout << "Enter 12 to delete a member by name\n";
        std::cout << "Enter 13 show all books\n";
        std::cout << "Enter 14 show all members\n";
        std::cout << "Enter 0 to exit\n";
        std::cin >> choice;
        std::cin.ignore();

        int memberId, bookId;
        std::string title, author, name;
        switch(choice){
            case 1:
                std::cout << "\nEnter book title : ";
                std::getline(std::cin, title);
                std::cout << "\nEnter book author\n(If unknown feel free to type enter) : ";
                std::getline(std::cin, author);
                library.addBook(title, author);
                break;
            case 2:
                std::cout << "\nEnter member name : ";
                std::getline(std::cin, name);
                library.addMember(name);
                break;
            case 3:
                std::cout << "\nEnter member id : ";
                std::cin >> memberId;
                std::cout << "\nEnter book id : ";
                std::cin >> bookId;
                library.issueBook(memberId, bookId);
                break;
            case 4:
                std::cout << "\nEnter member id : ";
                std::cin >> memberId;
                std::cout << "\nEnter book id : ";
                std::cin >> bookId;
                library.returnBook(memberId, bookId);
                break;
            case 5:
                std::cout << "\nEnter book id : ";
                std::cin >> bookId;
                library.searchBookById(bookId);
                break;
            case 6:
                std::cout << "\nEnter book title : ";
                std::getline(std::cin, title);
                library.searchBookByName(title);
                break;
            case 7:
                std::cout << "\nEnter member id : ";
                std::cin >> memberId;
                library.searchMemberById(memberId);
                break;
            case 8:
                std::cout << "\nEnter member name : ";
                std::getline(std::cin, name);
                library.searchMemberByName(name);
                break;
            case 9:
                std::cout << "\nEnter book id : ";
                std::cin >> bookId;
                library.removeBookById(bookId);
                break;
            case 10:
                std::cout << "\nEnter book name : ";
                std::getline(std::cin, title);
                library.removeBookByName(title);
                break;
            case 11:
                std::cout << "\nEnter member id : ";
                std::cin >> memberId;
                library.removeMemberById(memberId);
                break;
            case 12:
                std::cout << "\nEnter member name : ";
                std::getline(std::cin, name);
                library.removeMemberByName(name);
                break;
            case 13:
                library.showBooks();
                break;
            case 14:
                library.showMembers();
                break;
            case 0:
                std::cout << "\nExiting... Bye\n";
                break;
            default:
                std::cout << "Invalid choice! Please enter a valid input";
        }
    } while(choice != 0);

}