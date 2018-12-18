#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;


void initializeWeights(vector<vector<float>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    for (size_t j = 0; j < layer[i].size(); j++) {
      float randWeight = (rand() % 1000) / 1000.0;
      layer[i][j] = randWeight;
    }
  }
}

void displayLayer(const vector<vector<float>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    for (size_t j = 0; j < layer[i].size(); j++) {
      cout << layer[i][j] << " "; 
    }
    cout << endl;
  }
}

void displayLayer(const vector<float>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    cout << layer[i] << endl;
  }
}

float activation(float x) {
  return (1 / (1 + exp(-x)));
}

float derivSigmoid(float x) {
  return (exp(-x) / pow((1 + exp(-x)), 2));
}

float neuronOutput(const vector<float>& input, const vector<float>& weights) {
  float weightSum = 0;
  for (size_t i = 0; i <= input.size(); i++) {
    if (i == input.size()) {
      weightSum += -1 * weights[i];
    }
    else {
      weightSum += input[i] * weights[i];
    }  
  }
  // float weightSum = weightedSum(input, weights);

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

 updateWeights(weightLayer, learningRate, deltas) {
 
 }
*/

/*
void backPropagate(all the layers and weights) {
  vector<float> outputDeltas(5);
  vector<float> hiddenDeltas(100);
  
  for (size of output layer) {
    float err = ideal  - outputLayer[i];
    float weightSum = weightedSum(hiddenLayer, outWeights[i]);
    float delta = err * derivSigmoid(weightSum);
    outputDelta[i] = delta;
  }
  
  updateWeights(weightLayer, learningRate, hiddenLayer, deltas);

  for (size of hidden layer) {  
    float delta = derivSigmoid(weightedSum(hiddenLayer[i])) * sumofAll (( weight of W(ji) * delta for neuron i ))
    hiddenDeltas[i] = delta;
  }

  updateWeights(weightLayer, learningRate, inputLayer, deltas);
  

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
  initializeWeights(hidWeights);
  initializeWeights(outWeights);

  float output = neuronOutput(inputLayer, hidWeights[0]);
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
    float x = derivSigmoid(0.67);
    cout << x << endl;
}