#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <stdexcept>

using namespace std;

const vector<pair<int, int>> constantPosition = {{-2, 1}, {-1, 2}, {-1, -2}, {-2, -1}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};

string getString(pair<int, int> p){
    string s = "";
    s += (char)(p.first + 'a');
    s.append(to_string(p.second));

    return s;
}

void printVec(vector<pair<int, int>> v){
    for (pair<int, int> p : v){
        cout << getString(p) << " ";
    }
    cout << endl;
}

bool checkForOutOfBounds(pair<int, int>tempCurrentPos, int size){
    if(tempCurrentPos.first >= 0 and tempCurrentPos.second <= size and tempCurrentPos.first < size and tempCurrentPos.second > 0){
        return true;
    }

    return false;
}

void printPairVector(vector<pair<int, int>> &boardCoordinates, int cols){
    //cout << "Pair vectors elements: "<<endl;
    int flag = 0;
    for(int i = 0; i < boardCoordinates.size(); i++){
        cout << boardCoordinates.at(i).first;
        cout << boardCoordinates.at(i).second << " ";
        flag ++;
        if(flag == cols){
            cout << endl;
            flag = 0;
        }
    }
    cout << endl;
}

vector<pair<int, int>> findKnightsNextMove(pair<int, int>currentPosition, int size){
    
    vector<pair<int, int>> nextKnightsMoves;
    pair<int, int>tempCurrentPos = currentPosition;
     
    for(int i = 0; i < constantPosition.size(); i++){
        tempCurrentPos.first += constantPosition.at(i).first;
        tempCurrentPos.second += constantPosition.at(i).second;
        if(checkForOutOfBounds(tempCurrentPos, size) == true){
            nextKnightsMoves.push_back(tempCurrentPos);
            tempCurrentPos = currentPosition;
        }
        tempCurrentPos = currentPosition;
    }

    cout << getString(currentPosition) << ": ";
    printVec(nextKnightsMoves);

    return nextKnightsMoves;
}

pair<int, int>startingPos(char** argv){

    string startingPos = string(argv[2]);
    int iPosition = startingPos.at(0) - 'a';
    int jPosition = stoi(startingPos.substr(1, startingPos.size() - 1));
    pair<int, int>currentPosition = {iPosition,jPosition};

    return currentPosition;
}

pair<int, int>finalPos(char** argv){

    string endingPos = string(argv[3]);
    int iEndPosition = endingPos.at(0) - 'a';
    int jEndPosition = stoi(endingPos.substr(1, endingPos.size() - 1));
    pair<int, int>endPosition = {iEndPosition,jEndPosition};
    return endPosition;
}

vector<vector<int>> createChessBoard(vector<vector<int>> &chessBoard, int size){

    vector<int> temp; 
    for(int m = 0; m < size; m++){
        temp.push_back(m + 1);
    }
    for(int i = 0; i < size; i++){
        chessBoard.push_back(temp); 
    }
    return chessBoard;
}

void printDoubleVector(vector<vector<int>> &v, int rows, int cols){

   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++){
        cout << i; 
        cout << v.at(i).at(j) << " ";
      }
      cout << endl;
   }
}

bool isItVisited(pair<int, int> nextPosition, vector<pair<int, int>> visitedBoxes){

    for(int m = 0; m < visitedBoxes.size(); m++){
        if(nextPosition == visitedBoxes.at(m)){
            return true;
        }
    }
    return false;
}

bool findKnightsTour (vector<pair<int, int>> &visitedBoxes, pair<int, int>currentPosition, pair<int, int>endPosition, int size){
    bool success;
    printVec(visitedBoxes);

    if(currentPosition == endPosition){
        return true; 
    }
    else{
        vector<pair<int, int>> nextPossibleKnightMoves = findKnightsNextMove(currentPosition, size);

        for(int i = 0; i < nextPossibleKnightMoves.size(); i++){
            if(!isItVisited(nextPossibleKnightMoves.at(i), visitedBoxes)){
                visitedBoxes.push_back(nextPossibleKnightMoves.at(i));
                cout << "trying to visit: ";
                cout << getString(nextPossibleKnightMoves.at(i)) << endl;

                currentPosition = nextPossibleKnightMoves.at(i);
                success = findKnightsTour(visitedBoxes, currentPosition, endPosition, size);
                if(success){
                    cout << "returning success with visited boxes: ";
                    printVec(visitedBoxes);
                    return true;
                }
                
                else {
                    visitedBoxes.pop_back();
                    cout << "returning no success, popped back, new list: ";
                    printVec(visitedBoxes);
                }
            }
        }
        return false;
    }
}

void printPath(vector<pair<int, int>> visitedBoxes, pair<int, int>endPosition){
    for(int i = 0; i < visitedBoxes.size(); i++){
        cout << (char)(visitedBoxes.at(i).first + 97);
        cout << visitedBoxes.at(i).second << " ";
    }
}


int main(int arg, char** argv){

    int rows = atoi(argv[1]), cols = atoi(argv[1]), size = rows;

    std::vector<vector<int>> chessBoard;
    chessBoard = createChessBoard(chessBoard, size);
    
    pair<int, int>currentPosition = startingPos(argv);
    vector<pair<int,int>>visitedBoxes = {currentPosition};

    pair<int, int>endPosition = finalPos(argv);

    findKnightsTour(visitedBoxes, currentPosition, endPosition, size);
    printPath(visitedBoxes, endPosition);
 
    return 0;
} 