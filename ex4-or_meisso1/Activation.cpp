#include "Activation.h"
#include <cmath>

Matrix activation::relu (const Matrix &matrix)
{
  int rows = matrix.get_rows ();
  int cols = matrix.get_cols ();
  Matrix new_mat  (rows, cols);
  for (int i = 0; i < rows; i++)
  {
	for (int j = 0; j < cols; j++)
	{
	  new_mat (i, j) = (float) fmax (0, matrix (i, j));
	}
  }
  return new_mat;
}

Matrix activation::softmax (Matrix const &matrix)
{
  int rows = matrix.get_rows ();
  int cols = matrix.get_cols ();
  Matrix new_mat (rows, cols);
  for (int i = 0; i < rows; i++)
  {
	for (int j = 0; j < cols; j++)
	{
	  new_mat (i, j) = std::exp (matrix (i, j));
	}
  }
  new_mat = new_mat * (1 / new_mat.sum ());
  
  return new_mat;
}

