#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Represents an identified digit with the associated probability.
 * @var value The identified digit value.
 * @var probability The identification probability.
 */
typedef struct digit
{
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

/**
 * @class MlpNetwork
 * @brief Represents a Multi-Layer Perceptron (MLP) network
 * for digit identification.
 *
 * The MlpNetwork class is responsible for performing digit identification
 * using a Multi-Layer Perceptron (MLP) network.
 *  It consists of multiple Dense layers with specified weights, biases, and
 *  activation functions.
 *
 */
class MlpNetwork
{
 private:
  Dense dense1; /**< The first Dense layer of the MLP network. */
  Dense dense2; /**< The second Dense layer of the MLP network. */
  Dense dense3; /**< The third Dense layer of the MLP network. */
  Dense dense4; /**< The fourth Dense layer of the MLP network. */
 
 public:
  /**
   * @brief Constructs an MlpNetwork with the given weights and biases.
   *
   * @param weights_ An array of weight matrices for each layer.
   * @param biases_ An array of bias matrices for each layer.
   */
  MlpNetwork(const Matrix weights[], const Matrix biases[]);

  
  /**
   * @brief Performs digit identification using the MLP network on the
   * input image.
   *
   * @param img_input The input image matrix.
   * @return The identified digit and its associated probability.
   */
  digit operator() (Matrix &img_input);
};

#endif // MLPNETWORK_H
