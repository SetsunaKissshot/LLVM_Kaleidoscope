# LLVM_Kaleidoscope
```cpp
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

void printTypeInfo(MonoClass* klass) {
  const char* name = mono_class_get_name(klass);
  const char* namespace = mono_class_get_namespace(klass);

  printf("Class name: %s\n", name);
  printf("Namespace: %s\n", namespace);

  void* iter = NULL;
  MonoMethod* method;
  while ((method = mono_class_get_methods(klass, &iter))) {
    printf("Method name: %s\n", mono_method_get_name(method));
  }
}

int main() {
  mono_jit_init_version("myapp", "v4.0.30319");

  MonoDomain* domain = mono_domain_get();
  MonoAssembly* assembly = mono_domain_assembly_open(domain, "MyAssembly.dll");
  MonoImage* image = mono_assembly_get_image(assembly);

  MonoClass* klass = mono_class_from_name(image, "MyNamespace", "MyClass");
  printTypeInfo(klass);

  mono_jit_cleanup(domain);
  return 0;
}
```

```cpp
void Compiler::addNestedTypes(std::vector<MonoClass*>& types, MonoClass* type) {
  MonoClass* nestedType;
  void* iter = NULL;

  while ((nestedType = mono_class_get_nested_types(type, &iter))) {
    addNestedTypes(types, nestedType);
    types.push_back(nestedType);
  }
}
```

```cpp
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

int main() {
  mono_jit_init_version("myapp", "v4.0.30319");

  MonoDomain* domain = mono_domain_get();
  MonoAssembly* assembly = mono_domain_assembly_open(domain, "MyAssembly.dll");
  MonoImage* image = mono_assembly_get_image(assembly);

  // Create a new type
  MonoClass* klass = mono_class_from_name(image, "MyNamespace", "MyClass");
  MonoType* type = mono_class_get_type(klass);

  // Create a new method
  MonoMethodDesc* desc = mono_method_desc_new(":MyMethod(int)", false);
  MonoMethod* method = mono_method_desc_search_in_class(desc, klass);
  mono_method_desc_free(desc);

  // Modify the IL code of the method
  // ...

  mono_jit_cleanup(domain);
  return 0;
}
```