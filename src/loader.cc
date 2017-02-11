#include "loader.h"

Resource* Loader::GetResourceByID(std::string id) {
  return Loader::resources_[id];
}
