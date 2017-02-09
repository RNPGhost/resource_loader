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
    key_stack.push(key);
    map[key] = value;
  }
  ValueType* Pop() {
    ValueType* value = Peek();
    key_stack.pop();
    map.erase(key);
    return value;
  }
  ValueType* Peek() {
    KeyType key = key_stack.top();
    ValueType* value = map[key];
    return value;
  }
  bool Contains(KeyType key) {
    return (map.count(key) > 0);
  }
  size_t Size() {
    return key_stack.size();
  }
  
 private:
  std::stack<KeyType> key_stack_;
  std::unordered_map<KeyType, ValueType*> map_;
};

