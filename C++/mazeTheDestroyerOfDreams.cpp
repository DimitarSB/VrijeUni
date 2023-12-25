#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>
#include <time.h>

using namespace std;

const std::pair<int, int> RIGHT = {1, 0};
const std::pair<int, int> LEFT = {-1, 0};
const std::pair<int, int> UP = {0, -1};
const std::pair<int, int> DOWN = {0, 1};

const std::vector<std::pair<int, int>> DIRECTIONS = {RIGHT, LEFT, UP, DOWN};

class Cell{
    public:
    bool wall = true;
    bool floor = true;
    bool visited = false;
    bool partOfPath = false;
    int xCoor;
    int yCoor;
};

class Maze{
    public:
        Maze(int arg, char** argv);
        void createMaze(std::vector<std::vector<Cell>> &grid, int currentX, int currentY);
        void printMaze();

    private:
        Cell cell;
        int rows;
        int cols;
        int seed;
        vector<vector<Cell>> grid; 
        void checkNumberOfArg(int arg);
        void getSeed(int arg, char** argv);
        void fillTheGridWithCoor(vector<vector<Cell>> &grid);
        int currentX = 0;
        int currentY = 0;
        std::vector<std::pair<int, int>>newDirections(int currentX, int currentY);
        bool isItOut(std::pair<int, int> newCell);
        bool isItVisited(std::pair<int, int> newCell);
        void razeWalls(std::pair<int, int>randomDirection, int currentX, int currentY);
        
};

Maze::Maze(int arg, char** argv){

    checkNumberOfArg(arg);
    this->rows = atoi(argv[1]);
    this->cols = atoi(argv[2]);
    getSeed(arg, argv);
    this->grid.resize(this->rows, std::vector<Cell>(this->cols, Cell()));
    fillTheGridWithCoor(grid);
    printMaze();
    createMaze(this->grid, this->currentX, this->currentY);
    cout << "Before printing" << endl;
    printMaze();
 
}

void Maze::getSeed(int arg, char** argv){

    if(arg > 3){
        this->seed = atoi(argv[3]);
    }
    else this->seed = 0;
}

void Maze::fillTheGridWithCoor(vector<vector<Cell>> &grid){

    cout << "Size: " << grid.size() << endl;
    for(int i = 0; i < rows; i++){
        for(int m = 0; m < cols; m++){
            grid.at(i).at(m).xCoor = i;
            //cout << "grid.at(i).xCoor: " << grid.at(i).at(m).xCoor << "---------" << endl;
            grid.at(i).at(m).yCoor = m;
            //cout << "grid.at(i).yCoor: " << grid.at(i).at(m).yCoor << endl;    
        }
    }

//     for(int i = 0; i < grid.size(); i++){
//         for(int z = 0; z < grid.at(i).size(); z++){
//             cout << "At row: " << grid.at(i).at(z).xCoor << " ";
//             cout << "At cols:" << grid.at(i).at(z).yCoor << endl; 
//         }
//     }
}

void Maze::createMaze(std::vector<std::vector<Cell>> &grid, int currentX, int currentY){

    reset:
    grid.at(currentX).at(currentY).visited = true;
    std::vector<std::pair<int, int>> possibleDirections = newDirections(currentX, currentY);
    std::pair<int, int>randomDirection;
    cout << "possibleDir size: "<< possibleDirections.size() << endl;
    for(int i = 0; i < possibleDirections.size(); i++){
        cout << possibleDirections.at(i).first << endl;
        cout << possibleDirections.at(i).second << endl;
    }

    if(possibleDirections.empty() == true){
        return;
    }
    else{
        if(seed != 0){
            srand(seed);
        }
        else srand(time(NULL)); 

        //cout << "Got here" << endl;    
        std::pair<int, int>randomDirection = possibleDirections.at(rand() % possibleDirections.size());
        cout << "The direction is: " << endl;
        cout << randomDirection.first << endl;
        cout << randomDirection.second << endl;
        razeWalls(randomDirection, currentX, currentY);
        cout << "After raze: " << endl;
        
        int newCurrentX = currentX + randomDirection.first;
        int newCurrentY = currentY + randomDirection.second;
        printMaze();
        createMaze(grid, newCurrentX, newCurrentY);
        cout << "Reseting..." << endl;
        cout << endl;
        goto reset;
    }
    return;
}

std::vector<std::pair<int, int>> Maze::newDirections(int currentX, int currentY){

    cout << "Inside newDirections" << endl;
    std::vector<std::pair<int, int>> result;
    std::pair<int, int> newPair;

    for(int i = 0; i < DIRECTIONS.size(); i++){
        newPair.first = currentX + DIRECTIONS.at(i).first;
        newPair.second = currentY + DIRECTIONS.at(i).second;
        if(isItOut(newPair) == false and isItVisited(newPair) == false){
            result.push_back(DIRECTIONS.at(i));
        }
    }
    return result;
}

bool Maze::isItOut(std::pair<int, int> newCell){

    std::cout << "Inside the isItOut function..." << std::endl;
    if(newCell.first > rows or newCell.second > cols or newCell.first < 0 or newCell.second < 0){
        return true;
    }
    return false;
}

bool Maze::isItVisited(std::pair<int, int> newCell){

    std::cout << "Inside the isItVisited function..." << std::endl;
    if(grid.at(newCell.first).at(newCell.second).visited == true){
        return true;
    }
    return false;
}

void Maze::razeWalls(std::pair<int, int>randomDirection, int currentX, int currentY){

    if (randomDirection == RIGHT){
        grid.at(currentX).at(currentY).wall = false;
    }
    else if(randomDirection == LEFT){
            currentX = randomDirection.first;
            currentY = randomDirection.second;
            grid.at(currentX).at(currentY).wall = false; 

            currentX = currentX - LEFT.first;
            currentY = currentY - LEFT.second;
    }   
    else if (randomDirection == UP){
            currentX = randomDirection.first;
            currentY = randomDirection.second;
            grid.at(currentX).at(currentY).floor = false; 

            currentX = currentX - LEFT.first;
            currentY = currentY - LEFT.second;
    }
    else grid.at(currentX).at(currentY).floor = false;
}

void Maze::printMaze(){

    for(int i = 0; i < grid.size(); i++){
        cout << "+";

        for(int j = 0; j < grid.at(0).size(); j++){
            if(i == 0 || grid.at(i-1).at(j).floor){
                cout << "---+";
            } else {
                cout << "   +";
            }
        }

        cout << endl << "|";

        for(int z = 0; z < grid.at(i).size(); z++){
            if(cell.partOfPath){
                cout << " . ";
            } else {
                cout << "   ";
            }

            if(cell.wall) {
                cout << "|";
            } else {
                cout << " ";
            }
        }

        cout << endl;
    }

    cout << "+";

    for(int i = 0; i < grid.at(0).size(); i++){
        cout << "---
    }

    cout << endl;
}

//Check stuff
void Maze::checkNumberOfArg(int arg){
    
    if(arg < 3 or arg > 4){
        throw std::invalid_argument("invalid parameter list");
    }  
}


int main(int arg, char** argv){

    try{
        
    
        // Seed seed = Seed(argv, arg);
        // seed.showAllPrivateInSeed();

        Cell cell;
        Maze maze = Maze(arg, argv);

        // maze.printTheMaze();
    }
    catch (std::invalid_argument& excpt) {
        std::cout << excpt.what() << std::endl;
    }

    return 0;
} 
