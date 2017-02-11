#include "resource.h"
#include "loader.h"

Resource::Resource(std::string id, 
                   std::vector<std::string> dependency_ids, 
                   Loader* loader) 
    : dependency_ids(dependency_ids),
      id(id),
      loader_(loader)
{}

bool Resource::operator==(Resource resource) const {
  return (resource.id == id);
}

void Resource::RequestLoad() {
  loader_->RequestLoad(id);
}
