#include "map_stack.h"
#include <iostream>
#include <stack>
#include <unordered_map>

struct Resource {
 public:
  const char* GetID() { return id_; }
  bool operator==(Resource resource) {
    return (resource.id == id);
  }
  std::vector<Resource> dependencies [0];
  int dependencies_size = 0;
 private:
  const char* id_;
};

int main() {
}

void SubmitResourcesForLoading(Resource resource) {
  std::stack<Resource> not_loaded;
  std::unordered_map<const char*, Resource> loaded;
  MapStack<int, Resource> dependency_chain;

  not_loaded.push(resource);
  Resource current_resource;

  while (not_loaded.size() > 0) {
    current_resource = not_loaded.top();
    
    // if current resource has been added to the dependency chain,
    // it's dependencies have been submitted to be loaded,
    // so we can submit the current resource for loading
    if (dependency_chain.Size() > 0 &&
        dependency_chain.Peek() == current_resource)) {
      loaded.push(current_resource.GetID(), current_resource);
      not_loaded.pop();
      dependency_chain.Pop();
      // AddToLoadQueue(current_resource);
    }

    // otherwise, add unloaded dependencies of the current resource
    // to the not_loaded stack
    for (const Resource& dependency : current_resource.dependencies) {
      // if dependency appears in the dependency chain,
      // there must be a dependency loop
      if (dependency_chain.Contains(dependency) {
        // bad things
        return;
      }
      if (!loaded.Contains(dependency) {
        not_loaded.push(dependency);
      }
    }
    // once all dependencies have been submitted to be loaded,
    // the current resource must be added to the dependency chain
    // in order to catch dependency loops
    dependency_chain.Push(current_resource.GetID(), current_resource);
  }
}
