#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <stack>
#include <random>
#include <sstream>

class Maze{
    public:    
    Maze();
    int boardWidth;
    int boardHeight;
    void input(int argc, char* argv[]);
    void start();
    void GridGen(std::vector<std::vector<char> > &board);
    bool notVisited(std::pair<int, int> validPair);
    void wallDel(std::vector<std::vector<char> > &board);
    void validate(std::vector<std::vector<char> > &board);
    void transferOutside();
    bool pathFinder(std::vector<std::vector<char> > &board);
    void output(std::vector<std::vector<char> > &board);

    private:
    int seed;
    int counter = 1;
    std::stack<std::pair<int, int> > stack;
    std::vector<std::pair<int, int> > visited;
    std::vector<std::pair<int, int> > validNeighbors;
    std::pair<int, int> currentPosition;
    std::pair<int, int> nextPosition;
    std::pair<int, int> endPosition;
    std::vector<std::pair<int, int> > tempVector;
};

Maze::Maze(){
}

void Maze::input(int argc, char* argv[]){
      if (argc == 3) {
        boardHeight = (std::stoi(argv[1]));
        boardWidth = (std::stoi(argv[2]));
        srand(time(NULL));
    }
    else if (argc == 4) {
        boardHeight = (std::stoi(argv[1]));
        boardWidth = (std::stoi(argv[2]));
        seed = (std::stoi(argv[3]));
        srand(seed);
    }
    else {
        throw std::runtime_error("invalid parameter list");
    }
}

void Maze::start(){
    currentPosition.first = 1; //boardHeight y
    currentPosition.second = 2; //boardWidth x 
}


void Maze::GridGen(std::vector<std::vector<char> > &board) {

    for (int i = 0; i < (boardHeight * 2) + 1; i++){
        if (i % 2 == 0) {
            for (int evenW = 0; evenW < (boardWidth * 4); evenW = evenW + 4)
            {
                board.at(i).at(evenW) = '+';
                board.at(i).at(evenW + 1) = '-';
                board.at(i).at(evenW + 2) = '-';
                board.at(i).at(evenW + 3) = '-';
            }
            board.at(i).push_back('+');   
        }
        else {
            for (int unevenW = 0; unevenW < (boardWidth * 4); unevenW = unevenW + 4)
            {
                board.at(i).at(unevenW) = '|';
                board.at(i).at(unevenW + 1) = ' ';
                board.at(i).at(unevenW + 2) = ' ';
                board.at(i).at(unevenW + 3) = ' ';
            }
            board.at(i).push_back('|');     
        }
    }
}

bool Maze::notVisited(std::pair<int, int> validPair) {
    for (std::pair<int, int> posPair: visited)
    {
        if(posPair.first == validPair.first && posPair.second == validPair.second){
            return false;
        }   
    }
    return true;
}

void Maze::wallDel(std::vector<std::vector<char> > &board){
    std::pair<int, int> wDelete;
    wDelete.first = ' ';
    wDelete.second = ' ';
    if (currentPosition.first == nextPosition.first) {
        board.at(currentPosition.first).at((currentPosition.second + nextPosition.second) / 2) = wDelete.first;
    }
    else {
        board.at((currentPosition.first + nextPosition.first) / 2).at(currentPosition.second) = wDelete.second;
        board.at((currentPosition.first + nextPosition.first) / 2).at(currentPosition.second + 1) = wDelete.second;
        board.at((currentPosition.first + nextPosition.first) / 2).at(currentPosition.second - 1) = wDelete.second;
    }
}


void Maze::validate(std::vector<std::vector<char> > &board)
{
    std::pair<int, int> north;
    std::pair<int, int> south;
    std::pair<int, int> east;
    std::pair<int, int> west;

    north.first = currentPosition.first - 2;
    north.second = currentPosition.second;
    validNeighbors.clear();

    if (north.first > 0 && notVisited(north)) {
        validNeighbors.push_back(north);
    }
  
    south.first = currentPosition.first + 2;
    south.second = currentPosition.second;

    if(south.first > 0 && south.first < boardHeight * 2 && notVisited(south)) {
        validNeighbors.push_back(south);
    }

    east.first = currentPosition.first;
    east.second = currentPosition.second + 4;

    if(east.second > 0 && east.second < boardWidth * 4 && notVisited(east)) {
        validNeighbors.push_back(east);
    }

    west.first = currentPosition.first;
    west.second = currentPosition.second - 4;

    if(west.second > 0 && notVisited(west)) {
        validNeighbors.push_back(west);
    }

    if (!validNeighbors.empty()) {
        int sizeOf = validNeighbors.size();
        int randomIndex = rand() % sizeOf;
        nextPosition.first = validNeighbors.at(randomIndex).first;
        nextPosition.second = validNeighbors.at(randomIndex).second;
        wallDel(board);
    }
}

void Maze::transferOutside() {
    while (!stack.empty()) {
        tempVector.push_back(stack.top());
        stack.pop();
    }
    for (int i = tempVector.size() - 1; i >= 0; i--)
    {
        stack.push(tempVector.at(i));
    }
}

bool Maze::pathFinder(std::vector<std::vector<char> > &board){
    visited.push_back(currentPosition);
    endPosition.first = (boardHeight * 2) - 1;
    endPosition.second = (boardWidth * 4) - 2;
    if (counter == boardHeight * boardWidth) {
        return true;
    }
    validate(board);
    if (validNeighbors.empty()){
        currentPosition.first = stack.top().first;
        currentPosition.second = stack.top().second;
        stack.pop();
        pathFinder(board);
    }else {
        stack.push(currentPosition);
        currentPosition = nextPosition;
        counter++;
        if (currentPosition == endPosition) {
            transferOutside();
        }
        pathFinder(board);
    }
    return true;
}

void Maze::output(std::vector<std::vector<char> > &board) {
    if(pathFinder(board)){
        for(std::pair<int, int> element: tempVector){
            board.at(element.first).at(element.second) = '.';
            board.at(endPosition.first).at(endPosition.second) = '.';
        }
        for(int i = 0; i < board.size(); i++)
        {
        for(int j = 0; j < board.at(i).size(); j++)
        {
        std::cout << board.at(i).at(j);
        }
        std::cout << std::endl;
        }
    }
}
    

int main(int argc, char *argv[]) {
    Maze maze;
    try {
        maze.input(argc, argv);
        std::vector<std::vector<char> > board((4 * maze.boardHeight), std::vector<char>(4 * maze.boardWidth, ' '));
        maze.GridGen(board);
        maze.start();
        maze.output(board);
    }catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}