#include <iostream>
using namespace std;

int main() {
    
    double firstNumber, secondNumber;
    char operation; 
    bool quit = 0;
    
    while(quit == 0){

        cout << "Enter the expression: " << endl;
        cin >> operation;
        cin >> firstNumber;
        cin >> secondNumber;

      switch(operation) {
           
        case '+':
        cout << firstNumber << " + " << secondNumber << " = " << firstNumber + secondNumber << endl;
        break;
        
        case '-':
        cout << firstNumber << " - " << secondNumber << " = " << firstNumber - secondNumber << endl;
        break;
        
        case '*':
        cout << firstNumber << " * " << secondNumber << " = " << firstNumber * secondNumber << endl;
        break;
        
        case '/':
        cout << firstNumber << " / " << secondNumber << " = " << firstNumber / secondNumber << endl;
        break;
        
        case 'q':
        quit = 1;
        break;
        
        default:
        cout << "Error!" << endl;
        quit = 1;
        break;
        
      }

    }
   
  return 0;
}