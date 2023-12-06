#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

Cord::Cord(std::string_view sv) {
  if (sv.empty()) {
    throw std::runtime_error("sv size error");
  }

  data_ = new char[sv.size() + 1];
  for (unsigned int i = 0; i < sv.size(); ++i) {
    data_[i] = sv[i];
  }
  data_[sv.size()] = '\0';
  length_ = sv.size();
}

Cord::~Cord() { delete data_; }

SharedPointer<char> Cord::ToString() const {
  char* tostring = new char[length_ + 1];
  int count = 0;
  this->ToStringHelper(tostring, count);
  tostring[length_] = '\0';
  return *(new SharedPointer<char>(tostring, kSharedPointerType::kArray));
}

void Cord::ToStringHelper(char* sv, int& count) const {
  if (data_ != nullptr) {
    unsigned int i = 0;
    while (i != length_) {
      sv[count] = data_[i];
      count++;
      i++;
    }
    return;
  }
  left_.Get()->ToStringHelper(sv, count);
  right_.Get()->ToStringHelper(sv, count);
}