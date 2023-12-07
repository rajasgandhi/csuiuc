#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  const std::string kTestFile =
      "./example-data/ex_input_data/map-input-w51-h55.dat";
  constexpr size_t kTestFileWidth = 51;
  constexpr size_t kTestFileHeight = 55;
  const std::string kStudentOutput = "./student_out/ex_ppm_output_55.ppm";
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  pi.ToPpm(kStudentOutput);
}