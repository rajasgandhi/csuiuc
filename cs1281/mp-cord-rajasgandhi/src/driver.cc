#include <iostream>

#include "cord.hpp"
#include "cord_utilities.hpp"

int main() {
  SharedPointer<Cord> a = new Cord("CS_");
  SharedPointer<Cord> b = new Cord("128_");
  SharedPointer<Cord> c = ConcatCords(a, b);

  auto c_str = c->ToString();
  std::cout << c_str.Get() << std::endl;

  auto res = SubString(c, 0, 4);
  auto res_str = res->ToString();
  std::cout << res_str.Get() << std::endl;
}