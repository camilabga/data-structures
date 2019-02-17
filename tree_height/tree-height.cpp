#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node {
public:
    int key;
    Node *parent;
    vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;

  Node nodes[n];
  Node *root;
  int parent_index;
  for (int child_index = 0; child_index < n; child_index++){
    cin >> parent_index;
    if (parent_index >= 0){
      nodes[child_index].setParent(&nodes[parent_index]);
      nodes[child_index].key = child_index;
    } else {
      nodes[child_index].key = child_index;
      root=&nodes[child_index];
    }
  }

  stack<Node *> count_nodes;
  count_nodes.push(root);
  int max_height=0, current_height=0;

  Node *node;

  while(!count_nodes.empty()){
    current_height++;
    if (current_height > max_height) max_height = current_height;

    node = count_nodes.top();
    count_nodes.pop();

    if (node->children.size()==0) current_height--;

    for (auto iter = node->children.begin(); iter < node->children.end(); iter++)
      count_nodes.push(*iter);
  }

  cout << max_height << endl;

  return 0;
}

int main (int argc, char **argv){
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0){
      if (rl.rlim_cur < kStackSize){
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0){
            cerr << "setrlimit returned result = " << result << endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
