#include "resource.h"
#include "loader.h"

Resource::Resource(std::string resource_id, Loader* loader) {
  id = resource_id;
  loader_ = loader; 
}

bool Resource::operator==(Resource resource) const {
  return (resource.id == id);
}

void Resource::RequestLoad() {
  loader_->RequestLoad(id);
}
