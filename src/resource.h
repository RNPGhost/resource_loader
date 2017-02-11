#pragma once

#include <string>
#include <vector>

class Loader;

class Resource {
 public:
  Resource(std::string resource_id, Loader* loader);
  bool operator==(Resource resource) const;
  void RequestLoad();
  std::vector<std::string> dependency_ids;
  std::string id;
 private:
  Loader* loader_;
};
