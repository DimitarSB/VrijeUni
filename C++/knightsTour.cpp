#include <iostream>
#include <vector>
#include <cstdlib>
//#include <utility>
#include <stdexcept>

const std::vector<std::pair<int, int>> constantPosition = {{-2, 1}, {-1, 2}, {-1, -2}, {-2, -1}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};

bool checkForOutOfBounds(std::pair<int, int>tempCurrentPos, int size){
    if(tempCurrentPos.first >= 0 and tempCurrentPos.second <= size and tempCurrentPos.first < size and tempCurrentPos.second > 0){
        return true;
    }

    return false;
}

std::vector<std::pair<int, int>> findKnightsNextMove(std::pair<int, int>currentPosition, int size){
    
    std::vector<std::pair<int, int>> nextKnightsMoves;
    std::pair<int, int>tempCurrentPos = currentPosition;
     
    for(int i = 0; i < constantPosition.size(); i++){
        tempCurrentPos.first += constantPosition.at(i).first;
        tempCurrentPos.second += constantPosition.at(i).second;
        if(checkForOutOfBounds(tempCurrentPos, size) == true){
            nextKnightsMoves.push_back(tempCurrentPos);
            tempCurrentPos = currentPosition;
        }
        tempCurrentPos = currentPosition;
    }
    return nextKnightsMoves;
}

std::pair<int, int>startingPos(char** argv){

    std::string startingPos = std::string(argv[2]);
    int iPosition = startingPos.at(0) - 'a';
    int jPosition = stoi(startingPos.substr(1, startingPos.size() - 1));
    std::pair<int, int>currentPosition = {iPosition,jPosition};

    return currentPosition;
}

std::pair<int, int>finalPos(char** argv){

    std::string endingPos = std::string(argv[3]);
    int iEndPosition = endingPos.at(0) - 'a';
    int jEndPosition = stoi(endingPos.substr(1, endingPos.size() - 1));
    std::pair<int, int>endPosition = {iEndPosition, jEndPosition};
    return endPosition;
}

bool isItVisited(std::pair<int, int> nextPosition, std::vector<std::pair<int, int>> visitedBoxes){

    for(int m = 0; m < visitedBoxes.size(); m++){
        if(nextPosition == visitedBoxes.at(m)){
            return true;
        }
    }
    return false;
}

bool findKnightsTour (std::vector<std::pair<int, int>> &visitedBoxes, std::pair<int, int> &currentPosition, std::pair<int, int> endPosition, int size){

    bool success;
    if(currentPosition == endPosition){
        return true; 
    }
    else{
        std::vector<std::pair<int, int>> nextPossibleKnightMoves = findKnightsNextMove(currentPosition, size);
        for(int i = 0; i < nextPossibleKnightMoves.size(); i++){
            if(isItVisited(nextPossibleKnightMoves.at(i), visitedBoxes) == false){
                visitedBoxes.push_back(nextPossibleKnightMoves.at(i));
                currentPosition = nextPossibleKnightMoves.at(i);
                success = findKnightsTour(visitedBoxes, currentPosition, endPosition, size);
                if(success == true){
                    return true;
                }
                else visitedBoxes.pop_back();
            }
        }
        return false;
    }
}

void printPath(std::vector<std::pair<int, int>> visitedBoxes, bool foundPath){

    if(foundPath == true){
        for(int i = 0; i < visitedBoxes.size(); i++){
            std::cout << (char)(visitedBoxes.at(i).first + 97);
            std::cout << visitedBoxes.at(i).second << " ";
        }
    }
    else std::cout << "could not find a knight's tour" << std::endl;
}

void checkNumberOfArg(int arg){
    
    if(arg != 4){
        throw std::invalid_argument("invalid parameter list");
    }  
}

void checkCorrectnessOfBoardLength(char** argv){

    int temp = atoi(argv[1]);
    if(!(temp > 0 and temp < 27)){
        throw std::invalid_argument("invalid parameter list");
    }
}

void checkCorrectnessOfRowLength(int size, std::pair<int, int>currentPosition, std::pair<int, int>endPosition){

    if(currentPosition.first < 0 or endPosition.first < 0 or currentPosition.first >= size or endPosition.first >= size){
        throw std::invalid_argument("invalid parameter list");
    }
}

void checkCorrectnessOfColLength(int size, std::pair<int, int>currentPosition, std::pair<int, int>endPosition){

    if(currentPosition.second > size or endPosition.second > size or currentPosition.second <= 0 or endPosition.second <= 0){
        throw std::invalid_argument("invalid parameter list");
    }
}

int main(int arg, char** argv){

    try{
        checkNumberOfArg(arg);

        int rows = atoi(argv[1]), cols = atoi(argv[1]), size = rows;
        checkCorrectnessOfBoardLength(argv);

        std::pair<int, int>currentPosition = startingPos(argv);
        std::vector<std::pair<int,int>>visitedBoxes = {currentPosition};
        std::pair<int, int>endPosition = finalPos(argv);

        checkCorrectnessOfRowLength(size, currentPosition, endPosition);
        checkCorrectnessOfColLength(size, currentPosition, endPosition);

        bool foundPath;
        foundPath = findKnightsTour(visitedBoxes, currentPosition, endPosition, size);
        printPath(visitedBoxes, foundPath);
    }
    catch (std::invalid_argument& excpt) {
        std::cout << excpt.what() << std::endl;
    }

    return 0;
} 
