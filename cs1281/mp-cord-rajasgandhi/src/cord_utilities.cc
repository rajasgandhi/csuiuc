#include "cord_utilities.hpp"

#include <stdexcept>

SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                SharedPointer<Cord> right_cord) {
  if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
    throw std::runtime_error("input error");
  }

  Cord* c = new Cord();
  c->SetLeft(left_cord);
  c->SetRight(right_cord);
  c->SetLength(left_cord->Length() + right_cord->Length());

  auto* to_return = new SharedPointer<Cord>(c, kSharedPointerType::kObject);
  return *to_return;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx) {
  if (lower_idx >= upper_idx || lower_idx < 0 ||
      upper_idx > curr_cord->Length())
    throw std::runtime_error("input error");
  if (upper_idx == curr_cord->Length() && lower_idx == 0) return curr_cord;

  if (!(curr_cord.Get()->IsDataEmpty())) {
    Cord* new_cord = new Cord(
        curr_cord.Get()->Data().substr(lower_idx, upper_idx - lower_idx));
    return {new_cord, kSharedPointerType::kObject};
  }
  if (lower_idx < curr_cord.Get()->Left()->Length() &&
      upper_idx <= curr_cord.Get()->Left()->Length()) {
    return SubString(curr_cord.Get()->Left(), lower_idx, upper_idx);
  }
  if (lower_idx >= curr_cord.Get()->Left()->Length()) {
    return SubString(curr_cord.Get()->Right(),
                     lower_idx - curr_cord.Get()->Left()->Length(),
                     upper_idx - curr_cord.Get()->Left()->Length());
  }

  SharedPointer<Cord> left_cord = SubString(
      curr_cord.Get()->Left(), lower_idx, curr_cord.Get()->Left()->Length());
  SharedPointer<Cord> right_cord =
      SubString(curr_cord.Get()->Right(),
                0,
                upper_idx - curr_cord.Get()->Left()->Length());

  SharedPointer<Cord> conc_cord = ConcatCords(left_cord, right_cord);
  return conc_cord;
}