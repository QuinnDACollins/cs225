/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{

   
   if(s.empty()){
       return 0;
   }
    T top = s.top();
    s.pop();
    T c_sum = top + sum(s);
    s.push(top);
    
    
    return c_sum;
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    if(input.size() == 0){
        return true;
    }
    if(input.back() == '[' || input.front() == ']'){
        return false;
    }

    stack<char> b_stack;
    int s = input.size();
    unsigned brack_count = 0;

    for (int i = 0; i < s; i++){
       if(input.front() == '['){
           b_stack.push(input.front());
           input.pop();
       } else if(input.front() == ']') {
           brack_count += 1;
            if(b_stack.size() == 0 || b_stack.size() < brack_count){
                return false;
            }
           input.push(input.front());
           input.pop();
       } else {
           input.pop();
       }
    }

    if(b_stack.size() == input.size()){
        return true;
    } else {
        return false;
    }
    
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */


template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    // optional: queue<T> q2;
    int q_size = q.size();
    int iter_num = 2;
    q.emplace(q.front());
    q.pop();
    for(int i = 2; i < q_size ; i++){
        if(iter_num + i > q_size){
            for(int x = 0; x <= q_size - iter_num; x++){     
               s.emplace(q.front());
               q.pop();
            }
            int s_size = s.size();
            for(int y = 0; y < s_size; y++){
                q.emplace(s.top());
                s.pop();
            }
            break;
        }
        if(i % 2 != 0){
            for(int x = 0; x < i; x++){
                iter_num +=1;
                std::cout << q.front() << std::endl;
                q.emplace(q.front());
                q.pop();
            }
        } else {
            for(int x = 0; x < i; x++){
                iter_num +=1;
                
               s.emplace(q.front());
               q.pop();

            }

            int s_size = s.size();
            for(int y = 0; y < s_size; y++){
                q.emplace(s.top());
                s.pop();
            }
        }

    // Your code here
    }
}

}