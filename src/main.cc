#include "resource.h"
#include "loader.h"

int main() {
  Loader loader;

  Resource resource_1 ("resource_1");
  resource_1.dependency_ids.push_back("resource_2");
  resource_1.dependency_ids.push_back("resource_2");
  loader.AddResource(&resource_1);

  Resource resource_2 ("resource_2");
  resource_2.dependency_ids.push_back("resource_1");
  loader.AddResource(&resource_2);

  loader.SubmitResourcesForLoading("resource_1");

  resource_2.dependency_ids.clear();

  loader.SubmitResourcesForLoading("resource_1");
}
