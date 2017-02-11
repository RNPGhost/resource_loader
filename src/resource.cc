#include "resource.h"

Resource(std::string resource_id) {
  Resource::id = resource_id;
}

bool Resource::operator==(Resource resource) const {
  return (resource.id == Resource::id);
}

void Resource::RequestLoad() { 
  std::cout << "-- Resource Load Requested: " << Resource::id << " --\n";
}

