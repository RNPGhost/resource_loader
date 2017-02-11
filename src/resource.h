#pragma once

#include <string>
#include <vector>

class Loader;

class Resource {
 public:
  Resource(std::string id, 
           std::vector<std::string> dependency_ids,
           Loader* loader);
  bool operator==(Resource resource) const;
  void RequestLoad();
  const std::vector<std::string> dependency_ids;
  const std::string id;
 private:
  Loader* loader_;
};
