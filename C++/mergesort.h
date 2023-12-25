#include <iostream>
#include <vector>
using namespace std;

template <typename SortT>
void merge(vector<SortT> &list, unsigned int low, unsigned int mid, unsigned int high){
   
   vector<SortT> temp(list.size());
   unsigned int mergedSize;
   unsigned int mergePos;
   unsigned int leftPos;
   unsigned int rightPos;

   mergePos = 0;
   mergedSize = high - low + 1;
   leftPos = low;
   rightPos = mid + 1;

   while (leftPos <= mid && rightPos <= high){
      if (list.at(leftPos) < list.at(rightPos)){
         temp.at(mergePos) = list.at(leftPos);
         leftPos++;
      }
      else{
         temp.at(mergePos) = list.at(rightPos);
         rightPos++;
      }
      mergePos++;
   }

   while (leftPos <= mid){
      temp.at(mergePos) = list.at(leftPos);
      leftPos++;
      mergePos++;
   }
   while (rightPos <= high){
      temp.at(mergePos) = list.at(rightPos);
      rightPos++;
      mergePos++;
   }
   for (mergePos = 0; mergePos < mergedSize; mergePos++){
      list.at(low + mergePos) = temp.at(mergePos);
   }
}

template <typename T>
void mergeSort(vector<T> &list, unsigned int low, unsigned int high){

   if (low < high){
      unsigned int mid = low + (high - low) / 2;
      mergeSort(list, low, mid);
      mergeSort(list, mid + 1, high);
      merge(list, low, mid, high);
   }
}
