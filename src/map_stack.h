#pragma once

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>


// Event manager that passes event info of type EventInfoType on Trigger
template<typename KeyType, typename ValueType>
class MapStack {
 public:
  void Push(KeyType key, ValueType* value) {
    key_stack_.push(key);
    map_[key] = value;
  }
  ValueType* Pop() {
    KeyType key = key_stack_.top();
    ValueType* value = map_[key];
    key_stack_.pop();
    map_.erase(key);
    return value;
  }
  ValueType* Peek() {
    KeyType key = key_stack_.top();
    ValueType* value = map_[key];
    return value;
  }
  bool Contains(KeyType key) {
    return (map_.count(key) > 0);
  }
  size_t Size() {
    return key_stack_.size();
  }
  
 private:
  std::stack<KeyType> key_stack_;
  std::unordered_map<KeyType, ValueType*> map_;
};

