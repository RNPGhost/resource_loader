#pragma once

#include "resource.h"
#include <unordered_map>

class Loader {
 public:
  Resource* GetResourceByID(std::string id);
 private:
  unordered_map<std::string, Resource*> resources_;
}
