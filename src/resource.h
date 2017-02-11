#pragma once

#include <string>
#include <vector>

class Resource {
 public:
  Resource(std::string resource_id);
  bool operator==(Resource resource) const;
  void RequestLoad();
  std::vector<std::string> dependency_ids;
  std::string id;
};
