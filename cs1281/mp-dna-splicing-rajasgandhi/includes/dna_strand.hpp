#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  void Append(const char* sequence);
  void Print();

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  Node* FindLastOccurrence(Node* head, const char* sequence, int pattern_length);
  void SpliceAfterAndRemove(Node* insertionPoint,
                            Node* newHead,
                            Node* newTail,
                            int sequenceLength);
  void PushBack(char c);
};

#endif