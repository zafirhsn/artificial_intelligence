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

float nodeOutput(const vector<float>& input, const vector<float>& weights) {
  float weightSum = 0;
  for (size_t i = 0; i < input.size(); i++) {
    weightSum += input[i] * weights[i];
  }
  cout << "Weighted sum of inputs: " << weightSum << endl;
  float output = activation(weightSum);
  cout << "Output: " << output << endl;
  return output;
}

void neuralNetwork(int numHidden) {
  vector<float> inputLayer(748, 0.002);
  vector<vector<float>> hidWeights(100, vector<float>(748,0.5));
  vector<float> hiddenLayer(numHidden);
  vector<vector<float>> outWeights(5, vector<float>(100));
  vector<float> outputLayer(5);

  outputLayer.push_back(5);
  // initializeWeights(hidWeights);
  initializeWeights(outWeights);

  float output = nodeOutput(inputLayer, hidWeights[0]);

  cout << output << endl;


}


int main() {
    cout << "Hello world" << endl;

    neuralNetwork(100);

    cout << activation(0.5) << endl;





}