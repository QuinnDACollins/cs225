
#include "dsets.h"
#include <iostream>
using namespace std;
void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i ++){
        uptree.push_back(-1);
    }
}

int DisjointSets::find(int elem){
        if(uptree[elem] <= -1){
            return elem;
        } else {
            return find(uptree[elem]);
        }
}

int DisjointSets::size(int elem){
    return(-1 * uptree[find(elem)]);
}

void DisjointSets::setunion(int a, int b){
    int a_parent = find(a);
    int b_parent = find(b);
    if(size(b_parent) > size(a_parent)){
        uptree[b_parent] -= size(a_parent);
        uptree[a_parent] = b_parent;
       

    } else {
        uptree[a_parent] -= size(b_parent);
        uptree[b_parent] = a_parent;
        
    }
}

int DisjointSets::next(int elem){
    return uptree[elem];
}

bool DisjointSets::in_bounds(int elem){
    return elem < (int)uptree.size() - 1;
}