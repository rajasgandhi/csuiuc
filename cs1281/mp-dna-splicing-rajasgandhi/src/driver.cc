#include <iostream>

#include "dna_strand.hpp"

int main() {
  DNAstrand sequence1;
  sequence1.Append("aaaaa");

  DNAstrand to_splice_in1;
  to_splice_in1.Append("tg");

  const char* pattern = "a";

  try {
    sequence1.SpliceIn(pattern, to_splice_in1);
    sequence1.Print();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}