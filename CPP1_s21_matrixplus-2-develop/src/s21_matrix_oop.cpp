#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    rows_ = rows;
    cols_ = cols;
    create_matrix();
  } else {
    throw std::out_of_range("Invalid matrix size");
  }
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::create_matrix() {
  matrix_ = nullptr;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  create_matrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows <= 0) {
    throw std::length_error("lenght error");
  } else {
    rows_ = rows;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols <= 0) {
    throw std::length_error("lenght error");
  } else {
    cols_ = cols;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  int error = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    error = false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >
          std::numeric_limits<double>::epsilon()) {
        error = false;
      }
    }
  }
  return error;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Error: Matrices should be the same dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Error: Matrices should be the same dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("Error: Matrices should be the same dimensions");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->~S21Matrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  create_matrix();
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
  return *this;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return result;
}

void S21Matrix::swap_rows(int i, int j) {
  for (int k = 0; k < cols_; ++k) {
    double num = (*this)(i, k);
    (*this)(i, k) = (*this)(j, k);
    (*this)(j, k) = num;
  }
}

double S21Matrix::Determinant() {
  S21Matrix matrix_det = S21Matrix(cols_, rows_);
  if (this->cols_ != this->rows_) {
    throw std::out_of_range(
        "Error: Matrix (rows and cols) has different dimensions");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_det(i, j) = (*this)(i, j);
    }
  }
  int swap_count = 0;
  for (int i = 0; i < matrix_det.getRows(); ++i) {
    int zero_count = 0;
    if (matrix_det(i, i) == 0) {
      for (int j = i + 1; j < matrix_det.getCols(); ++j) {
        if (matrix_det(j, i) != 0) {
          matrix_det.swap_rows(i, j);
          ++swap_count;
          zero_count = 0;
          break;
        }
        ++zero_count;
      }
    }
    if (zero_count != 0 && zero_count == (rows_ - i - 1)) {
      return 0;
    }

    for (int j = i + 1; j < matrix_det.getCols(); ++j) {
      double del = matrix_det(j, i) / matrix_det(i, i);

      for (int k = 0; k < matrix_det.getCols(); ++k) {
        double tmp = matrix_det(i, k) * del;
        matrix_det(j, k) -= tmp;
      }
    }
  }

  double det = 1;
  for (int i = 0; i < matrix_det.getRows(); ++i) {
    det *= matrix_det(i, i);
  }

  if (swap_count % 2 == 1) {
    det *= -1;
  }

  return det;
}

S21Matrix S21Matrix::minor_matrix(int row, int col) {
  S21Matrix minor_matrix = S21Matrix(rows_ - 1, cols_ - 1);
  if (minor_matrix.getRows() != rows_ - 1 ||
      minor_matrix.getCols() != cols_ - 1) {
    throw std::out_of_range("Error");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i < row && j < col) {
        minor_matrix(i, j) = (*this)(i, j);
      } else if (i > row && j < col) {
        minor_matrix((i - 1), j) = (*this)(i, j);
      } else if (i < row && j > col) {
        minor_matrix(i, j - 1) = (*this)(i, j);
      } else if (i > row && j > col) {
        minor_matrix((i - 1), j - 1) = (*this)(i, j);
      }
    }
  }
  return minor_matrix;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range("Error: Matrix has different");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        S21Matrix temp = minor_matrix(i, j);
        result.matrix_[i][j] = temp.Determinant() * pow(-1.0, i + j + 2);
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res = *this;
  res.MulNumber(num);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double number) {
  MulNumber(number);
  return *this;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) < 1e-07) {
    throw std::out_of_range(
        "Error: determinant  is equal to 0 or rows and "
        "cols have different dimensions.");
  }
  S21Matrix tmp(CalcComplements().Transpose());
  tmp.MulNumber(1. / det);
  return tmp;
}

double& S21Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Error: Index is out of range.");
  }
  return matrix_[i][j];
}