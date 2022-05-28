#include "Queue.h"

Queue::Queue() { 
  vector = {};
}

Queue::~Queue(){
  vector.clear();
}

// `int size()` - returns the number of elements in the stack (0 if empty)
int Queue::size() const {
  return vector.size();
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const {
  return vector.empty();
}

// `void enqueue(int val)` - enqueue an item to the queue in O(1) time
void Queue::enqueue(int value) {
    vector.push_back(value);

}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue() {
    if(vector.size() != 0){
    vector.erase(vector.begin());
    return vector.at(0);
    } else {
      return 0;
    }
}
