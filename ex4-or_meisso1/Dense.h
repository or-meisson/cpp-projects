#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"

/**
 * @class Dense
 * @brief Represents a dense layer in a neural network.
 *
 * The Dense class is responsible for performing the forward pass
 * calculations in a neural network. It applies a linear transformation
 * to the input data using weights and biases, followed by an activation
 * function.
 */
 


class Dense
{
 private:
  Matrix weights;                       /**< The weight matrix of the layer. */
  Matrix bias;                          /**< The bias matrix of the layer. */
  using ActivationFunctionType = Matrix (*)(const Matrix&);
  /**< Type alias for the activation function pointer. */
  ActivationFunctionType activationFunction;
  /**< The activation function of the layer. */
 
 public:
  /**
   * @brief Constructs a Dense layer with the given weights, biases,
   * and activation function.
   *
   * @param weights_ The weight matrix of the layer.
   * @param bias_ The bias matrix of the layer.
   * @param ActivationFunction_ The activation function of the layer.
   */
  Dense(const Matrix &weights_, const Matrix &bias_, Matrix
  (ActivationFunction_)(Matrix const &));
  
  /**
   * @brief Retrieves the weight matrix of the layer.
   *
   * @return The weight matrix.
   */
  Matrix get_weights() const;
  
  /**
   * @brief Retrieves the bias matrix of the layer.
   *
   * @return The bias matrix.
   */
  Matrix get_bias() const;
  
  /**
   * @brief Retrieves the activation function of the layer.
   *
   * @return A pointer to the activation function.
   */
  ActivationFunctionType get_activation() const;
  /**
   * @brief Performs the forward pass calculations for the layer.
   *
   * @param x The input matrix.
   * @return The output matrix after applying the layer's transformation
   * and activation.
   */
  Matrix operator()(const Matrix &x) const;
};

#endif // DENSE_H
