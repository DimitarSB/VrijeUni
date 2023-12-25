#include <iostream>
using namespace std;

int main(){
    
    int chosenNumber;
    int counter = 0;
    
    cout << "Enter the first number of the sequence:" << endl;
    cin >> chosenNumber;
    cout << chosenNumber;

    if(chosenNumber == 1){
        counter ++;
    } 

    if (chosenNumber <= 0)
        cout << "Error!" << endl;
        
    else if (chosenNumber > 0){
            do{
                if (chosenNumber % 2 == 0){
                    chosenNumber = chosenNumber / 2;
                    cout << " " << chosenNumber;
                    if (chosenNumber == 1){
                        counter++;
                    }
                }
                
            else if (chosenNumber % 2 != 0){
                    chosenNumber = 3 * chosenNumber + 1;
                    cout << " " << chosenNumber;
                    if (chosenNumber == 1){
                        counter++;
                    }
            }
        } while (counter != 3);
    }
    
    cout << "...";
    
    return 0;
}