#include "set_stack.h"
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Resource {
 public:
  Resource(std::string resource_id) {
    id = resource_id;
  }
  bool operator==(Resource resource) const {
    return (resource.id == id);
  }
  void RequestLoad() {
    std::cout << "-- Resource Load Requested: " << id << " --\n";
  }
  std::vector<std::string> dependency_ids;
  std::string id;
};

std::unordered_map<std::string, Resource*> resources;

Resource* GetResourceByID(std::string resource_id) {
  return resources[resource_id];
}

void SubmitResourcesForLoading(std::string resource_id) {
  std::stack<std::string> not_loaded;
  SetStack<std::string> dependency_chain;
  std::unordered_set<std::string> load_required;

  not_loaded.push(resource_id);
  std::string current_resource_id;
  Resource* current_resource;

  while (not_loaded.size() > 0) {
    current_resource_id = not_loaded.top();
    current_resource = GetResourceByID(current_resource_id);

    // if current resource has been added to the dependency chain,
    // it's dependencies must already have been loaded
    // so we can submit the current resource for loading
    if (dependency_chain.Size() > 0 &&
        dependency_chain.Top() == current_resource_id) {
      not_loaded.pop();
      dependency_chain.Pop();
      current_resource->RequestLoad();
    } else {
      // otherwise, mark fresh dependencies as not loaded
      for (const std::string dependency_id : current_resource->dependency_ids) {
        // if dependency appears in the dependency chain,
        // there must be a dependency loop
        if (dependency_chain.Contains(dependency_id)) {
          std::cout << "-- Circular dependency detected: Exiting --\n";
          return;
        }
        // only mark a dependency id as not loaded if
        // it isn't already marked as required
        if (load_required.count(dependency_id) == 0) {
          load_required.insert(dependency_id);
          not_loaded.push(dependency_id);
          std::cout << "added " << dependency_id << " to not_loaded\n";
        }
      }
      // once all dependencies have been marked for loading,
      // the current resource must be added to the dependency chain
      // in order to catch dependency loops
      dependency_chain.Push(current_resource_id);
      std::cout << "added " << current_resource_id << " to dependency_chain\n";
    }
  }
}

int main() {
  Resource resource_1 ("resource_1");
  resource_1.dependency_ids.push_back("resource_2");
  resource_1.dependency_ids.push_back("resource_2");
  resources["resource_1"] = &resource_1;

  Resource resource_2 ("resource_2");
  resource_2.dependency_ids.push_back("resource_1");
  resources["resource_2"] = &resource_2;

  SubmitResourcesForLoading("resource_1");

  resource_2.dependency_ids.clear();

  SubmitResourcesForLoading("resource_1");
}
