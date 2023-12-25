#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

//Class Node
class Node{

    public:
        Node();
        Node(int);
        int value;
        int level = -1;
        Node* rightSubtree = nullptr;
        Node* leftSubtree = nullptr;
        //int numberOfRoots = 0;
};

Node::Node(){};

Node::Node(int value){

    this->value = value;
}

//Class BST
class BST{

    public:
        BST();
        ~BST();
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder(std::vector<int> &result);
        int getHeight();
        void prettyPrint();
        
    private:
        Node* root = nullptr;
        std::vector<int> allValuesInTree;
        void nodeRemover(Node* current);
        void insertKeyOverload(int newKey, Node* current);
        bool hasKeyOverload(int searchKey, Node* current);
        void inOrderOverload(std::vector<int> &allValuesInTree, Node* current);
        int leftSideHeight = 0;
        int rightSideHeight = 0;
        int getHeightOverload(Node* current);
        void prettyPrintOverload(std::vector<int> sorted, Node* current);
        int findPosition(std::vector<int> sorted, int wishedValue);
};

BST::BST(){};

BST::~BST(){

    nodeRemover(root);
}

void BST::nodeRemover(Node* current){

    if(root == nullptr){}
    else{
        if(current->leftSubtree != nullptr){
            nodeRemover(current->leftSubtree);
        }
        if(current->rightSubtree != nullptr){
            nodeRemover(current->rightSubtree);
        }
        delete current;
    }
}

void BST::insertKey(int newKey){

    insertKeyOverload(newKey, root);
}

void BST::insertKeyOverload(int newKey, Node* current){

    if(root == nullptr){
        root = new Node(newKey);
    }
    else if(newKey < current->value){
        if(current->leftSubtree != nullptr){
            current = current->leftSubtree;
            insertKeyOverload(newKey, current);
        }
        else current->leftSubtree = new Node(newKey);
    }
    else{
        if(current->rightSubtree != nullptr){
            current = current->rightSubtree;
            insertKeyOverload(newKey, current);
        }
        else current->rightSubtree = new Node(newKey);
    }
}

bool BST::hasKey(int searchKey){
    
    bool result = hasKeyOverload(searchKey, root);
    return result;
}

bool BST::hasKeyOverload(int searchKey, Node* current){

    if(root == nullptr){
        return false;
    }

    if(searchKey == current->value){
        return true;
    }
    else{
        if(current->leftSubtree != nullptr and searchKey < current->value){
            current = current->leftSubtree;
            if (hasKeyOverload(searchKey, current) == true){
                return true;
            }
        }
        else if(current->rightSubtree != nullptr and searchKey > current->value){
            current = current->rightSubtree;
            if (hasKeyOverload(searchKey, current) == true){
                return true;
            } 
        }
        return false;
    }
    return false;
}

std::vector<int> BST::inOrder(std::vector<int> &result){

    inOrderOverload(allValuesInTree, root);
    return allValuesInTree;
}

void BST::inOrderOverload(std::vector<int> &allValuesInTree, Node* current){

    if(root == nullptr){
        return ;
    }
    else{
        if(current->leftSubtree != nullptr){
            inOrderOverload(allValuesInTree, current->leftSubtree); 
        }
        allValuesInTree.push_back(current->value);

        if(current->rightSubtree != nullptr){
            inOrderOverload(allValuesInTree, current->rightSubtree);
        }
        return ;
    }
    return ;
}

int BST::getHeight(){

    return getHeightOverload(root);
}

int BST::getHeightOverload(Node* current){

    if(root == nullptr){
        return 0;
    }
    else{
        if(current->leftSubtree != nullptr){
            leftSideHeight = getHeightOverload(current->leftSubtree);
        }
        else leftSideHeight = 0;

        if(current->rightSubtree != nullptr){
            rightSideHeight = getHeightOverload(current->rightSubtree);   
        }
        else rightSideHeight = 0;   

        if(leftSideHeight >= rightSideHeight){
            leftSideHeight++;
            return leftSideHeight;
        }
        else if(leftSideHeight < rightSideHeight){
            rightSideHeight++;
            return rightSideHeight;
        }
        return 0;
    }
    return 0;
}

void BST::prettyPrint(){

    std::vector<int> sorted = inOrder(sorted);
    sorted.resize(sorted.size() / 2);
    prettyPrintOverload(sorted, root);
}

void BST::prettyPrintOverload(std::vector<int> sorted, Node* current){

    if(root == nullptr){
        return;
    }
    else{
        std::cout << std::setfill('-') << std::setw(5 * sorted.size() + 1) << "" << std::endl;
        std::cout << std::setfill(' ');
        bool over = false;
        std::queue<Node*> pointersInTree;
        std::queue<int> valuesInLevel;
        pointersInTree.push(current);
        pointersInTree.push(nullptr);
        do{
            current = pointersInTree.front();
            pointersInTree.pop();
            if(current == nullptr){
                int index;
                for(int i = 0; i < sorted.size(); i++){
                    if(valuesInLevel.empty() != true){
                        int searchingValue = valuesInLevel.front();
                        if(index = findPosition(sorted, searchingValue) != i){ 
                            std::cout << "|" << std::setw(5);
                        }
                        else{
                            std::cout << "|" << std::setw(4) << std::right << sorted.at(i);
                            valuesInLevel.pop();
                        }
                    }
                    else std::cout << "|" << std::setw(5);
                }
                std::cout << "|" << std::endl;
                std::cout << std::setfill('-') << std::setw(5 * sorted.size() + 1) << "" << std::endl;
                std::cout << std::setfill(' ');
                if(pointersInTree.empty() == true){
                    over = true;
                }
                else pointersInTree.push(nullptr);
            }
            else{
                valuesInLevel.push(current->value);
                if(current->leftSubtree != nullptr){
                    pointersInTree.push(current->leftSubtree);
                }
                if(current->rightSubtree != nullptr){
                    pointersInTree.push(current->rightSubtree);
                }
            }
        }while(over != true);
    }
}

int BST::findPosition(std::vector<int> sorted, int wishedValue){
    
    for(int i = 0; i < sorted.size(); i++){
        if(wishedValue == sorted.at(i)){
            return i;
        }
    }
    return -1;
}

int main(){

    int input, wishedNum;
    BST bst;
    std::cout << "Enter the numbers to be stored: ";
    
    while(std::cin >> input){
        bst.insertKey(input);
    }
    std::cin.clear();
    std::cin.ignore(1, '\n');

    std::cout << "The numbers in sorted order: ";
    std::vector<int> result = bst.inOrder(result);
    for(int i = 0; i < result.size(); i++){
        std::cout << result.at(i) << " ";
    }

    bst.prettyPrint();

    return 0; 
}
