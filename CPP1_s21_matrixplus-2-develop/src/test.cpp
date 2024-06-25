#include <gtest/gtest.h>

#include "s21_matrix_oop.h"
void FillingMatrixRandom(S21Matrix& matrix);
void FillingMatrixNumber(S21Matrix& matrix, double num);

TEST(test, constructor) {
  S21Matrix matrix;
  int i = matrix.getRows();
  int j = matrix.getCols();
  EXPECT_EQ(i, j);
}

TEST(constructor, basic) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.getRows(), 3);
  EXPECT_EQ(matrix1.getCols(), 3);
}

TEST(constructor, two_args) {
  S21Matrix matrix1(2, 3);
  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 3);
}

TEST(constructor, two_args_fail) {
  EXPECT_THROW(S21Matrix matrix1(-1, 1), std::out_of_range);
}

TEST(constructor, copy) {
  S21Matrix matrix1(4, 3);
  FillingMatrixRandom(matrix1);

  S21Matrix matrix2(matrix1);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(eq_suite, basic) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  FillingMatrixRandom(matrix1);
  FillingMatrixRandom(matrix2);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(eq_suite, not_eq_0) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  FillingMatrixNumber(matrix1, 0.0);
  FillingMatrixNumber(matrix2, 2.0);

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(eq_suite, not_eq_1) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(sum_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1.SumMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 6.0);
  EXPECT_EQ(matrix1(0, 1), 8.0);
  EXPECT_EQ(matrix1(1, 0), 10.0);
  EXPECT_EQ(matrix1(1, 1), 12.0);
}

TEST(sum_suite, basic2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 2.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 5.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  matrix1.SumMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 7.0);
  EXPECT_EQ(matrix1(0, 1), 7.0);
  EXPECT_EQ(matrix1(1, 0), 7.0);
  EXPECT_EQ(matrix1(1, 1), 7.0);
}

TEST(sum_suite, random_number) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);

  FillingMatrixRandom(matrix1);
  FillingMatrixRandom(matrix2);

  S21Matrix expected_result(3, 4);

  for (size_t i = 0; i < (size_t)expected_result.getRows(); ++i) {
    for (size_t j = 0; j < (size_t)expected_result.getCols(); ++j) {
      expected_result(i, j) = matrix1(i, j) + matrix2(i, j);
    }
  }

  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1 == expected_result);
}

TEST(sum_suite, exception) {
  S21Matrix matrix1(2, 20);
  S21Matrix matrix2(60, 2);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::out_of_range);
}

TEST(sub_suite, exception) {
  S21Matrix matrix1(2, 20);
  S21Matrix matrix2(60, 2);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::out_of_range);
}

TEST(sub_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 1.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 1.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 10.0;
  matrix2(0, 1) = 10.0;
  matrix2(1, 0) = 10.0;
  matrix2(1, 1) = 10.0;

  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), -9.0);
  EXPECT_EQ(matrix1(0, 1), -9.0);
  EXPECT_EQ(matrix1(1, 0), -9.0);
  EXPECT_EQ(matrix1(1, 1), -9.0);
}

TEST(sub_suite, random_number) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);

  FillingMatrixRandom(matrix1);
  FillingMatrixRandom(matrix2);

  S21Matrix expected_result(3, 4);

  for (size_t i = 0; i < (size_t)expected_result.getRows(); ++i) {
    for (size_t j = 0; j < (size_t)expected_result.getCols(); ++j) {
      expected_result(i, j) = matrix1(i, j) - matrix2(i, j);
    }
  }

  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1 == expected_result);
}

TEST(mul_number_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 4.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  double num = 2.0;
  matrix1.MulNumber(num);

  EXPECT_EQ(matrix1(0, 0), 8.0);
  EXPECT_EQ(matrix1(0, 1), 4.0);
  EXPECT_EQ(matrix1(1, 0), 6.0);
  EXPECT_EQ(matrix1(1, 1), 8.0);
}

TEST(mul_matrix_suite, random_number) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(4, 5);

  FillingMatrixRandom(matrix1);
  FillingMatrixRandom(matrix2);

  S21Matrix expected_result(3, 5);

  for (size_t i = 0; i < (size_t)matrix1.getRows(); ++i) {
    for (size_t j = 0; j < (size_t)matrix2.getCols(); ++j) {
      expected_result(i, j) = 0.0;
      for (size_t k = 0; k < (size_t)matrix1.getCols(); ++k) {
        expected_result(i, j) =
            expected_result(i, j) + matrix1(i, k) * matrix2(k, j);
      }
    }
  }
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1 == expected_result);
}

TEST(mul_matrix_suite, basic) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 58.0);
  EXPECT_EQ(matrix1(0, 1), 64.0);
  EXPECT_EQ(matrix1(1, 0), 139.0);
  EXPECT_EQ(matrix1(1, 1), 154.0);
}

TEST(mul_matrix_suite, exception) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(21, 2);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::out_of_range);
}

TEST(transpose_suite, basic) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix result = matrix1.Transpose();

  EXPECT_EQ(result(0, 0), 1.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 2.0);
  EXPECT_EQ(result(1, 1), 5.0);
  EXPECT_EQ(result(2, 0), 3.0);
  EXPECT_EQ(result(2, 1), 6.0);
}

TEST(determinant_suite, basic_1_1) {
  S21Matrix matrix2(1, 1);
  matrix2(0, 0) = 1.0;
  EXPECT_DOUBLE_EQ(matrix2.Determinant(), 1.0);
}

TEST(determinant_suite, basic_2_2) {
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(matrix2.Determinant(), -2.0);
}

TEST(determinant_suite, basic_3_3) {
  S21Matrix matrix3(3, 3);
  matrix3(0, 0) = 6.0;
  matrix3(0, 1) = 1.0;
  matrix3(0, 2) = 1.0;
  matrix3(1, 0) = 4.0;
  matrix3(1, 1) = -2.0;
  matrix3(1, 2) = 5.0;
  matrix3(2, 0) = 2.0;
  matrix3(2, 1) = 8.0;
  matrix3(2, 2) = 7.0;

  EXPECT_DOUBLE_EQ(matrix3.Determinant(), -306.0);
}

TEST(determinant_suite, zero_det) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.0;
  matrix1(2, 2) = 9.0;

  EXPECT_EQ(matrix1.Determinant(), 0.0);
}

TEST(determinant_suite, exception) {
  S21Matrix matrix4(2, 3);
  EXPECT_THROW(matrix4.Determinant(), std::out_of_range);
}

TEST(calc_complements_suite, exception) {
  S21Matrix matrix1(3, 2);
  EXPECT_THROW(matrix1.CalcComplements(), std::out_of_range);
}

TEST(inverse_matrix_suite, exception) {
  S21Matrix matrix1(2, 2);
  FillingMatrixNumber(matrix1, 1);
  EXPECT_THROW(matrix1.InverseMatrix(), std::out_of_range);
}

TEST(inverse_matrix_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix result = matrix1.InverseMatrix();

  EXPECT_EQ(result(0, 0), -2);
  EXPECT_EQ(result(0, 1), 1);
  EXPECT_EQ(result(1, 0), 1.5);
  EXPECT_EQ(result(1, 1), -0.5);
}

TEST(overloads, equals) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 2.0;
  matrix3(0, 1) = 2.0;
  matrix3(1, 0) = 2.0;
  matrix3(1, 1) = 2.0;

  EXPECT_TRUE(matrix1 == matrix2);
  EXPECT_FALSE(matrix1 == matrix3);
}

TEST(overloads_assignment, copy_basic) {
  S21Matrix matrix1(2, 2);
  FillingMatrixRandom(matrix1);
  S21Matrix matrix2 = matrix1;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(overloads_assignment, copy_same) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1 = matrix1;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(overloads, plus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 3.0;
  matrix3(0, 1) = 5.0;
  matrix3(1, 0) = 7.0;
  matrix3(1, 1) = 9.0;

  S21Matrix result = matrix1 + matrix2;
  EXPECT_TRUE(matrix3 == result);
}

TEST(overloads, minus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = -1.0;
  matrix3(0, 1) = -1.0;
  matrix3(1, 0) = -1.0;
  matrix3(1, 1) = -1.0;

  S21Matrix result = matrix1 - matrix2;
  EXPECT_TRUE(result == matrix3);
}

TEST(overloads, multiply) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 10.0;
  matrix3(0, 1) = 13.0;
  matrix3(1, 0) = 22.0;
  matrix3(1, 1) = 29.0;

  S21Matrix result = matrix1 * matrix2;
  EXPECT_TRUE(result == matrix3);
}

TEST(overloads, multiply_scalar_basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 6.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 * 2.0;
  EXPECT_TRUE(result == matrix2);
}

TEST(overloads, indexation_basic) {
  S21Matrix matrix1(2, 2);
  EXPECT_EQ(matrix1(1, 1), 0);
}

TEST(overloads, indexation_exception) {
  S21Matrix matrix1(2, 2);
  EXPECT_THROW(matrix1(4, 1), std::out_of_range);
}

TEST(set, SetRows) {
  S21Matrix a(4, 3);
  a.setRows(3);
  EXPECT_EQ(a.getRows(), 3);
  EXPECT_FALSE(a.getRows() == 4);
}

TEST(set, wrongSetRows) {
  S21Matrix a(4, 3);
  EXPECT_THROW(a.setRows(-3), std::length_error);
}

TEST(set, wrongSetCols) {
  S21Matrix a(4, 3);
  EXPECT_THROW(a.setCols(-3), std::length_error);
}

TEST(set, SetCols) {
  S21Matrix a(4, 4);
  a.setCols(2);
  EXPECT_EQ(a.getCols(), 2);
  EXPECT_FALSE(a.getCols() == 4);
}

void FillingMatrixRandom(S21Matrix& matrix) {
  srand(time(nullptr));
  for (size_t i = 0; i < (size_t)matrix.getRows(); ++i) {
    for (size_t j = 0; j < (size_t)matrix.getCols(); ++j) {
      matrix(i, j) = rand() % 10;
    }
  }
}

void FillingMatrixNumber(S21Matrix& matrix, double num) {
  for (size_t i = 0; i < (size_t)matrix.getRows(); ++i) {
    for (size_t j = 0; j < (size_t)matrix.getCols(); ++j) {
      matrix(i, j) = num;
    }
  }
}

int main(void) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
