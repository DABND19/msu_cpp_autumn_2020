#pragma once

#include <iterator>

template <typename T, typename RefT = T&, typename PtrT = T*>
class VectorIterator
    : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, PtrT,
                           RefT> {
 public:
  using Self = VectorIterator;

 private:
  PtrT current_;

 public:
  VectorIterator(PtrT pos) : current_(pos) {}

  bool operator==(const Self& rhs) const { return current_ == rhs.current_; }
  bool operator!=(const Self& rhs) const { return current_ != rhs.current_; }
  bool operator<(const Self& rhs) const { return current_ < rhs.current_; }
  bool operator>(const Self& rhs) const { return current_ > rhs.current_; }
  bool operator<=(const Self& rhs) const { return current_ <= rhs.current_; }
  bool operator>=(const Self& rhs) const { return current_ >= rhs.current_; }

  Self& operator++() {
    current_++;
    return *this;
  }

  Self operator++(int) {
    auto result = *this;
    current_++;
    return result;
  }

  Self& operator--() {
    current_--;
    return *this;
  }

  Self operator--(int) {
    auto result = *this;
    current_--;
    return result;
  }

  Self operator+(ptrdiff_t shift) const { return {current_ + shift}; }
  Self operator-(ptrdiff_t shift) const { return {current_ - shift}; }

  Self& operator+=(ptrdiff_t shift) const { return *this = *this + shift; }

  Self& operator-=(ptrdiff_t shift) const { return *this = *this - shift; }

  RefT operator*() { return *current_; }
};
