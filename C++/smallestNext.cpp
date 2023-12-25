#include <iostream>
#include <vector>
using namespace std;

void findTheNextSmallest(vector<int> arrayOfInt, int smallestNum){

    smallestNum++;
    
    for(int i = 0; i < arrayOfInt.size(); i++){
        if(smallestNum == arrayOfInt[i]){
            smallestNum++;
            i = 0;
        }
    }
    cout << "The smallest missing number is " << smallestNum;
}


int check(vector<int> &arrayOfInt){

    int theSmallestNum = arrayOfInt[0];

    for(int i = 0; i < arrayOfInt.size(); i++){
        if(theSmallestNum > arrayOfInt[i]){
            theSmallestNum = arrayOfInt[i];
        }
    }

    return theSmallestNum;
}

void input(vector<int> &arrayOfInt, int wishedNum){

    int counter = 0;
    int inputedValue;
    cout << "Please enter the numbers"<<endl;

    while (counter < wishedNum){
        cin >> inputedValue;
        arrayOfInt.push_back(inputedValue);
        counter++;
    }   
}

int main(){

    vector <int> arrayOfInt;
    int wishedNumbers;
    int smallestNumber;

    cout << "How many numbers? "<<endl;
    cin >> wishedNumbers;

    input(arrayOfInt, wishedNumbers);
    smallestNumber = check(arrayOfInt);
    findTheNextSmallest(arrayOfInt, smallestNumber);

    return 0;
}