#include <iostream>
#include <vector>
using namespace std;

void printvector(vector<int> v){
    for (int i : v){
        cout << i << " ";
    }

    cout << endl;
}

int list(vector<int> v){
    cout << endl << "The deduplicated vector is: [" << v.at(0);
    for(int i = 1; i < v.size(); i++){
        cout << "," << v.at(i);
    }
    cout << "]";
    
    return 0;
}

vector<int> erase(vector<int> &v, int positionForErase){
    cout << "before: ";
    printvector(v);
    cout<< "pos " << positionForErase << endl;

    vector<int> temp;
    for(int i = positionForErase + 1; i < v.size(); i++){
        cout<< "v{i}" << v[i]<<endl;
        temp.push_back(v[i]);
    }

    v.resize(positionForErase);
    cout << "remainder: ";
    printvector(v);

    for(int i = 0; i < temp.size(); i++){
        cout<<"values in temp: "<< temp[i]<<endl;
    }

    for(int i = 0; i < temp.size(); i++){
        v.push_back(temp[i]);
    }

    cout << "end: ";
    printvector(v);
    return v;
}


void check(vector<int> &arrayOfInt){

    for(int i = 0; i < arrayOfInt.size(); i++){
        for(int m = 0; m < arrayOfInt.size(); m++){
            if(arrayOfInt[i] == arrayOfInt[m] and i != m){
                erase(arrayOfInt, m); // Calling my erase function
                m--; 
            }
        }                 
    }

    list(arrayOfInt);
}

void input(vector<int> &arrayOfInt){
    int inputedValue;

    while (cin >> inputedValue && !cin.eof()){
        cout << "x";
        arrayOfInt.push_back(inputedValue);
    }
}

int main(){

    vector <int> arrayOfInt;
    cout << "Enter the vector elements: ";

    input(arrayOfInt);
    check(arrayOfInt);

    return 0;
}
