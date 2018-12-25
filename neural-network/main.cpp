#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;

/*
Created by Zafir Hasan for Artificial Intelligence (CS-UY 4315). The goal of this program is to create an artificial neural network that can recognize the digits 0-4 in handwriting. This will be a 2 layer fully-connected network that will be trained through back propagation. 
*/

const int NUM_HIDDEN_NEURONS = 100;
const int NUM_OUTPUT_NEURONS = 5;
const long double LEARNING_RATE = 0.01;
const int TRAINING_IMAGE_COUNT = 28038;
const int TESTING_IMAGE_COUNT = 2561;
const long double CUTOFF_ERROR = 0.00005;
const int HIDDEN_BIAS = -100000;
const int OUT_BIAS = -1;

vector<long double> inputLayer(784);
vector<vector<long double>> hidWeights(NUM_HIDDEN_NEURONS, vector<long double>(785, 0.0));
vector<long double> hiddenLayer(NUM_HIDDEN_NEURONS);
vector<vector<long double>> outWeights(NUM_OUTPUT_NEURONS, vector<long double>(NUM_HIDDEN_NEURONS+1, 0.0));
vector<long double> outputLayer(NUM_OUTPUT_NEURONS);

// Initialize the weights between all layers with random numbers between 0.0 and 1.0
// COMPLETED TESTS
void initializeWeights(vector<vector<long double>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    for (size_t j = 0; j < layer[i].size(); j++) {
      long double randWeight = (rand() % 10000) / 100000000.0;
      layer[i][j] = randWeight;
    }
  }
}

// Display any one of the weight layers
// COMPLETED TESTS
void displayLayer(const vector<vector<long double>>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
		// cout << "All weights for layer[" << i << "]:" << endl;
    for (size_t j = 0; j < layer[i].size(); j++) {
      cout << layer[i][j] << " "; 
    }
    cout << endl;
  }
}

// Display any of the perceptron layers
// COMPLETED TESTS
void displayLayer(const vector<long double>& layer) {
  for (size_t i = 0; i < layer.size(); i++) {
    cout << layer[i] << endl;
  }
}

// Activation function (Sigmoid) f = 1 / (1 + e^-x)
// COMPLETED TESTS
long double activation(long double x) {
  return (1 / (1 + exp(-x)));
}

// Derivative of activation function (Sigmoid) f' = e^x / (1 + e^x)
// COMPLETED ALL TESTS
long double derivActivation(long double x) {
  return (exp(-x) / pow((1 + exp(-x)), 2));
}

// Compute weighted sum of inputs to a neuron
// COMPLETED TESTS
long double weightedSum(const vector<long double>& input, const vector<long double>& weights, int bias) {
  long double weightSum = 0;
  for (size_t i = 0; i <= input.size(); i++) {
    if (i == input.size()) {
      weightSum += bias * weights[i];
    }
    else {
      weightSum += input[i] * weights[i];
    }  
  }
  return weightSum;
}

// Compute output of single neuron
// COMPLETED TESTS
long double neuronOutput(const vector<long double>& input, const vector<long double>& weights, int bias) {
  long double weightSum = weightedSum(input, weights, bias);
  // cout << "Weighted sum of inputs: " << weightSum << endl;
  long double output = activation(weightSum);
  // cout << "Neuron Output: " << output << endl;
  return output;
}

// Compute output of all neurons in a layer 
// COMPLETED TESTS
void updateNeurons(const vector<long double>& inputs, const vector<vector<long double>>& weights, vector<long double>& outputs, int bias) {
  for (size_t i = 0; i < outputs.size(); i++) {
    long double output = neuronOutput(inputs, weights[i], bias);
    outputs[i] = output;
  }
}

// Update weights using weight update rule
// COMPLETED TESTS 
void updateWeights(vector<vector<long double>>& weightLayer, long double learningRate, const vector<long double>& inputLayer, const vector<long double>& deltas) {
   for (size_t i = 0; i < weightLayer.size(); i++) { 
     for (size_t j = 0; j < weightLayer[i].size(); j++) {
        if (j == weightLayer[i].size() - 1) {
          weightLayer[i][j] += (learningRate * -1 * deltas[i]);
        }
        else {
          weightLayer[i][j] += (learningRate * inputLayer[j] * deltas[i]);
        }  
     }
   }    
}

// Calculate sum of weighted sum of outgoing weights x outputlayer deltas for hidden layer deltas 
// COMPLETED TESTS
long double sumWeightDeltas(const vector<vector<long double>>& weights, const vector<long double>& deltas, int neuronIndex) {
  long double weightSum = 0;
  for (size_t i = 0; i < weights.size(); i++) {
    weightSum += weights[i][neuronIndex] * deltas[i];
  }
  return weightSum;
}

// Back propagation training
// COMPLETED TESTS
void backPropagate(vector<long double>& outputLayer, vector<vector<long double>>& outWeights, vector<long double>& hiddenLayer, vector<vector<long double>>& hidWeights, vector<long double>& inputLayer, vector<long double>& labels) {
  // Store deltas for output and hidden layer neurons in vectors
  vector<long double> outputDeltas(NUM_OUTPUT_NEURONS);
  vector<long double> hiddenDeltas(NUM_HIDDEN_NEURONS);

  // Loop through size of output layer in order to compute delta for each neuron and store in vector
  for (size_t i = 0; i < outputLayer.size(); i++) {
    // Error = ideal - actual
    long double err = labels[i] - outputLayer[i];
		// cout << "The error for outlayer[" << i << "] is: " << err << endl;

    // Compute the weighted sum between these layers for the ith output neuron
    long double weightSum = weightedSum(hiddenLayer, outWeights[i], OUT_BIAS);
		// cout << "The weighted sum of outputLayer[" << i << "] is: " << weightSum << endl;


    long double delta = err * derivActivation(weightSum);
		// cout << "The DELTA of outputLayer[" << i << "] is: " << delta << endl;
		// cout << endl;
		outputDeltas[i] = delta;
  }
   
  // Update weights between output layer and hidden layer 
  updateWeights(outWeights, LEARNING_RATE, hiddenLayer, outputDeltas);
	// displayLayer(outWeights);
	cout << endl;

  // Loop through size of hidden layer in order to compute deltas for hidden layer neurons
  for (size_t i = 0; i < hiddenLayer.size(); i++) {  
    // Compute deltas for hidden layer neurons after updating weights between hiddn layer and output layer
		long double sumoutgoingWeights = sumWeightDeltas(outWeights, outputDeltas, i);
    long double weightSum = weightedSum(inputLayer, hidWeights[i], HIDDEN_BIAS);
    // cout << "The weighted sum of hiddenLayer[" << i << "] is: " << weightSum << endl;
    long double delta = derivActivation(weightSum) * sumoutgoingWeights;
		// cout << "The sum of all outgoing weights of hiddenLayer[" << i << "] is: " << sumoutgoingWeights << endl; 

		// cout << "The DELTA of hiddenLayer[" << i << "] is: " << delta << endl;
    hiddenDeltas[i] = delta;
  }

  // Update weights between hidden layer and input layer using back propagation 
  updateWeights(hidWeights, LEARNING_RATE, inputLayer, hiddenDeltas);
	// displayLayer(hidWeights);
}

// Initialize the image labels using either train_labels.txt or test_labels.txt
// COMPLETED TESTS
void initializeLabels(vector<vector<long double>>& labels, const string filename) {
 	ifstream ifs(filename); 
  if (!ifs) {
    cerr << "Could not open the file.\n";
    exit(1);
  }
  else {
    cout << "File has been opened successfully" << endl;
  }

	string line;
  while(getline(ifs, line)) {
		vector<long double> imgLabel; 
		for (char c : line) {
			if (c != ' ') {
				int n = c - 48;
				imgLabel.push_back((long double)n);
			}
		}
		labels.push_back(imgLabel);
	}
}

// Read in binary image data and convert to decimal. Then store values into inputLayer
// COMPLETED TESTS
void readImage(string filename, vector<vector<long double>>& inputs, int imageCount) {
	FILE *fp1;
	
	short c;
	int h, i, j, header, x, y;
	header = 0;
	x = 28;
	y = 28;
	// char file1[20] = filename;
  const char* file = filename.c_str();

	if((fp1 = fopen(file, "rb")) == NULL) {
		printf("cannot open %s\n", filename);
		exit(1);
	}
	else {
		cout << "Reading image successfully..." << endl;
	}

	for (i = 1; i <= header; i++) {  // skip the header 
		c = getc(fp1);
	}

	int countPixels = 0;
	// fprintf(fp2,"%4d",x);  fprintf(fp2,"%4d",y);
  for (h = 0; h < imageCount; h++) {
    vector<long double> img;
    for (i = 1; i <= y; i++) {
      for (j = 1; j <= x; j++)
        {
          c = getc(fp1);
          // cout << c << " ";
          img.push_back((long double)c);
          countPixels++;
        }
        // cout << endl;
    }
    // cout << countPixels << endl;
    // cout << endl;
    inputs.push_back(img);
    countPixels = 0;
  }
	fclose(fp1);
  cout << "All images parsed" << endl;
}

// Compute the squared error for a certain image
// COMPLETED TESTS
long double squaredErr(const vector<long double>& label, const vector<long double>& outputs) {
  long double err = 0.0;
  for (size_t i = 0; i < label.size(); i++) {
    err += pow((label[i] - outputs[i]), 2);
  }
  err *= 0.5;
  return err;
}

// Initialize the input layer with the current image 
// COMPLETED TESTS
void initializeInputs(const vector<long double>& inputs, vector<long double>& inputLayer) {
  for (size_t i = 0; i < inputs.size(); i++) {
    inputLayer.push_back(inputs[i]);
  }
}

void trainNetwork(vector<long double>& outputLayer, vector<vector<long double>>& outWeights, vector<long double>& hiddenLayer, vector<vector<long double>>& hidWeights, vector<long double>& inputLayer) {
  long double meanSquareErr = 0.0;
  long double deltaErr = 1000.0;
  long double countItrs = 0.0;
  long double countEpochs = 0.0;

	vector<vector<long double>> labels;
  vector<vector<long double>> inputs;
  string filename = "train_images.raw"; 

  // Initialize the labels and binary data from images
  readImage(filename, inputs, TRAINING_IMAGE_COUNT);
	initializeLabels(labels, "train_labels.txt");
  
  // Initialize all weights with random values
  initializeWeights(hidWeights);
  initializeWeights(outWeights);
  

  // Keep training as long as the change in error between meanSquareErr and square err of current iteration are above 0.0005% and while the number of epochs is less than 2
  while (abs(deltaErr) > CUTOFF_ERROR && countEpochs < 2.0) {
    if (countItrs >= TRAINING_IMAGE_COUNT) {
      countItrs = 0;
      countEpochs++;
    }
    // Read the next image and initialize inputLayer with decimal pixel values
    inputLayer.clear();
    initializeInputs(inputs[(int)countItrs], inputLayer);
    // displayLayer(inputLayer);
    // displayLayer(outWeights);

    // Update neurons in hidden and output layers using new inputs
    updateNeurons(inputLayer, hidWeights, hiddenLayer, HIDDEN_BIAS);
    // displayLayer(hiddenLayer);
    cout << endl;
    updateNeurons(hiddenLayer, outWeights, outputLayer, OUT_BIAS);
    // displayLayer(outputLayer);

    // Back propagate the error
    backPropagate(outputLayer, outWeights, hiddenLayer, hidWeights, inputLayer, labels[(int)countItrs]);
    // displayLayer(outWeights);

    // Compute the square error for the output neurons for this image and then calculate the percent change in error from the meanSquareErr
    long double errSquare = squaredErr(labels[(int)countItrs], outputLayer);
    countItrs += 1.0;
    cout << countItrs << endl;
    if (meanSquareErr == 0.0) {
      meanSquareErr = errSquare;
    }
    else {
      long double totItrs = ((long double)TRAINING_IMAGE_COUNT * countEpochs) + countItrs;
      deltaErr = ((errSquare - meanSquareErr) / meanSquareErr) * 100.0;
      meanSquareErr = ((meanSquareErr * (totItrs - 1.0)) + errSquare) / totItrs;

    }
    cout << "The squared error is: " << errSquare << endl;
  }

  cout << endl;
  cout << "The network is fully trained" << endl;
  cout << "The final mean square error is: " << meanSquareErr << endl;
  cout << "The final delta error is: " << deltaErr << endl;
  cout << "Iterations completed: " << ((long double)TRAINING_IMAGE_COUNT * countEpochs) + countItrs << endl;
  cout << "Epochs completed: " << countEpochs << endl;

}

// Returns index of max number in vector, used to create confusion matrix
int max(const vector<long double>& vec) {
  long double m = 0.0;
  int mindex;
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] > m) { 
      m = vec[i];
      mindex = i;
    }
  }
  return mindex;
}

void testNetwork(vector<long double>& outputLayer, const vector<vector<long double>>& outWeights, vector<long double>& hiddenLayer, const vector<vector<long double>>& hidWeights, vector<long double>& inputLayer) {
  vector<vector<long double>> confusionMatrix(5, vector<long double>(5));
  vector<vector<long double>> labels; 
  vector<vector<long double>> inputs;
  string filename = "test_images.raw"; 
  long double countTests = 0.0;

  // Initialize labels vector and binary data from images
  readImage(filename, inputs, TESTING_IMAGE_COUNT);
	initializeLabels(labels, "test_labels.txt");

  // Test all images in test_images.raw
  while (countTests < TESTING_IMAGE_COUNT) {
    inputLayer.clear();

    initializeInputs(inputs[(int)countTests], inputLayer);
    updateNeurons(inputLayer, hidWeights, hiddenLayer, HIDDEN_BIAS);
    updateNeurons(hiddenLayer, outWeights, outputLayer, OUT_BIAS);

    // Add result to the confusion matrix after each image
    int outputIndex = max(outputLayer);
    int trueIndex = max(labels[(int)countTests]);
    confusionMatrix[trueIndex][outputIndex]++;
    countTests++;
  }
  cout << "Test complete" << endl;
  displayLayer(confusionMatrix);

  // Compute and output the accuracy of the network
  long double accuracy = 0.0; 
  for (size_t i = 0; i < confusionMatrix.size(); i++) {
    accuracy += (long double)confusionMatrix[i][i]; 
  }
  cout << "Accuracy of network: " << endl;
  cout << ((accuracy / TESTING_IMAGE_COUNT) * 100) << " % " << endl;

}

int main() {

  trainNetwork(outputLayer, outWeights, hiddenLayer, hidWeights, inputLayer);
  cout << endl;
  testNetwork(outputLayer, outWeights, hiddenLayer, hidWeights, inputLayer);

}