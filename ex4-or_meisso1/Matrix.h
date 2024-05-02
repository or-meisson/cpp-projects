/**
 * @file Matrix.h
 * @brief Contains the declaration of the Matrix class and related functions.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "iostream"

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows; /**< Number of rows in the matrix */
	int cols; /**< Number of columns in the matrix */
} matrix_dims;

/**
 * @class Matrix
 * @brief Represents a mathematical matrix and provides various operations
 * on matrices.
 */
class Matrix
{
 private:
  matrix_dims dimensions{}; /**< Matrix dimensions */
  float **mat; /**< Pointer to the matrix data */
 
 public:
  /**
   * @brief Default constructor. Creates a 1x1 matrix with default values.
   */
  Matrix ();
  
  /**
   * @brief Parameterized constructor. Creates a matrix with the given number
   * of rows and columns.
   * @param num_of_rows Number of rows in the matrix
   * @param num_of_cols Number of columns in the matrix
   */
  Matrix (int num_of_rows, int num_of_cols);
  
  /**
   * @brief Destructor. Deallocates the dynamically allocated matrix data.
   */
  ~Matrix ();
  
  /**
   * @brief Getter for the number of rows in the matrix.
   * @return The number of rows in the matrix.
   */
  int get_rows () const;
  
  /**
   * @brief Getter for the number of columns in the matrix.
   * @return The number of columns in the matrix.
   */
  int get_cols () const;
  
  /**
   * @brief Transposes the matrix.
   * @return Reference to the transposed matrix.
   */
  Matrix &transpose ();
  
  /**
   * @brief Vectorizes the matrix.
   * @return Reference to the vectorized matrix.
   */
  Matrix &vectorize ();
  
  /**
   * @brief Prints the matrix in plain format.
   */
  void plain_print () const;
  
  /**
   * @brief Computes the element-wise multiplication between two matrices.
   * @param mat1 The matrix to perform the multiplication with.
   * @return The resulting matrix after the multiplication.
   */
  Matrix dot (const Matrix &mat1) const;
  
  /**
   * @brief Computes the Frobenius norm of the matrix.
   * @return The Frobenius norm of the matrix.
   */
  float norm () const;
  
  /**
   * @brief Finds the index of the maximum element in the matrix.
   * @return The index of the maximum element.
   */
  int argmax () const;
  
  /**
   * @brief Computes the sum of all elements in the matrix.
   * @return The sum of all elements in the matrix.
   */
  float sum () const;
  
  /**
   * @brief Copy constructor. Creates a new matrix by copying the contents of
   * another matrix.
   * @param mat_to_copy The matrix to copy from.
   */
  Matrix (const Matrix &mat_to_copy);
  
  /**
   * @brief Assignment operator. Assigns the contents of another matrix to
   * this matrix.
   * @param other The matrix to assign from.
   * @return Reference to the assigned matrix.
   */
  Matrix &operator= (const Matrix &other);
  
  /**
   * @brief Addition operator. Adds two matrices element-wise.
   * @param mat1 The first matrix to add.
   * @param mat2 The second matrix to add.
   * @return The resulting matrix after addition.
   */
  friend Matrix operator+ (const Matrix &mat1, const Matrix &mat2);
  
  /**
   * @brief Multiplication operator. Multiplies two matrices.
   * @param mat1 The first matrix to multiply.
   * @param mat2 The second matrix to multiply.
   * @return The resulting matrix after multiplication.
   */
  friend Matrix operator* (const Matrix &mat1, const Matrix &mat2);
  
  /**
   * @brief Scalar multiplication operator. Multiplies the matrix by a
   * scalar value.
   * @param scalar The scalar value to multiply with.
   * @param mat1 The matrix to multiply.
   * @return The resulting matrix after scalar multiplication.
   */
  friend Matrix operator* (float scalar, const Matrix &mat1);
  
  /**
   * @brief Scalar multiplication operator. Multiplies the matrix by a
   * scalar value.
   * @param scalar The scalar value to multiply with.
   * @return The resulting matrix after scalar multiplication.
   */
  Matrix operator* (float scalar) const;
  
  /**
   * @brief Assignment and addition operator. Adds another matrix to
   * this matrix.
   * @param mat1 The matrix to add.
   * @return Reference to the modified matrix after addition.
   */
  Matrix &operator+= (const Matrix &mat1);
  
  /**
   * @brief Parenthesis indexing operator. Allows access to matrix elements
   * using parentheses.
   * @param i The row index.
   * @param j The column index.
   * @return Reference to the element at the specified indices.
   */
  float &operator() (int i, int j);
  
  /**
   * @brief Parenthesis indexing operator (const version). Allows access to
   * matrix elements using parentheses.
   * @param i The row index.
   * @param j The column index.
   * @return The element at the specified indices.
   */
  float operator() (int i, int j) const;
  
  /**
   * @brief Brackets indexing operator. Allows access to matrix elements
   * using brackets.
   * @param i The element index.
   * @return Reference to the element at the specified index.
   */
  float &operator[] (int i);
  
  /**
   * @brief Brackets indexing operator (const version). Allows access to
   * matrix elements using brackets.
   * @param i The element index.
   * @return The element at the specified index.
   */
  float operator[] (int i) const;
  
  /**
   * @brief Output stream operator. Allows the matrix to be printed using
   * the << operator.
   * @param os The output stream.
   * @param mat The matrix to print.
   * @return Reference to the output stream.
   */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &mat);
  
  /**
   * @brief Input stream operator. Allows the matrix to be read from input
   * using the >> operator.
   * @param is The input stream.
   * @param mat The matrix to read into.
   * @return Reference to the input stream.
   */
  friend std::istream &operator>> (std::istream &is, Matrix &mat);
  
};

#endif //MATRIX_H
