#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

/*
Created by Zafir Hasan for Artificial Intelligence (CS-UY 4315). The goal of this program is to create an artificial neural network that can recognize the digits 0-4 in handwriting. This will be a 2 layer fully-connected network that will be trained through back propagation. 
*/

const int NUM_HIDDEN_NEURONS = 100;
const float LEARNING_RATE = 0.2;


// Initialize the weights between all layers with random numbers between 0.0 and 1.0
// COMPLETED TESTS
void initializeWeights(vector<vector<float>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    for (size_t j = 0; j < layer[i].size(); j++) {
      float randWeight = (rand() % 1000) / 1000.0;
      layer[i][j] = randWeight;
    }
  }
}

// Display any one of the weight layers
// COMPLETED TESTS
void displayLayer(const vector<vector<float>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    for (size_t j = 0; j < layer[i].size(); j++) {
      cout << layer[i][j] << " "; 
    }
    cout << endl;
  }
}

// Display any of the perceptron layers
// COMPLETED TESTS
void displayLayer(const vector<float>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    cout << layer[i] << endl;
  }
}

// Activation function (Sigmoid) f = 1 / (1 + e^-x)
// COMPLETED TESTS
float activation(float x) {
  return (1 / (1 + exp(-x)));
}


// Derivative of activation function (Sigmoid) f' = e^x / (1 + e^x)
// COMPLETED ALL TESTS
float derivActivation(float x) {
  return (exp(-x) / pow((1 + exp(-x)), 2));
}

// Compute weighted sum of inputs to a neuron
// COMPLETED TESTS
float weightedSum(const vector<float>& input, const vector<float>& weights) {
  float weightSum = 0;
  for (size_t i = 0; i <= input.size(); i++) {
    if (i == input.size()) {
      weightSum += -1 * weights[i];
    }
    else {
      weightSum += input[i] * weights[i];
    }  
  }
  return weightSum;
}

// Compute output of single neuron
// COMPLETED TESTS
float neuronOutput(const vector<float>& input, const vector<float>& weights) {
  float weightSum = weightedSum(input, weights);
  cout << "Weighted sum of inputs: " << weightSum << endl;
  float output = activation(weightSum);
  cout << "Neuron Output: " << output << endl;
  return output;
}

// Compute output of all neurons in a layer 
// COMPLETED TESTS
void updateNeurons(const vector<float>& inputs, const vector<vector<float>>& weights, vector<float>& outputs) {
  for (size_t i = 0; i < outputs.size(); i++) {
    float output = neuronOutput(inputs, weights[i]);
    outputs[i] = output;
  }
}

void assert(const string& desc, float correctOut, float output) {
  cout << desc << " SHOULD BE: " << correctOut << endl;
  cout << desc << " IS : " << output << endl;
  correctOut = (int)(correctOut / 0.0001) * 0.0001; 
  output = (int)(output / 0.0001) * 0.0001; 
  
  if (correctOut == output) {
    cout << "TEST PASSED" << endl;
  }
  else {
    cout << "TEST FAILED" << endl;
  }
}

/*
void updateWeights(weightLayer, learningRate, inputLayer, deltas) {
   for (size_t i = 0; i < weightLayer.size(); i++) { 
     for (size_t j = 0; j < weightLayer[i].size() - 1; j++) {
        weightLayer[i][j] += learningRate * inputLayer[j] * deltas[i];
     }
   }
      
 }
*/

/*
float sumWeightDeltas(const vector<vector<float>>& weights, const vector<float>& deltas, int neuronIndex) {
  float weightSum = 0;
  for (size_t i = 0; i < weights.size(); i++) {
    weightSum += weights[i][neuronIndex] * delta[i];
  }
  return weightSum;
}
*/

/*
void backPropagate(vector<float>& outputLayer, vector<vector<float>>& outWeights, vector<float>& hiddenLayer, vector<vector<float>>& hidWeights, vector<float>& inputLayer, vector<float>& idealOutput) {
  // Store deltas for output and hidden layer neurons in vectors
  vector<float> outputDeltas(5);
  vector<float> hiddenDeltas(100);

  // Loop through size of output layer in order to compute delta for each neuron and store in vector
  for (size_t i = 0; i < outputLayer.size(); i++) {
    // Error = ideal - actual
    float err = ideal  - outputLayer[i];

    // Compute the weighted sum between these layers for the ith output neuron
    float weightSum = weightedSum(hiddenLayer, outWeights[i]);

    float delta = err * derivActivation(weightSum);
    outputDelta[i] = delta;
  }*/
  
  /*
  // Update weights between output layer and hidden layer 
  updateWeights(outWeights, learningRate, hiddenLayer, outputDeltas);

  // Loop through size of hidden layer in order to compute deltas for hidden layer neurons
  for (size_t i = 0; i < hiddenLayer.size(); i++) {  
    // Compute deltas for hidden layer neurons after updating weights between hiddn layer and output layer
    float delta = derivActivation(weightedSum(inputLayer, hidWeights[i])) * sumWeightDeltas(outWeights, outputDeltas, i);
    hiddenDeltas[i] = delta;
  }

  // Update weights between hidden layer and input layer using back propagation 
  updateWeights(hidWeights, learningRate, inputLayer, hiddenDeltas);
  */

// }


void neuralNetwork(int numHidden) {
  const float learningRate = 0.2;
  float err = 1.0;

  vector<float> inputLayer(748, 0.002);
  vector<vector<float>> hidWeights(numHidden, vector<float>(749, 0.2));
  vector<float> hiddenLayer(numHidden, 0.0);
  vector<vector<float>> outWeights(5, vector<float>(101,0.5));
  vector<float> outputLayer(5);

  // initializeWeights(hidWeights);
  // initializeWeights(outWeights);




  // Test for updating all neuron layers with appropriate output
  cout << "Updating all hidden layer neurons using inputs and weights" << endl;
  updateNeurons(inputLayer, hidWeights, hiddenLayer);
  displayLayer(hiddenLayer);
  updateNeurons(hiddenLayer, outWeights, outputLayer);
  displayLayer(outputLayer);

  // backPropagate()
  

/*
  Tests for neuron output
  cout << "Testing neuron output of hiddenLayer[0]:" << endl;
  float output = neuronOutput(inputLayer, hidWeights[0]);

  cout << endl;
  cout << "Testing neuron output of outputLayer[0]:" << endl;
  float output1 = neuronOutput(hiddenLayer, outWeights[0]);

*/

/*
  Tests for weighted sum of neuron
  float weightSum = weightedSum(inputLayer, hidWeights[0]);
  cout << "Weighted sum of hiddenLayer[0]: " << weightSum << endl;

  float weightSum1 = weightedSum(hiddenLayer, outWeights[0]);
  cout << "Weighted sum of outputLayer[0]: " << weightSum1 << endl;

*/
  
  /*
  initializeActualOutputs
  initializeInputs(file);
  while (err > 2%) {
    computeNodes(hiddenLayer, hiddenWeights, inputLayer);
    computeNodes(outputLayer, outWeights, hiddenLayer);
    backPropagate(outputLayer, outWeights, hiddenLayer, hidWeights, inputLayer, vector of actual ANSWER);

  }

  */

}


int main() {

    neuralNetwork(NUM_HIDDEN_NEURONS);





    /*
    Tests for the derivative of the activation function (derivActivation)
    cout << "Testing derivative sigmoid function" << endl;
    cout << "Input of 26.11: " << derivActivation(26.11) << endl;
    cout << "Input of 0.0: " << derivActivation(0.0) << endl;
    cout << "Input of 0.5226: " << derivActivation(0.5226) << endl;
    */

}