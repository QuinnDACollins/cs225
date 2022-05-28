#pragma once

#include <cstddef>
#include <vector>
class Queue {
    public:
        Queue();
        ~Queue();
        std::vector<int> vector;
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
};