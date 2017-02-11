#include "loader.h"

Resource* Loader::GetResourceByID(std::string id) {
  return resources_[id];
}
