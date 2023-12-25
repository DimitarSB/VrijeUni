#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>

class Stack {
    public:
        Stack();

        bool isEmpty() const;
        // returns true if stack has no elements stored

        int top() const;
        // returns element from top of the stack
        // throws std::runtime_error("stack is empty")

        int pop();
        // returns element from top of the stack and removes it
        // throws std::runtime_error("stack is empty")

        void push(int);
        // puts a new element on top of the stack

        std::string toString() const;
        // returns the contents of the stack in the format [top,next,...,bottom]
        // e.g.: push(1), push(2), toString() -> [2,1]

    private:
        std::vector<int> elements;
};

Stack::Stack(){}

int Stack::top()const{

    int top;
    top = elements.at(elements.size() - 1);
    return top;
}

void Stack::push(int newItem){

    elements.push_back(newItem);
}

int Stack::pop(){

    if(isEmpty() == false){
        int top = elements.at(elements.size() - 1);
        elements.pop_back();
        return top;
    }
    else throw std::runtime_error("stack is empty");
}

bool Stack::isEmpty()const{

    if(elements.size() == 0){
        return true;
    }
    return false;
}

std::string Stack::toString()const{

    std::string contents = "[";
    if(isEmpty() == false){
        std::vector<int> reversedElements = elements;
        std::reverse(reversedElements.begin(), reversedElements.end());


        for(int i = 0; i < reversedElements.size() - 1 ; i++){
            contents += std::to_string(reversedElements.at(i)) + ",";
        }
        contents += std::to_string(reversedElements.at(reversedElements.size() - 1));
    }
    contents.append("]");
    return contents;
}

int main() {
    Stack stack;
    
    while (true) {
        try {
            std::cout << "stack> ";
            
            std::string command;
            std::cin >> command;
            
            if ( (command.compare("end") == 0) || std::cin.eof() ){
                break;
            } else if (command.compare("top") == 0) {
                std::cout << stack.top() << std::endl;
            } else if (command.compare("pop") == 0) {
                std::cout << stack.pop() << std::endl;
            } else if (command == "push") {
                if ( std::cin.eof() ) break;
                int i;
                std::cin >> i;
                bool failed = std::cin.fail();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if ( failed ){
                  throw std::runtime_error("not a number");
                }
                stack.push(i);
            } else if ( command.compare("list") == 0){
                std::cout << stack.toString() << std::endl;;
            } else {
                throw std::runtime_error("invalid command");
            }
        } catch (std::runtime_error& e) {
            std::cout << std::endl;
            std::cout << "error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}
