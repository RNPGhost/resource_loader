#include "resource.h"

#include <iostream>

Resource::Resource(std::string resource_id) {
  id = resource_id;
}

bool Resource::operator==(Resource resource) const {
  return (resource.id == id);
}

void Resource::RequestLoad() { 
  std::cout << "-- Resource Load Requested: " << id << " --\n";
}
