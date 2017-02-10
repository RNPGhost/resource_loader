#include "set_stack.h"
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Resource {
 public:
  Resource(std::string resource_id) {
    id = resource_id;
  }
  bool operator==(Resource resource) const {
    return (resource.id == id);
  }
  bool LoadRequested() const {
    return load_requested_;
  }
  void RequestLoad() {
    load_requested_ = true;
    std::cout << "Resource Load Requested: " << id << "\n";
  }
  std::vector<std::string> dependency_ids;
  std::string id;
 private:
  bool load_requested_ = false;
};

std::unordered_map<std::string, Resource*> resources;

Resource* GetResourceByID(std::string resource_id) {
  return resources[resource_id];
}

void SubmitResourcesForLoading(std::string resource_id) {
  std::stack<std::string> not_loaded;
  SetStack<std::string> dependency_chain;

  not_loaded.push(resource_id);
  std::string current_resource_id;
  Resource* current_resource;

  while (not_loaded.size() > 0) {
    current_resource_id = not_loaded.top();
    current_resource = GetResourceByID(current_resource_id);

    // if current resource has been added to the dependency chain,
    // it's dependencies have been submitted to be loaded,
    // so we can submit the current resource for loading
    if (dependency_chain.Size() > 0 &&
        dependency_chain.Top() == current_resource_id) {
      not_loaded.pop();
      dependency_chain.Pop();
      // load request is only skipped in the event that
      // a resource dependency list contains two identical ids
      if (!current_resource->LoadRequested()) {
        current_resource->RequestLoad();
      }
    
    } else {
      // otherwise, add unloaded dependencies of the current resource
      // to the not_loaded stack
      for (const std::string dependency_id : current_resource->dependency_ids) {
        // if dependency appears in the dependency chain,
        // // there must be a dependency loop
        if (dependency_chain.Contains(dependency_id)) {
          // bad things
          std::cout << "Circular dependency detected. Exiting." << "\n";
          return;
        }
        if (!(GetResourceByID(dependency_id)->LoadRequested())) {
          not_loaded.push(dependency_id);
        }
      }
      // once all dependencies have been submitted to be loaded,
      // the current resource must be added to the dependency chain
      // in order to catch dependency loops
      dependency_chain.Push(current_resource_id);
    }
  }
}

int main() {
  Resource resource_1 ("resource_1");
  Resource* resource_1_ptr = &resource_1;
  resource_1_ptr->dependency_ids.push_back("resource_2");
  resource_1_ptr->dependency_ids.push_back("resource_2");
  resources["resource_1"] = resource_1_ptr;

  Resource resource_2 ("resource_2");
  Resource* resource_2_ptr = &resource_2;
  resource_2_ptr->dependency_ids.push_back("resource_1");
  resources["resource_2"] = resource_2_ptr;

  SubmitResourcesForLoading("resource_1");

  resource_2_ptr->dependency_ids.clear();

  SubmitResourcesForLoading("resource_1");
}
