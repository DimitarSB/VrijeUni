#include <iostream>
#include <vector>
using namespace std;
#include "mergesort.h"

int main(){

    vector<double> list { 42.0, -7, 1.001e3, -16.5, 2.5, 0.0, -17.8 };
    mergeSort(list, 0, list.size()-1);
    for (unsigned int i=0; i < list.size(); i++){
        cout << list.at(i) << ' ';
    }    
    cout << endl; 

    return 0;
}