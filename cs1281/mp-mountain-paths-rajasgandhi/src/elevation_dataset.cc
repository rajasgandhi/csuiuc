#include "elevation_dataset.hpp"

#include <fstream>
#include <limits>
#include <stdexcept>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height) {
  width_ = width;
  height_ = height;
  data_.resize(height_, std::vector<int>(width_, 0));

  std::ifstream ifs(filename);

  if (!ifs.is_open()) {
    throw std::runtime_error("invalid file name");
  }

  max_ele_ = std::numeric_limits<int>::min();
  min_ele_ = std::numeric_limits<int>::max();

  int temp = 0;

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      if (!(ifs >> temp)) {
        throw std::runtime_error("invalid input or too little input");
      }

      data_.at(i).at(j) = temp;

      int curr = data_.at(i).at(j);

      if (min_ele_ > curr) {
        min_ele_ = curr;
      }
      if (max_ele_ < curr) {
        max_ele_ = curr;
      }
    }
  }

  ifs >> temp;

  if (!ifs.fail()) {
    throw std::runtime_error("too many input points");
  }
}
