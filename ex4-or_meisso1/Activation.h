#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

// Insert Activation class here...



namespace activation
{
	/**
	 * @brief Applies the Rectified Linear Unit (ReLU) activation function
	 * element-wise to the input matrix.
	 *
	 * The ReLU activation function returns the input value if it is positive,
	 * and zero otherwise.
	 *
	 * @param matrix The input matrix.
	 * @return The matrix with ReLU activation applied element-wise.
	 */
	Matrix relu(Matrix const &matrix);
	
	/**
	 * @brief Applies the Softmax activation function to the input matrix.
	 *
	 * The Softmax activation function normalizes the values of the input
	 * matrix to represent a probability
	 * distribution over the classes.
	 *
	 * @param matrix The input matrix.
	 * @return The matrix with Softmax activation applied.
	 */
	Matrix softmax(Matrix const &matrix);
}

#endif //ACTIVATION_H
