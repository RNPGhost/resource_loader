#include "set_stack.h"
#include <iostream>
#include <stack>
#include <string>
#include <vector>

struct Resource {
  Resource(std::string resource_id) {
    id = resource_id;
  }
  bool operator==(Resource resource) const {
    return (resource.id == id);
  }
  bool IsLoadRequested() const {
    return false;
  }
  std::vector<std::string> dependency_ids;
  std::string id;
};

int main() {
}

Resource GetResourceByID(std::string resource_id) {
  return Resource("resource_1");
}

void SubmitResourcesForLoading(std::string resource_id) {
  std::stack<std::string> not_loaded;
  SetStack<std::string> dependency_chain;

  not_loaded.push(resource_id);
  std::string current_resource_id;

  while (not_loaded.size() > 0) {
    current_resource_id = not_loaded.top();
    
    // if current resource has been added to the dependency chain,
    // it's dependencies have been submitted to be loaded,
    // so we can submit the current resource for loading
    if (dependency_chain.Size() > 0 &&
        dependency_chain.Top() == current_resource_id) {
      not_loaded.pop();
      dependency_chain.Pop();
      // AddToLoadQueue(current_resource_id);
    } else {
      // otherwise, add unloaded dependencies of the current resource
      // to the not_loaded stack
      Resource current_resource = GetResourceByID(current_resource_id);
      for (const Resource& dependency : current_resource.dependency_ids) {
        // if dependency appears in the dependency chain,
        // // there must be a dependency loop
        if (dependency_chain.Contains(dependency.id)) {
          // bad things
          return;
        }
        if (!GetResourceByID(dependency.id).IsLoadRequested()) {
          not_loaded.push(dependency.id);
        }
      }
      // once all dependencies have been submitted to be loaded,
      // the current resource must be added to the dependency chain
      // in order to catch dependency loops
      dependency_chain.Push(current_resource.id);
    }
  }
}
