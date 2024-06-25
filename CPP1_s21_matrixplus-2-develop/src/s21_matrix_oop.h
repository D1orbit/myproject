#pragma once

#include <stdlib.h>

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  int getRows();
  int getCols();
  void create_matrix();
  void swap_rows(int i, int j);
  S21Matrix minor_matrix(int row, int cols);
  void setCols(int cols);
  void setRows(int rows);

  S21Matrix();   // Default constructor
  ~S21Matrix();  // Destructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  double& operator()(int i, int j);
  bool operator==(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
};