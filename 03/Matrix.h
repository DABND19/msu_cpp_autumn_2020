#pragma once
#include <cstdlib>
#include <iostream>

class Matrix {
 private:
  int* data;
  size_t rows_num;
  size_t columns_num;

  size_t capacity() const;

 public:
  class Row {
   private:
    int* data;
    size_t size;

   public:
    Row(const Matrix& matrix, size_t row_num);
    int& operator[](size_t column_num);
    int operator[](size_t column_num) const;
    size_t getSize() const;
  };

  Matrix(size_t rows, size_t columns);
  Matrix(const Matrix& copied);
  Row operator[](size_t row_num) const;
  Row operator[](size_t row_num);
  std::pair<size_t, size_t> getSize() const;
  Matrix operator*=(int scalar);
  Matrix& operator=(const Matrix& equal);
  friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
  friend bool operator==(const Matrix& lhs, const Matrix& rhs);
  friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
  ~Matrix();
};

std::ostream& operator<<(std::ostream& os, const Matrix::Row& row);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
