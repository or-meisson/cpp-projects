// Matrix.cpp
#include "Matrix.h"
#include "iostream"
#include <cmath>

#define DIMENSION_ERROR "wrong dimensions"
#define INVALID_INPUT "invalid input"
#define OUT_OF_RANGE_ERROR "index not in matrix range"
#define PRINT_ASTERISK_COND 0.1




////////////////operators//////////////////



// assignment and add operator
Matrix &Matrix::operator+= (const Matrix &mat1)
{
  if (mat1.dimensions.rows != dimensions.rows || mat1.dimensions.cols
												 != dimensions.cols)
  {
	throw std::length_error (DIMENSION_ERROR);
  }
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  mat[i][j] = mat[i][j] + mat1 (i, j);
	}
  }
  return *this;
}

//multiplication operator, scalar on the left
Matrix operator* (float scalar, const Matrix &mat1)
{
  Matrix matrix (mat1);
  for (int i = 0; i < matrix.get_rows (); i++)
  {
	for (int j = 0; j < matrix.get_cols (); j++)
	{
	  matrix (i, j) *= scalar;
	}
  }
  return matrix;
}

//multiplication operator, scalar on the right
Matrix Matrix::operator* (float scalar) const
{
  Matrix matrix (dimensions.rows, dimensions.cols);
  
  for (int i = 0; i < matrix.dimensions.rows; i++)
  {
	for (int j = 0; j < matrix.dimensions.cols; j++)
	{
	  matrix.mat[i][j] = mat[i][j] * scalar;
	}
  }
  return matrix;
}

//multiplication operator
Matrix operator* (const Matrix &mat1, const Matrix &mat2)
{
  int rows1 = mat1.dimensions.rows;
  int cols1 = mat1.dimensions.cols;
  int rows2 = mat2.dimensions.rows;
  int cols2 = mat2.dimensions.cols;
  if (cols1 != rows2)
  {
	throw std::length_error (DIMENSION_ERROR);
  }
  Matrix mat (rows1, cols2);
  for (int i = 0; i < rows1; i++)
  {
	for (int j = 0; j < cols2; j++)
	{
	  float sum = 0;
	  for (int k = 0; k < cols1; k++)
	  {
		sum += mat1.mat[i][k] * mat2.mat[k][j];
	  }
	  mat.mat[i][j] = sum;
	}
  }
  return mat;
}

// plus operator
Matrix operator+ (const Matrix &mat1, const Matrix &mat2)
{
  int rows1 = mat1.dimensions.rows;
  int cols1 = mat1.dimensions.cols;
  int rows2 = mat2.dimensions.rows;
  int cols2 = mat2.dimensions.cols;
  if (rows1 != rows2 || cols1 != cols2)
  {
	throw std::length_error (DIMENSION_ERROR);
  }
  Matrix mat (rows1, cols1);
  for (int i = 0; i < rows1; i++)
  {
	for (int j = 0; j < cols1; j++)
	{
	  mat.mat[i][j] = mat1 (i, j) + mat2 (i, j);
	}
  }
  return mat;
}

//assignment operator
Matrix &Matrix::operator= (const Matrix &other)
{
  if (this == &other)
  { return *this; }
  for (int i = 0; i < dimensions.rows; i++)
  {
	delete[] mat[i];
  }
  delete[] mat;
  dimensions.rows = other.dimensions.rows;
  dimensions.cols = other.dimensions.cols;
  mat = new float *[dimensions.rows];
  for (int i = 0; i < dimensions.rows; i++)
  { mat[i] = new float[dimensions.cols]; }
  
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  mat[i][j] = other.mat[i][j];
	}
  }
  
  return *this;
}

//Parenthesis() indexing
float &Matrix::operator() (int i, int j)
{
  if (i < 0 || j < 0 || i >= dimensions.rows || j >= dimensions.cols)
  {
	throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  return mat[i][j];
}

float Matrix::operator() (int i, int j) const
{
  if (i < 0 || j < 0 || i >= dimensions.rows || j >= dimensions.cols)
  {
	throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  return mat[i][j];
}

//Brackets[] indexing
float Matrix::operator[] (int i) const
{
  if (i < 0 || i >= dimensions.rows * dimensions.cols)
  {
	throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  int j = 0;
  for (int k = 0; k < dimensions.rows; k++)
  {
	for (int t = 0; t < dimensions.cols; t++)
	{
	  if (j == i)
	  {
		return mat[k][t];
	  }
	  j++;
	}
  }
  throw std::out_of_range (OUT_OF_RANGE_ERROR);
}

//Brackets[] indexing
float &Matrix::operator[] (int i)
{
  if (i < 0 || i >= dimensions.rows * dimensions.cols)
  {
	throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  int j = 0;
  for (int k = 0; k < dimensions.rows; k++)
  {
	for (int t = 0; t < dimensions.cols; t++)
	{
	  if (j == i)
	  {
		return mat[k][t];
	  }
	  j++;
	}
  }
  throw std::out_of_range (OUT_OF_RANGE_ERROR);
}



////////////////////////////member functions///////////////////////////////////

//default constructor
Matrix::Matrix ()
{
  dimensions.rows = 1;
  dimensions.cols =1;
  mat = new float *[dimensions.rows];
  mat[0] = new float[dimensions.cols];
  mat[0][0] = 0;
}

//Parameterized constructor
Matrix::Matrix (int num_of_rows, int num_of_cols)
{
  if (num_of_rows < 1 || num_of_cols < 1)
  {
	  throw std::length_error (DIMENSION_ERROR);
  }
  dimensions.rows = num_of_rows;
  dimensions.cols = num_of_cols;
  mat = new float *[dimensions.rows];
  for (int i = 0; i < dimensions.rows; i++)
  {
	mat[i] = new float[dimensions.cols];
  }
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  mat[i][j] = 0;
	}
  }
}

//destructor
Matrix::~Matrix ()
{
  for (int i = 0; i < dimensions.rows; i++)
  {
	delete[] mat[i];
  }
  delete[] mat;
}

//getter for rows
int Matrix::get_rows () const
{
  return dimensions.rows;
}
//getter for columns
int Matrix::get_cols () const
{
  return dimensions.cols;
}

Matrix &Matrix::transpose ()
{

  Matrix transposed (dimensions.cols, dimensions.rows);
  for (int i = 0; i < dimensions.cols; i++)
  {
	for (int j = 0; j < dimensions.rows; j++)
	{
	  transposed (i, j) = mat[j][i];
	}
  }
  (*this) = transposed;
  
  return (*this);
}

//vectorize
Matrix &Matrix::vectorize ()
{
  Matrix vectorized (dimensions.rows * dimensions.cols, 1);
  int idx = 0;
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  vectorized (idx, 0) = mat[i][j];
	  idx++;
	}
  }
  
  
  
  dimensions.cols = 1;
  dimensions.rows = dimensions.rows * dimensions.cols;
  (*this) = vectorized;

  return (*this);
}

//plain print
void Matrix::plain_print () const
{
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  std::cout << mat[i][j] << " ";
	}
	std::cout << std::endl;
  }
}

//dot
Matrix Matrix::dot (const Matrix &mat1) const
{
  int rows1 = mat1.dimensions.rows;
  int cols1 = mat1.dimensions.cols;
  if (rows1 != dimensions.rows || cols1 != dimensions.cols)
  {
	throw std::length_error (DIMENSION_ERROR);
  }
  Matrix new_mat (dimensions.rows, dimensions.cols);
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  new_mat.mat[i][j] = mat[i][j] * mat1 (i, j);
	}
  }
  return new_mat;
}

//pretty print
std::ostream &operator<< (std::ostream &os, Matrix const &mat)
{if(!os){
  throw std::runtime_error(INVALID_INPUT);
}
  for (int i = 0; i < mat.get_rows (); i++)
  {
	for (int j = 0; j < mat.get_cols (); j++)
	{
	  if (mat (i, j) > PRINT_ASTERISK_COND)
	  {
		os << "**";
	  }
	  else
	  { os << "  "; }
	}
	os << std::endl;
  }
  
  return os;
}

//handle input - build matrix
std::istream &operator>> (std::istream &is, Matrix &mat)
{
  if (!is)
  {
	throw std::runtime_error (INVALID_INPUT);
  }
  for (int i = 0; i < mat.dimensions.rows * mat.dimensions.cols; i++)
  {
	is.read ((char *) &mat[i], sizeof (float));
	if (!is.good ())
	{
	  throw std::runtime_error (INVALID_INPUT);
	}
	
  }
  return is;
}

//norm
float Matrix::norm () const
{
  float norm = 0;
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  norm += mat[i][j] * mat[i][j];
	}
  }
  return std::sqrt (norm);
}

//argmax
int Matrix::argmax () const
{
  float max_num = mat[0][0];
  int max_idx = 0;
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  if (mat[i][j] > max_num)
	  {
		max_num = mat[i][j];
		max_idx = i * dimensions.cols + j;
	  }
	}
  }
  return max_idx;
}

//sum
float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  sum += mat[i][j];
	}
  }
  return sum;
}

//copy constructor
Matrix::Matrix (const Matrix &mat_to_copy)
{
  dimensions.rows = mat_to_copy.dimensions.rows;
  dimensions.cols = mat_to_copy.dimensions.cols;
  
  mat = new float *[dimensions.rows];
  for (int i = 0; i < dimensions.rows; i++)
  { mat[i] = new float[dimensions.cols]; }
  for (int i = 0; i < dimensions.rows; i++)
  {
	for (int j = 0; j < dimensions.cols; j++)
	{
	  mat[i][j] = mat_to_copy (i, j);
	}
  }
}
