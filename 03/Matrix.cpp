#include "Matrix.h"

#include <stdexcept>

Matrix::Row::Row(const Matrix& matrix, size_t row_num) {
  size = matrix.rows_num;
  data = matrix.data + row_num * matrix.columns_num;
}

int& Matrix::Row::operator[](size_t column_num) {
  if (column_num >= size) {
    throw std::out_of_range("index of column out of range");
  }

  return data[column_num];
}

int Matrix::Row::operator[](size_t column_num) const {
  if (column_num >= size) {
    throw std::out_of_range("index of column out of range");
  }

  return data[column_num];
}

size_t Matrix::Row::getSize() const { return size; }

Matrix::Matrix(size_t rows, size_t columns) {
  rows_num = rows;
  columns_num = columns;
  data = new int[rows_num * columns_num];
}

Matrix::Matrix(const Matrix& copied) {
  rows_num = copied.rows_num;
  columns_num = copied.columns_num;
  data = new int[rows_num * columns_num];
  std::copy(copied.data, copied.data + rows_num * columns_num, data);
}

Matrix& Matrix::operator=(const Matrix& equal) {
  if (equal.data != data) {
    if (equal.rows_num * equal.columns_num == rows_num * columns_num) {
      std::copy(equal.data, equal.data + rows_num * columns_num, data);
    } else {
      Matrix tmp(equal);
      std::swap(tmp.data, data);
    }
    rows_num = equal.rows_num;
    columns_num = equal.columns_num;
  }
  return *this;
}

Matrix::Row Matrix::operator[](size_t row_num) const {
  if (row_num >= rows_num) {
    throw std::out_of_range("index of row out of range");
  }

  return Row(*this, row_num);
}

Matrix::Row Matrix::operator[](size_t row_num) {
  if (row_num >= rows_num) {
    throw std::out_of_range("index of row out of range");
  }

  return Row(*this, row_num);
}

std::pair<size_t, size_t> Matrix::getSize() const {
  return {rows_num, columns_num};
}

Matrix Matrix::operator*=(double alpha) {
  for (size_t i = 0; i < columns_num * rows_num; i++) {
    data[i] *= alpha;
  }

  return *this;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  if (lhs.getSize() != rhs.getSize()) {
    throw std::out_of_range("sizes of matrices are not equal");
  }

  const auto [rows_num, columns_num] = lhs.getSize();
  Matrix result(rows_num, columns_num);

  for (size_t i = 0; i < rows_num * columns_num; i++) {
    result.data[i] = lhs.data[i] + rhs.data[i];
  }

  return result;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
  if (lhs.getSize() != rhs.getSize()) {
    throw std::out_of_range("sizes of matrices are not equal");
  }

  const auto [rows_num, columns_num] = lhs.getSize();
  bool result = true;

  for (size_t i = 0; i < rows_num * columns_num; i++) {
    if (lhs.data[i] != rhs.data[i]) {
      result = false;
      break;
    }
  }

  return result;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) { return !(lhs == rhs); }

Matrix::~Matrix() { delete[] data; }

std::ostream& operator<<(std::ostream& os, const Matrix::Row& row) {
  for (size_t i = 0; i < row.getSize(); i++) {
    os << row[i] << ' ';
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
  auto [rows_num, columns_num] = matrix.getSize();
  for (size_t i = 0; i < rows_num; i++) {
    os << matrix[i] << std::endl;
  }

  return os;
}
