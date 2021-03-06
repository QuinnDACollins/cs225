#include <stack>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return NULL;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
//@todo Graded in MP3.1
  ListNode *cur = head_;
    while(length_ != 0 && cur != NULL){
      ListNode*temp = cur->next;
      delete cur;
      cur = temp;
      length_ -=1;
    }
  }


/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  newNode -> next = head_;
  newNode -> prev = NULL;
  
   if(length_ != 0){    
    head_->prev = newNode;
  } else {
    tail_ = newNode;
  }

  head_ = newNode;
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if(length_ != 0){    
    tail_->next = newNode;
  } else {
    head_ = newNode;
  }
  tail_ = newNode;
  

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  //length_ = splitPoint;

  ListNode * split_node = _index_helper(splitPoint, start);
  tail_ = split_node->prev;
  tail_->next = NULL;

  split_node->prev = NULL;
  
  return split_node;
}
template <typename T>
typename List<T>::ListNode *&List<T>::_index_helper(int index, ListNode *& node) {
  if(index == 0){
    return node;
  } else {
    return _index_helper(index - 1, node -> next);
  }

}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  //ListNode *temp = head_;
  int numRotates = floor(length_ / 3);
  ListNode *temp = head_;


  if(length_ >= 3){
    ListNode* first = head_;
    ListNode* second = first->next;
    temp = second;
    ListNode* third = second->next;
    ListNode * fourth = third->next;
    


    second->prev = NULL;
    first->prev = third;
    third->next = first;
    first->next = fourth;

    for(unsigned i = 1; (int)i < numRotates; i+=1){
      first = first->next;
      second = first->next;
      third = second->next;
      fourth = third->next;

    

      first->prev->next->next = second;
      second->prev = first->prev;
      first->prev = third;
      third->next = first;
      first->next = fourth;
    }
    tail_ = first;
    head_ = temp;
  } else {
    return;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  List<T> s_list = List();
  ListNode*n = startPoint;

  if(startPoint == head_){
    head_ = endPoint;
  } else {
    ListNode *hn = head_;
    while(hn != startPoint){
      s_list.insertBack(hn->data);
      hn = hn ->next;
    }
  }
  
  
  std::stack<T> s;
  while(n != endPoint->next && n != NULL){
    s.push(n->data);
    n = n->next;
  }
  while(!s.empty()){
    s_list.insertBack(s.top());
    s.pop();
  }

  if(endPoint == tail_){
    tail_ = startPoint;
  } else {
    ListNode* en = endPoint;
    while(en != NULL){
      s_list.insertBack(en->data);
      en = en->next;
    }
  }
  std::cout <<"TEST" << std::endl;
  *this = List(s_list);


}



/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /*ListNode* cur = head_;
  for(int i = 0; i < floor(length_ / n); i++){
    int t = 0;
    while(t < (n * i)){
      cur = cur->next;
      t += 1;
    } 
    ListNode*temp = cur;
    while(t < (n+1) * i){
      cur = cur->next;
      t += 1;
    }
    reverse(temp, cur);
  } */
  return;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  return NULL;
 /* /// @todo Graded in MP3.2
  ListNode* start = min_node(first, second);
  bool first = true;
  if(start != first){
    first = false;
  }

  start->next = max_node(first, second);

  ListNode* f_c = first->next;
  ListNode* s_c = second->next;

  ListNode* cur = start->next;
  if(first == true){
    while(cur != NULL && s_c != NULL){
      if(min_node(cur->next, s_c) == cur->next){
        cur = cur->next;
        cur = s_c;
        s_c = s_c->next;
      } else if(min_node(cur->next, s_c) == s_c){
        cur = cur->next;
        cur
      }
    }
  } 
}

  if(f_c == NULL){
    cur->next = s_c;
  } else if(s_c == NULL){
    cur->next = f_c;
  }
  return start;*/
}

template <typename T>
typename List<T>::ListNode *List<T>::min_node(ListNode * first, ListNode* second){
  if(first->data > second){
    return second;
  } else if(first == second){
    return first;
  } else {
    return first;
  }
}
template <typename T>
typename List<T>::ListNode *List<T>::max_node(ListNode * first, ListNode* second){
  if(first->data > second){
    return first;
  } else if(first == second){
    return first;
  } else {
    return second;
  }
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  return NULL;
}
