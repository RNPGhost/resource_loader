#pragma once

#include "resource.h"
#include <string>
#include <unordered_map>

class Loader {
 public:
  Resource* GetResourceByID(std::string id);
  void FindAndLoadDependencies(std::string resource_id);
  void AddResource(Resource* resource);
  void RequestLoad(std::string resource_id);
 private:
  std::unordered_map<std::string, Resource*> resources_;
};
