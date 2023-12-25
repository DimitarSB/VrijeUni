#include <iostream>
#include <vector>
#include "mergesort.h"

int main(){
    std::vector<std::string> names { "Frits", "Hugo", "Adam", "Catherine", "Joliet", "Xu", "Quirin"};
    mergeSort(names, 0, names.size()-1);
    for (unsigned int i=0; i < names.size(); i++){
        std::cout << names.at(i) << ' ';
    }
    std::cout << std::endl;
    return 0;
}