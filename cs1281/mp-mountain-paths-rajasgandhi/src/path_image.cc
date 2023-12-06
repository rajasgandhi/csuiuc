#include "path_image.hpp"

#include <fstream>
#include <iostream>

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = image.Width();
  height_ = image.Height();

  path_image_ = image.GetImage();

  const Color kRed = Color(252, 25, 63);
  const Color kGreen = Color(31, 253, 13);

  for (size_t i = 0; i < height_; i++) {
    Path p = Path(width_, i);
    p.SetLoc(0, i);
    size_t loc = i;
    for (size_t j = 0; j < width_ - 1; j++) {
      int current_elev = dataset.DatumAt(loc, j);

      UpdateLocation(dataset, current_elev, loc, j, p);
    }

    paths_.push_back(p);
  }

  size_t min_ele = paths_.at(0).EleChange();
  size_t lowest_ele_row = 0;
  for (size_t i = 0; i < paths_.size(); i++) {
    if (paths_.at(i).EleChange() < min_ele) {
      min_ele = paths_.at(i).EleChange();
      lowest_ele_row = i;
    }
  }

  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < paths_.at(i).Length(); j++) {
      path_image_.at(paths_.at(i).GetPath().at(j)).at(j) = kRed;
    }
  }

  for (size_t i = 0; i < paths_.at(lowest_ele_row).Length(); i++) {
    path_image_.at(paths_.at(lowest_ele_row).GetPath().at(i)).at(i) = kGreen;
  }
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);

  if (!ofs.is_open()) {
    throw std::runtime_error("could not open file");
  }

  ofs << "P3\n";
  ofs << width_ << " " << height_ << "\n";
  ofs << kMaxColorValue << "\n";
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ofs << path_image_.at(i).at(j).Red() << " "
          << path_image_.at(i).at(j).Green() << " "
          << path_image_.at(i).at(j).Blue() << " ";
    }
    ofs << "\n";
  }
  ofs.close();
}

void PathImage::UpdateLocation(const ElevationDataset& dataset,
                               const int& current_elevation,
                               size_t& row,
                               const size_t& col,
                               Path& p) const {
  if (row == 0) {
    if (abs(dataset.DatumAt(row + 1, col + 1) - current_elevation) <
        abs(dataset.DatumAt(row, col + 1) - current_elevation)) {
      p.IncEleChange(
          abs(dataset.DatumAt(row + 1, col + 1) - current_elevation));
      row += 1;
    } else {
      p.IncEleChange(abs(dataset.DatumAt(row, col + 1) - current_elevation));
    }
  } else if (row == height_ - 1) {
    if (abs(dataset.DatumAt(row - 1, col + 1) - current_elevation) <
        abs(dataset.DatumAt(row, col + 1) - current_elevation)) {
      p.IncEleChange(
          abs(dataset.DatumAt(row - 1, col + 1) - current_elevation));
      row -= 1;
    } else {
      p.IncEleChange(abs(dataset.DatumAt(row, col + 1) - current_elevation));
    }
  } else {
    if (abs(dataset.DatumAt(row + 1, col + 1) - current_elevation) <=
            abs(dataset.DatumAt(row - 1, col + 1) - current_elevation) &&
        abs(dataset.DatumAt(row + 1, col + 1) - current_elevation) <
            abs(dataset.DatumAt(row, col + 1) - current_elevation)) {
      p.IncEleChange(
          abs(dataset.DatumAt(row + 1, col + 1) - current_elevation));
      row += 1;
    } else if (abs(dataset.DatumAt(row - 1, col + 1) - current_elevation) <
                   abs(dataset.DatumAt(row, col + 1) - current_elevation) &&
               abs(dataset.DatumAt(row - 1, col + 1) - current_elevation) <
                   abs(dataset.DatumAt(row + 1, col + 1) - current_elevation)) {
      p.IncEleChange(
          abs(dataset.DatumAt(row - 1, col + 1) - current_elevation));
      row -= 1;
    } else {
      p.IncEleChange(abs(dataset.DatumAt(row, col + 1) - current_elevation));
    }
  }
  p.SetLoc(col + 1, row);
}