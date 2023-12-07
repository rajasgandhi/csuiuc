#ifndef CORD_HPP
#define CORD_HPP

#include <string_view>

#include "shared_pointer.hpp"

class Cord {
public:
  Cord(std::string_view sv);
  ~Cord();
  SharedPointer<char> ToString() const;

  void SetLength(unsigned int length) { length_ = length; }
  void SetRight(const SharedPointer<Cord>& kRight) { right_ = kRight; }
  void SetLeft(const SharedPointer<Cord>& kLeft) { left_ = kLeft; }
  bool IsDataEmpty() { return data_ == nullptr; }

  void ToStringHelper(char* sv, int& count) const;

  // Provided, do not modify!
  Cord() = default;
  Cord(const Cord& rhs) = delete;
  Cord& operator=(const Cord& rhs) = delete;
  unsigned int Length() const { return length_; }
  const SharedPointer<Cord> Left() const { return left_; }
  const SharedPointer<Cord> Right() const { return right_; }
  const std::string_view Data() const { return data_; }

private:
  // data members
  SharedPointer<Cord> left_;
  SharedPointer<Cord> right_;
  char* data_ = nullptr;
  unsigned int length_ = 0;
  // friend functions
  friend SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                         SharedPointer<Cord> right_cord);
};

#endif