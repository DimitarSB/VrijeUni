#include <iostream>
#include <fstream>
#include <vector>

std::vector<char> lowerCaseConverter (std::vector<char> &inputArray){

    for(int i = 0; i < inputArray.size(); i++){
        inputArray[i] = tolower(inputArray[i]);
    }
    return inputArray;
}

bool isItVowel(char c){

    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return true;
    }
    else return false;
}

std::vector<int> numOfEveryChar (std::vector<char> &inputArray){

    std::vector<int> numOfEveryCharFound(26, 0);

    for(int i = 0; i < inputArray.size(); i++){
        for(int m = 0; m < 26; m++){
            if((int)inputArray[i] - 'a' == m){
               numOfEveryCharFound[m] = numOfEveryCharFound[m] + 1;
            }
        }
    }
    return numOfEveryCharFound;
}

std::vector<int> findBiggerBetweenTwo(std::vector<int> &solution){

    if(solution[0] > solution[2]){
        solution.push_back(solution[0]);
        solution.push_back(solution[1]);
    }
    else if(solution[0] < solution[2]){
        solution.push_back(solution[2]);
        solution.push_back(solution[3]);       
    }
    else{
        if(solution[1] > solution[3]){
            solution.push_back(solution[2]);
            solution.push_back(solution[3]);
        }
        else {
            solution.push_back(solution[0]);
            solution.push_back(solution[1]);
        }
    }
    return solution;
}

int ifVowelValueZeroThenA(int zeroValue, int &indexZeroValue){

    if(zeroValue == 0){
        indexZeroValue = 0;
    }
    return indexZeroValue;
}

int ifConsValueZeroThenB(int zeroValue, int &indexZeroValue){
    
    if(zeroValue == 0){
        indexZeroValue = 1;
    }
    return indexZeroValue;
}

std::vector<int> findTheWantedVowAndCon(std::vector<int> &numOfEveryCharFound){
    
    std::vector<int>temp;

    int biggestNumberForVowel = 0;
    int biggestNumberIndexForVowel = 0;
    int biggestNumberForCons = 0;
    int biggestNumberIndexForCons = 0;

    for(int i = 0; i < numOfEveryCharFound.size(); i++){
        if(isItVowel((char)i + 'a') == true){
            if(biggestNumberForVowel < numOfEveryCharFound[i]){
                biggestNumberForVowel = numOfEveryCharFound[i];
                biggestNumberIndexForVowel = i;
            }
        }
        else {
                if(biggestNumberForCons < numOfEveryCharFound[i]){
                    biggestNumberForCons = numOfEveryCharFound[i];
                    biggestNumberIndexForCons = i;
                }
            }
    }
    
    biggestNumberIndexForVowel = ifVowelValueZeroThenA(biggestNumberForVowel, biggestNumberIndexForVowel);
    biggestNumberIndexForCons = ifConsValueZeroThenB(biggestNumberForCons, biggestNumberIndexForCons);

    temp.push_back(biggestNumberForVowel);
    temp.push_back(biggestNumberIndexForVowel + 'a');
    temp.push_back(biggestNumberForCons);
    temp.push_back(biggestNumberIndexForCons + 'a');

    return temp;
}

int main(int arg, char** argv){

    std::vector<char> inputArray;
    std::vector<int> numberOfEveryChar;
    std::vector<int> solution;
    char inp;
    std::ifstream inFS;

    if(arg == 2){
        inFS.open(argv[1]);
        if(!(inFS.is_open())){
            std::cout << "cannot open input file "<< argv[1] << std::endl;
            return -1;
        }
        else{
            while(inFS >> inp){
                inputArray.push_back(inp);
            }
            inFS.close();
        }
    }
    else if(arg == 1){

        while(std::cin >> inp){
            if(isalpha(inp)){
                inputArray.push_back(inp);
            }
        }
    }
    else if(arg >= 3){ 
            std::cout << "cannot handle parameter list" << std::endl;
            return -1;
        }

    inputArray = lowerCaseConverter(inputArray);
    numberOfEveryChar = numOfEveryChar(inputArray);
    solution = findTheWantedVowAndCon(numberOfEveryChar);

    std::cout << "Most frequent vowel: " << char(solution[1]) << " (" << solution[0] << " times)" << std::endl;
    std::cout << "Most frequent consonant: " << char(solution[3]) << " (" << solution[2] << " times)" << std::endl;

    solution = findBiggerBetweenTwo(solution);

    std::cout << "Most frequent letter, overall: " << char(solution[5]) << " (" << solution[4] << " times)"  << std::endl;
    
    return 0;
}
    