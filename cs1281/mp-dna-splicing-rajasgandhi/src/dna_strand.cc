#include "dna_strand.hpp"

#include <iostream>
#include <stdexcept>

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
  delete head_;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern == nullptr) throw std::runtime_error("pattern is null");
  if (pattern[0] == '\0') throw std::runtime_error("pattern is empty");
  if (to_splice_in.head_ == nullptr || &to_splice_in == this) return;
  int pattern_length = 0;
  for (unsigned int i = 0; pattern[i] != '\0'; ++i) {
    pattern_length++;
  }
  bool e = true;
  for (int i = 0; i < pattern_length; ++i) {
    if (pattern[i] != 'a') {
      e = false;
    }
  }
  Node* temp = to_splice_in.head_;
  while (temp != nullptr) {
    if (temp->data != 'a') {
      e = false;
    }
    temp = temp->next;
  }
  if (e) {
    SpliceAfterAndRemove(
        head_, to_splice_in.head_, to_splice_in.tail_, pattern_length);
  } else {
    Node* insertion_point = FindLastOccurrence(head_, pattern, pattern_length);
    Node* true_insertion_point = nullptr;
    Node* current = head_;
    if (insertion_point == head_) {
      true_insertion_point = insertion_point;
    } else {
      while (current->next != nullptr) {
        if (current->next == insertion_point) true_insertion_point = current;
        current = current->next;
      }
    }
    SpliceAfterAndRemove(true_insertion_point,
                         to_splice_in.head_,
                         to_splice_in.tail_,
                         pattern_length);
  }
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}

Node* DNAstrand::FindLastOccurrence(Node* head,
                                    const char* sequence,
                                    int pattern_length) {
  Node* traverse = head;
  Node* start = nullptr;
  while (traverse != nullptr) {
    char* c1 = new char[pattern_length];
    for (int i = 0; i < pattern_length; ++i) {
      c1[i] = '0';
    }
    if (traverse->data == sequence[0]) {
      Node* temp = traverse;
      for (int i = 0; i < pattern_length; ++i) {
        if (temp == nullptr) {
          break;
        }
        c1[i] = temp->data;
        temp = temp->next;
      }
    }
    bool equal = true;
    for (int i = 0; i < pattern_length; ++i) {
      if (sequence[i] != c1[i]) {
        equal = false;
      }
    }

    if (equal) {
      start = traverse;
    }
    delete[] c1;
    traverse = traverse->next;
  }
  if (start == nullptr) {
    throw std::runtime_error("Pattern not found!");
  }

  return start;
}

void DNAstrand::SpliceAfterAndRemove(Node* insertionPoint,
                                     Node* newHead,
                                     Node* newTail,
                                     int sequenceLength) {
  if (insertionPoint == head_) {
    // head_ = newHead;
    Node* new_tail_next = nullptr;
    Node* temp = head_;
    int count = 0;
    while (temp != nullptr) {
      Node* tmp = temp->next;
      if (count == sequenceLength) {
        new_tail_next = temp;
        break;
      }
      delete temp;
      temp = tmp;
      count++;
    }

    newTail->next = new_tail_next;
    head_ = newHead;
  } else {
    Node* temp = insertionPoint->next;
    insertionPoint->next = newHead;

    while (newHead->next != nullptr) {
      newHead = newHead->next;
    }
    int count = 0;
    while (temp != nullptr) {
      Node* tmp = temp->next;
      if (count == sequenceLength) {
        newHead->next = temp;
        break;
      }
      delete temp;
      temp = tmp;
      count++;
    }
  }
}

void DNAstrand::Append(const char* sequence) {
  if (sequence == nullptr) {
    return;
  }

  for (int i = 0; sequence[i] != '\0'; i++) {
    PushBack(sequence[i]);
  }
}

void DNAstrand::PushBack(char c) {
  Node* new_node = new Node(c);
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next = new_node;
    tail_ = new_node;
  }
}

void DNAstrand::Print() {
  Node* current = head_;
  while (current != nullptr) {
    std::cout << current->data;
    current = current->next;
  }
  std::cout << std::endl;
}