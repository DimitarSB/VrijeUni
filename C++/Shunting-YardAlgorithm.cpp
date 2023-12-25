#include <iostream>
#include <sstream>
#include <stack>
#include <queue>

class Token{

    public:
        std::string expression;
        std::stack<std::string> operators;
        std::queue<std::string> output;
        void prefixTransformation (std::stack<std::string> &operators, std::queue<std::string> &output, std::stringstream &streamOfPieces);
        void handleLeftovers (std::stack<std::string> &operators, std::queue<std::string> &output);       
        void calculateOutput(std::queue<std::string> &output);
        void printQueue(std::queue<std::string> output);
    	void resetQueue(std::queue<std::string> &output);

    private:    
        bool isItLowPrecedence (std::string piece);
        bool isItHighPrecedence (std::string piece);
        bool isItParenthesis (std::string piece);
        void handleParanthesis (std::stack<std::string> &operators, std::queue<std::string> &output);
        void removeLastInQueue(std::queue<std::string> &output);
};

void Token::prefixTransformation(std::stack<std::string> &operators, std::queue<std::string> &output, std::stringstream &streamOfPieces){

    std::string expressionPiece;
    std::string pieceHolder;
    if(streamOfPieces.eof() == true){
        return; 
    }
    else{
        streamOfPieces >> expressionPiece;
        if(isItHighPrecedence(expressionPiece) == true){
            if(operators.empty() == false and isItHighPrecedence(operators.top()) == true){
                pieceHolder = operators.top();
                operators.pop();
                output.push(pieceHolder);
            }
            operators.push(expressionPiece);
        }
        else if(isItLowPrecedence(expressionPiece) == true){
            if(operators.empty() == false and isItHighPrecedence(operators.top()) == true){
                while(operators.empty() == false and isItParenthesis(operators.top()) != true){
                    pieceHolder = operators.top();
                    operators.pop();  
                    output.push(pieceHolder);
                }
                operators.push(expressionPiece);
            }
            else if(operators.empty() == false and isItLowPrecedence(operators.top()) == true){
                pieceHolder = operators.top();
                operators.pop();
                output.push(pieceHolder);
                operators.push(expressionPiece); 
            }
            else operators.push(expressionPiece);
        }
        else if(isItParenthesis(expressionPiece) == true){
            if(expressionPiece == "("){
                operators.push(expressionPiece);
            }
            else handleParanthesis(operators, output);
        }
        else output.push(expressionPiece);
        prefixTransformation(operators, output, streamOfPieces);
    }
}

bool Token::isItLowPrecedence(std::string piece){
    
    if(piece != "+" and piece != "-"){
        return false; 
    }
    else return true;
}

bool Token::isItHighPrecedence(std::string piece){
    
    if(piece != "/" and piece != "%" and piece != "*"){
        return false; 
    }
    else return true;
}

bool Token::isItParenthesis(std::string piece){
    
    if(piece != "(" and piece != ")"){
        return false; 
    }
    else return true;
}

void Token::handleParanthesis(std::stack<std::string> &operators, std::queue<std::string> &output){
    
    while(operators.top() != "("){
        output.push(operators.top());
        operators.pop();
    }
    operators.pop();
}

void Token::handleLeftovers(std::stack<std::string> &operators, std::queue<std::string> &output){

    if(operators.empty() == false){
        do{
            output.push(operators.top());
            operators.pop();
        }while(operators.empty() != true);
    }
}

void Token::printQueue(std::queue<std::string> output) {

    while (output.empty() == false) {
        if(output.front() == "+" or output.front() == "-" or output.front() == "/" or output.front() == "*" or output.front() == "%"){
            std::cout << output.front() << " ";
        }
        else{
            double result = stod(output.front());
            std::cout << result << " ";
        }
        output.pop();
    }
}

void Token::calculateOutput(std::queue<std::string> &output){

    while(output.size() != 1){
        if(output.front() == "+" or output.front() == "-" or output.front() == "/" or output.front() == "*" or output.front() == "%"){
            double resultD, number2 = stod(output.back());
            removeLastInQueue(output);
            double number1 = stod(output.back());
            removeLastInQueue(output);
            if(output.front() == "+"){
                resultD = number1 + number2;
                output.pop();
                output.push(std::to_string(resultD));
            }
            else if(output.front() == "-"){
                resultD = number1 - number2;
                output.pop();
                output.push(std::to_string(resultD));
            }
            else if(output.front() == "*"){
                resultD= number1 * number2;
                output.pop();
                output.push(std::to_string(resultD));                
            }
            else if(output.front() == "/"){
                resultD = number1 / number2;
                output.pop();
                output.push(std::to_string(resultD));
            }
            else if(output.front() == "%"){
                int intNumber1 = (int)number1;
                int intNumber2 = (int)number2;
                intNumber1 = intNumber1 % intNumber2;
                output.pop();
                output.push(std::to_string(intNumber1));
            }
        }
        else{
            std::string pieceHolder = output.front();
            output.pop();
            output.push(pieceHolder);
        }
    }
}

void Token::removeLastInQueue(std::queue<std::string> &output){

    std::string pieceHolder;
    for(int i = 0; i < output.size() - 1; i++){
        pieceHolder = output.front();
        output.pop();
        output.push(pieceHolder);
    }
    output.pop();
}

void Token::resetQueue(std::queue<std::string> &output){

    while (output.empty() == false){
        output.pop();
    } 
}

int main(){

    Token input;

    while(getline(std::cin, input.expression)){
        if(input.expression.empty() == true)
            break;
        std::stringstream streamOfPieces(input.expression);
        input.prefixTransformation(input.operators, input.output, streamOfPieces);
        input.handleLeftovers(input.operators, input.output);      
        input.printQueue(input.output);
        input.calculateOutput(input.output);
        double result = stod(input.output.front());
        std::cout << "= " << result << std::endl;
        input.resetQueue(input.output);
    }
    return 0;
}
    