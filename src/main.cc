#include "resource.h"
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::unordered_map<std::string, Resource*> resources;

Resource* GetResourceByID(std::string resource_id) {
  return resources[resource_id];
}

void SubmitResourcesForLoading(std::string resource_id) {
  // contains resources that are currently known to be required
  // but that haven't requested loading
  std::stack<std::string> not_loaded;
  // contains resources that have had their dependencies expanded
  // but haven't requested loading
  std::unordered_set<std::string> dependency_chain;
  // contains resources that are currently known to be required
  std::unordered_set<std::string> load_required;

  not_loaded.push(resource_id);
  std::string current_resource_id;
  Resource* current_resource;

  while (not_loaded.size() > 0) {
    current_resource_id = not_loaded.top();
    current_resource = GetResourceByID(current_resource_id);

    // if the current resource is not in the dependency chain
    // then its dependencies have not yet been expanded
    if (dependency_chain.count(current_resource_id) == 0) {
      // mark fresh dependencies as not loaded
      for (const std::string& dependency_id : current_resource->dependency_ids) {
        // if dependency appears in the dependency chain,
        // there must be a dependency loop
        if (dependency_chain.count(dependency_id) > 0) {
          std::cout << "-- Circular dependency detected: Exiting --\n";
          return;
        }
        // only mark a dependency id as not loaded if
        // it isn't already marked as required
        if (load_required.count(dependency_id) == 0) {
          // all resources marked as not loaded are required
          load_required.insert(dependency_id);
          not_loaded.push(dependency_id);
          std::cout << "added " << dependency_id << " to not_loaded\n";
        }
      }
      // once all dependencies have been marked for loading,
      // the current resource must be added to the dependency chain
      // in order to catch dependency loops
      dependency_chain.insert(current_resource_id);
      std::cout << "added " << current_resource_id << " to dependency_chain\n";

    // otherwise, if the current resource in the dependency chain, 
    // dependencies have already been expanded,
    // so we can request load and discard it
    } else {
      not_loaded.pop();
      dependency_chain.erase(current_resource_id);
      current_resource->RequestLoad();
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
