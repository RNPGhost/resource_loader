#pragma once

#include <stack>
#include <unordered_set>


// Event manager that passes event info of type EventInfoType on Trigger
template<typename T>
class SetStack {
 public:
  void Push(T value) {
    stack_.push(value);
    set_.insert(value);
  }
  void Pop() {
    set_.erase(stack_.top());
    stack_.pop();
  }
  T& Top() {
    return stack_.top();
  }
  bool Contains(T value) {
    return (set_.count(value) > 0);
  }
  size_t Size() {
    return stack_.size();
  }
  
 private:
  std::stack<T> stack_;
  std::unordered_set<T> set_;
};

