#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();

  std::vector<std::vector<Color>> temp_image(height_,
                                             std::vector<Color>(width_));

  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      int shade_of_gray = 0;
      if (!(dataset.MaxEle() == dataset.MinEle())) {
        shade_of_gray = static_cast<int>(std::round(
            (static_cast<double>(dataset.DatumAt(i, j) - dataset.MinEle())) /
            (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue));
      }

      temp_image.at(i).at(j) =
          Color(shade_of_gray, shade_of_gray, shade_of_gray);
    }
  }

  image_ = temp_image;
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  width_ = width;
  height_ = height;

  std::vector<std::vector<Color>> temp_image(height_,
                                             std::vector<Color>(width_));

  ElevationDataset ed = ElevationDataset(filename, width, height);

  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      int shade_of_gray = 0;
      if (!(ed.MaxEle() == ed.MinEle())) {
        shade_of_gray = static_cast<int>(
            std::round((static_cast<double>(ed.DatumAt(i, j) - ed.MinEle())) /
                       (ed.MaxEle() - ed.MinEle()) * kMaxColorValue));
      }

      temp_image.at(i).at(j) =
          Color(shade_of_gray, shade_of_gray, shade_of_gray);
    }
  }

  image_ = temp_image;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);

  ofs << "P3\n";
  ofs << width_ << " " << height_ << "\n";
  ofs << kMaxColorValue << "\n";
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ofs << image_.at(i).at(j).Red() << " " << image_.at(i).at(j).Green()
          << " " << image_.at(i).at(j).Blue() << " ";
    }
    ofs << "\n";
  }

  ofs.close();
}
