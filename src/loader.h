#pragma once

#include "resource.h"
#include <string>
#include <unordered_map>

class Loader {
 public:
  Resource* GetResourceByID(std::string id);
 private:
  std::unordered_map<std::string, Resource*> resources_;
}
