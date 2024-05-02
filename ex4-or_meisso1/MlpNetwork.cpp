#include "MlpNetwork.h"


MlpNetwork::MlpNetwork (const Matrix *weights, const Matrix *biases):
dense1 (weights[0], biases[0], activation::relu),
dense2 (weights[1], biases[1], activation::relu),
dense3 (weights[2], biases[2], activation::relu),
dense4 (weights[3], biases[3], activation::softmax)
{}


digit MlpNetwork::operator() (Matrix &img_input)
{
  
  img_input.vectorize ();
  
  Matrix layer;
  
  layer = dense1 (img_input);
  layer = dense2 (layer);
  layer = dense3 (layer);
  layer = dense4 (layer);
  
  unsigned int max_idx = layer.argmax ();
  float probability = layer[max_idx];
  return {max_idx, probability};
  
}
  
