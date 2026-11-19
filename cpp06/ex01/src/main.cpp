#include <iostream>

#include "Data.hpp"
#include "Serializer.hpp"

static void testRoundTrip() {
  std::cout << "--- round trip ---\n";

  Data data;
  data.name = "forty-two";
  data.value = 42;

  uintptr_t raw = Serializer::serialize(&data);
  Data* ptr = Serializer::deserialize(raw);

  std::cout << "original:     " << &data << "\n";
  std::cout << "serialized:   " << std::hex << std::showbase << raw << std::dec
            << "\n";
  std::cout << "deserialized: " << ptr << "\n";
  std::cout << "equal:        " << (ptr == &data ? "true" : "false") << "\n";
}

static void testMembers() {
  std::cout << "--- members through the deserialized pointer ---\n";

  Data data;
  data.name = "forty-two";
  data.value = 42;

  Data* ptr = Serializer::deserialize(Serializer::serialize(&data));

  std::cout << "read:  " << ptr->name << ", " << ptr->value << "\n";

  ptr->value = 21;
  std::cout << "write: data.value is now " << data.value << "\n";
}

static void testNull() {
  std::cout << "--- null pointer ---\n";

  Data* ptr = Serializer::deserialize(Serializer::serialize(NULL));

  std::cout << "equal: " << (ptr == NULL ? "true" : "false") << "\n";
}

int main() {
  testRoundTrip();
  testMembers();
  testNull();
  return 0;
}
