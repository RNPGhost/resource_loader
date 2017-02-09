#pragma once

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>


// Event manager that passes event info of type EventInfoType on Trigger
template<typename KeyType, typename ValueType>
class MapStack {
  public:
    void Push(const KeyType key, const ValueType* value) {
      key_stack.push(key);
      map[key] = value;
    }
    ValueType* Pop() {
      int key = key_stack.pop();
      ValueType* value = map[key];
      map[key] = null;
      return value;
    }
    ValueType* Peek() {
      int key = key_stack.top();
      ValueType* value = map[key];
      return value;
    }
    bool Contains(KeyType key) {
      return (map[key] != NULL);
    }
    int Size() {
      return key_stack.size();
    }
  
  private:
    std::stack<int> key_stack;
    unordered_map<KeyType, ValueType*> map;
};

