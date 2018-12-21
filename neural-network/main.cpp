#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// Initialize the weights between all layers with random numbers between 0.0 and 1.0
void initializeWeights(vector<vector<float>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    for (size_t j = 0; j < layer[i].size(); j++) {
      float randWeight = (rand() % 1000) / 1000.0;
      layer[i][j] = randWeight;
    }
  }
}

// Display any one of the weight layers
void displayLayer(const vector<vector<float>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    for (size_t j = 0; j < layer[i].size(); j++) {
      cout << layer[i][j] << " "; 
    }
    cout << endl;
  }
}

// Display any of the perceptron layers
void displayLayer(const vector<float>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    cout << layer[i] << endl;
  }
}

// Activation function (Sigmoid) f = 1 / (1 + e^-x)
float activation(float x) {
  return (1 / (1 + exp(-x)));
}


// Derivative of activation function (Sigmoid) f' = e^x / (1 + e^x)
float derivSigmoid(float x) {
  return (exp(-x) / pow((1 + exp(-x)), 2));
}

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
float neuronOutput(const vector<float>& input, const vector<float>& weights) {
  float weightSum = weightedSum(input, weights);
  cout << "Weighted sum of inputs: " << weightSum << endl;
  float output = activation(weightSum);
  cout << "Neuron Output: " << output << endl;
  return output;
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
 updateOutputWeights(weightLayer, learningRate, inputLayer, deltas) {
   for (size_t i = 0; i < weightLayer.size(); i++) { 
     for (size_t j = 0; j < weightLayer[i].size() - 1; j++) {
        weightLayer[i][j] += learningRate * inputLayer[j] * deltas[i];
     }
   }
      
 }
*/

/*
updateHiddenWeights(weightLayer, learningRate, inputLayer, deltas) {
  for (size_t i = 0; i < weightLayer.size(); i++) {
    for (size_t j = 0; j < weightLayer[i].size() - 1; j++) {
      weightLayer[i][j] += learningRate * inputLayer[j] * deltas[i];
    }
  }
}
*/

/*

void backPropagate(vector<float>& outputLayer, vector<vector<float>>& outWeights, vector<float>& hiddenLayer, vector<vector<float>>& hidWeights, vector<float>& inputLayer, vector<float>& idealOutput) {
  // Store deltas for output and hidden layer neurons in vectors
  vector<float> outputDeltas(5);
  vector<float> hiddenDeltas(100);

  // Loop through size of output layer in order to compute delta for each neuron and store in vector
  for (size_t i = 0; i < output.size(); i++) {
    // Error = ideal - actual
    float err = ideal  - outputLayer[i];

    // Compute the weighted sum between these layers for the ith output neuron
    float weightSum = weightedSum(hiddenLayer, outWeights[i]);

    float delta = err * derivSigmoid(weightSum);
    outputDelta[i] = delta;
  }
  
  // Update weights between output layer and hidden layer 
  updateOutputWeights(weightLayer, learningRate, hiddenLayer, deltas);

  // Loop through size of hidden layer in order to compute deltas for hidden layer neurons
  for (size of hidden layer) {  
    float delta = derivSigmoid(weightedSum(hiddenLayer[i])) * sumofAll (( weight of W(ji) * delta for neuron i ))
    hiddenDeltas[i] = delta;
  }

  // Update weights between hidden layer and input layer using back propagation 
  updateHiddenWeights(weightLayer, learningRate, inputLayer, deltas);
  

}

*/

void neuralNetwork(int numHidden) {
  const float learningRate = 0.2;
  float err = 1.0;

  vector<float> inputLayer(748, 0.002);
  vector<vector<float>> hidWeights(100, vector<float>(749, 0.2));
  vector<float> hiddenLayer(numHidden);
  vector<vector<float>> outWeights(5, vector<float>(101,0.5));
  vector<float> outputLayer(5);

  outputLayer.push_back(5);
  // initializeWeights(hidWeights);
  // initializeWeights(outWeights);

  float output = neuronOutput(inputLayer, hidWeights[0]);
  float weightSum = weightedSum(inputLayer, hidWeights[0]);
  cout << "Weighted sum of hidden layer neuron 0 is: " << weightSum << endl;

  // assert("Hidden neuron 0", 0.248, output);
  // assert("Hidden neuron 0 output" , 0.52478, output);
  
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

    neuralNetwork(100);

}