#include "resource.h"
#include "loader.h"

int main() {
  Loader loader;

  Resource resource_1 ("resource_1",{"resource_2", "resource_2"}, &loader);
  loader.AddResource(&resource_1);

  Resource resource_2 ("resource_2", {"resource_1"}, &loader);
  loader.AddResource(&resource_2);

  loader.FindAndLoadDependencies("resource_1");

  Resource new_resource_2 ("resource_2", {}, &loader);
  loader.AddResource(&new_resource_2);

  loader.FindAndLoadDependencies("resource_1");
}
