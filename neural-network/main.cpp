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

void neuralNetwork(int numHidden) {
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
  


}


int main() {

    neuralNetwork(100);


}