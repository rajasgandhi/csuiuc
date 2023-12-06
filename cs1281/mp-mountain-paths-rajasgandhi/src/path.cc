#include "path.hpp"

Path::Path(size_t length, size_t starting_row) {
  length_ = length;
  starting_row_ = starting_row;

  path_.resize(length);
}

void Path::IncEleChange(unsigned int value) { ele_change_ += value; }