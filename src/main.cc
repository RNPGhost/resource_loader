#include "map_stack.h"
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

struct Resource {
  bool operator==(Resource resource) const {
    return (resource.id == id);
  }
  std::vector<Resource> dependencies;
  const std::string id;
};

int main() {
}

void SubmitResourcesForLoading(Resource resource) {
  std::stack<Resource> not_loaded;
  std::unordered_map<std::string, Resource> loaded;
  MapStack<std::string, Resource> dependency_chain;

  not_loaded.push(resource);
  Resource current_resource;

  while (not_loaded.size() > 0) {
    current_resource = not_loaded.top();
    
    // if current resource has been added to the dependency chain,
    // it's dependencies have been submitted to be loaded,
    // so we can submit the current resource for loading
    if (dependency_chain.Size() > 0 &&
        *dependency_chain.Peek() == current_resource) {
      loaded[current_resource.id] = current_resource);
      not_loaded.pop();
      dependency_chain.Pop();
      // AddToLoadQueue(current_resource);
    }

    // otherwise, add unloaded dependencies of the current resource
    // to the not_loaded stack
    for (const Resource& dependency : current_resource.dependencies) {
      // if dependency appears in the dependency chain,
      // there must be a dependency loop
      if (dependency_chain.Contains(dependency.id)) {
        // bad things
        return;
      }
      if (loaded.count(dependency.id) > 0) {
        not_loaded.push(dependency);
      }
    }
    // once all dependencies have been submitted to be loaded,
    // the current resource must be added to the dependency chain
    // in order to catch dependency loops
    dependency_chain.Push(current_resource.id, current_resource);
  }
}
