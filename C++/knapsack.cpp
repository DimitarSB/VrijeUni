#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int knapsack(vector<int> &weightOfObjects, vector<int> &valueOfItems, vector<bool> &included, int position, int leftOvers)
{
    int totalValue = 0;
    if (leftOvers == 0 or position == weightOfObjects.size())
    {
        return totalValue;
    }
    else if (leftOvers < weightOfObjects.at(position))
    {
        return knapsack(weightOfObjects, valueOfItems, included, position + 1, leftOvers);
    }
    else if (leftOvers > weightOfObjects.at(position))
    {

        vector<bool> goesNotIn = included;
        vector<bool> goesIn = included;
        goesIn.at(position) = true;
        int totalValueWithOut = knapsack(weightOfObjects, valueOfItems, goesNotIn, position + 1, leftOvers);
        int totalValueWith = knapsack(weightOfObjects, valueOfItems, goesIn, position + 1, leftOvers - weightOfObjects.at(position));
        if (totalValueWith > totalValueWithOut)
        {
            included = goesIn;
            totalValue = totalValueWith;
            return totalValue;
        }
        else if (totalValueWith > totalValueWithOut)
        {
            included = goesNotIn;
            totalValue = totalValueWithOut;
            return totalValue;
        }
    }
    return 0;
}

int main()
{
    vector<bool> included;
    vector<int> weightOfObjects;
    vector<int> valueOfItems;
    int maxWeight;
    int position = 0;
    int leftOvers = maxWeight;

    ifstream inFS;
    inFS.open("knapsack1");
    if (!inFS.is_open())
    {
        cout << "Could not open file knapsack1." << endl;
        return 1; // 1 indicates error
    }
    inFS >> maxWeight;
    int w, v;
    while (!inFS.fail())
    {
        inFS >> w;
        inFS >> v;
        weightOfObjects.push_back(w);
        valueOfItems.push_back(v);
    }
    inFS.close();

    cout << "With a capacity of " << maxWeight;
    cout << " kg, the total value is " << knapsack(weightOfObjects, valueOfItems, included, position, leftOvers);
    cout << " Eur, leading to a total weight of " << maxWeight << " kg The following items are included:" << endl;

    return 0;
}