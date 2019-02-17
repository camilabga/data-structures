#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cassert>
#include <algorithm>

using namespace std;

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    int value;

    stack <int> stack_main;
    stack <int> max_stack;

    for (int i = 0; i < num_queries; i++){
        cin >> query;
        if (query == "push"){
            cin >> value;

            if (stack_main.empty()) {
                stack_main.push(value);
                max_stack.push(value);
            } else {
                if (value > max_stack.top()) {
                    max_stack.push(value);
                } else {
                    max_stack.push(max_stack.top());
                }
                stack_main.push(value);
            }
        } else if (query == "pop") {
            stack_main.pop();
            max_stack.pop();
        } else if (query == "max") {
            cout << max_stack.top() << endl;
        } else {
            assert(0);
        }
    }    

    return 0;
}