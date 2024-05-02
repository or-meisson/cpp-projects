#include "Dense.h"

Dense::Dense(const Matrix& weights_, const Matrix& bias_,
			 ActivationFunctionType activationFunction_)
	: weights(weights_), bias(bias_), activationFunction(activationFunction_)
{
}

Matrix Dense::get_weights() const
{
  return weights;
}

Matrix Dense::get_bias() const
{
  return bias;
}

Dense::ActivationFunctionType Dense::get_activation() const
{
  return activationFunction;
}

Matrix Dense::operator()(const Matrix &x) const
{
  Matrix res = Matrix (bias.get_rows (), bias.get_cols ());
  res = weights * x;
  res += bias;
  return activationFunction(res);
}
