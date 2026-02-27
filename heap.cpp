// heap.cpp
// Diba Mirza

#include "heap.h"
#include <iostream>
#include <cmath>
#define DEBUG false
#define LOG(x) if (DEBUG) { std::cout << "[DEBUG] " << x << std::endl; }

using std::cout;

// Builds a heap from the range [start, end) using the heapify algorithm
// Should run in O(n) time
Heap::Heap(std::vector<int>::iterator start, std::vector<int>::iterator end){
  vdata.assign(start,end);
  int size = distance(vdata.begin(), vdata.end());
  int start_p = size/2 - 1;
  LOG("size: " << size << ", start_p: " << start_p);

  for(int index = start_p; index >= 0; index--){
    int curr = index;
    LOG(index);

    while(size - 1>= 2 * curr + 1 || size - 1>= 2 * curr + 2){
      int left_p = 2 * curr + 1;
      int right_p = 2 * curr + 2;

      if(size - 1 >= left_p && size - 1 >= right_p){
        LOG("left_p: " << left_p << ", right_p: " << right_p << ", vdata[curr]: " << vdata[curr] << ", vdata[right_p]: " << vdata[right_p] << ", vdata[left_p]: " << vdata[left_p]);

        int min_val = std::min(vdata[right_p], vdata[left_p]);
        if(vdata[curr] > min_val){
          LOG("For loop iteration: " << (start_p - index) << ", index: " << index << ", min_val: " << min_val);
          int temp = vdata[curr];

          if(min_val == vdata[right_p]){
            vdata[curr] = vdata[right_p];
            vdata[right_p] = temp;
            curr = right_p;
            LOG("curr updated to " << curr << " (right child)");

          }else{
            vdata[curr] = vdata[left_p];
            vdata[left_p] = temp;
            curr = left_p;
            LOG("curr updated to " << curr << " (left child)");
          }
        } else {
            break;
        }

      }else if(size - 1 >= left_p ){
        LOG("Inside else if block (one child case): left_p = " << left_p);
        if(vdata[curr] > vdata[left_p]){
            LOG("Swapping curr (" << vdata[curr] << ") with left_p (" << vdata[left_p] << ")");
            int temp = vdata[curr];
            vdata[curr] = vdata[left_p];
            vdata[left_p] = temp;
            curr = left_p;
            LOG("curr updated to " << curr);
        }
        if(vdata[curr] < vdata[left_p]){
          break;
        }
    }
    
  }

}

}

// Pushes a value into the heap, then ensures
// the heap is correctly arranged
void Heap::push(int value){
  vdata.push_back(value);

  if(vdata.size() == 1){
    return;
  }

  LOG("vdata size: " << vdata.size());
  int values_index = vdata.size() - 1;
  int values_parent_index = (std::floor(values_index - 1) / 2);
  // cout << "values_parent_indexf: " << values_parent_index << ", values_index: " << values_index << std::endl;
  
  while(vdata[values_parent_index] > vdata[values_index]){
  // cout << "values_parent_index: " << values_parent_index << ", values_index: " << values_index << std::endl;
    vdata[values_index] = vdata[values_parent_index];
    vdata[values_parent_index] = value;
    values_index = values_parent_index;
    values_parent_index  = (values_index - 1)/2;
    if(values_index > vdata.size() || values_parent_index > vdata.size()){
      break;
    }
}
}

// Pops the minimum value off the heap
// (but does not return it), then ensures
// the heap is correctly arranged
void Heap::pop(){
  if(vdata.size() == 0) return;
  vdata[0] = vdata.back();
  vdata.pop_back();
  int current_index = 0;
  while(true){
    int left_child_index  = 2 * current_index + 1;
    int right_child_index = 2 * current_index + 2;
    bool has_left  = left_child_index  < (int)vdata.size();
    bool has_right = right_child_index < (int)vdata.size();
    if(!has_left) break;  
    int smallest_index = left_child_index;
    if(has_right && vdata[right_child_index] < vdata[left_child_index]){
      smallest_index = right_child_index;
    }
    if(vdata[current_index] > vdata[smallest_index]){
      std::swap(vdata[current_index], vdata[smallest_index]);
      current_index = smallest_index;
    } else {
      break;  
    }
  }
}

// Returns the minimum element in the heap
int Heap::top(){
  return vdata[0];
}

// Returns true if the heap is empty, false otherwise
bool Heap::empty(){
  return vdata.empty();
}
    