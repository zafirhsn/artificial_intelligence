# Neural Network
A 2 layer Fully-connected perceptron for recognizing handwritten digits from 0 to 4. The network is trained using back-propagation
with stochastic gradient descent. The goal was not only to train the network to recognize handwritten digits, but to experiment with
various parameters of the network to determine which combination of parameters produced the most accurate network. The results of that
experimentation are represented in the tables below.

## To Compile and Run
1.	Download MinGW from https://osdn.net/projects/mingw/releases/
2.	Install the mingw32-gcc-g++-bin (version 6.3.0-1) from the MinGW installation manager
3.	Add C:\MinGW\bin to PATH environment variable
4.  Download repo as zip file and unzip repo where ever you'd like on your machine
5.	Open terminal and **cd into directory** where main.cpp lives
6.  Make sure **test_images.raw**, **test_labels.txt**, **train_images.raw**, and **train_labels.txt** are in the same directory as main.cpp

Type in following commands in terminal<br/>
`$ g++ -g main.cpp -o main.exe` <br/><br/>
`$ main` <br/>

If you encounter an error compiling the program, try this command <br/>
`$ g++ -std=c++11 main.cpp -o main.exe`<br/><br/>
`$ main`

## Confusion Matrices
The following tables represent the test results of the network for various parameters. The top row of each table represents the output class
of the image determined by the network. The left-most column represents the true class that the image belongs to. For example, if the 
network determines that an image is the number '3', but the image is actually that of a '4', the cell in the '4' row and '3' column
would increase by 1. A correctly classified image would therefore be in the same number column as row. In Test 1, we can see that the
network correctly identified 456 '0's, but also incorrectly determined 2 '0's to be '1's, and 2 '0's to be '3's. There are **2561** test
images in total. 


### Test 1
Learning Rate: 0.001  
Number of Hidden Layer Neurons: 100

|         | '0'     | '1'    | '2'  | '3'   | '4'   |
| ------- |:-------:| :-----:|:----:|:-----:|:-----:|
| **'0'** | 456 | 0  | 2 | 2 | 0 | 
| **'1'** | 0   |  563  | 3 | 4 | 1 | 
| **'2'** | 5   |    2  | 491 | 21 | 11 |
| **'3'** | 3   |    1  | 16 | 479 | 1 | 
| **'4'** | 1   |    4  | 10 | 1 | 484 | 

Accuracy = ((456 + 563 + 491 + 479 + 484) / 2561) * 100 = **96.5638%**
<br/> 
<br/>

## Test 2  
Learning Rate: 0.01  
Number of Hidden Layer Neurons: 100

|         | '0'     | '1'    | '2'  | '3'   | '4'   |
| ------- |:-------:| :-----:|:----:|:-----:|:-----:|
| **'0'** | 431 | 0  | 6 | 20 | 3 | 
| **'1'** | 0  |  560  | 3 | 8 | 0 | 
| **'2'** | 9   |  12  | 432 | 59 | 18 |
| **'3'** | 6   |  4  | 14 | 465 | 11 | 
| **'4'** | 1   |  3  | 8 | 4 | 484 |

Accuracy: ((431 + 560 + 432 + 465 + 484) / 2561) * 100 = **92.6201%**

<br/>
<br/>


## Test 3  
Learning Rate: 0.01  
Number of Hidden Layer Neurons: 50

|         | '0'     | '1'    | '2'  | '3'   | '4'   |
| ------- |:-------:| :-----:|:----:|:-----:|:-----:|
| **'0'** | 395 | 0  | 50 | 10 | 5 | 
| **'1'** | 0  |  555  | 8 | 1 | 7 | 
| **'2'** | 12   |  20  | 430 | 36 | 32 |
| **'3'** | 1  |  17  | 31 | 437 | 14 | 
| **'4'** | 4   |  16  | 24 | 15 | 441 |

Accuracy: ((395 + 555 + 430 + 437 + 441) / 2561) * 100 = **88.1687%**

<br/>
<br/>


## Test 4  
Learning Rate: 0.01  
Number of Hidden Layer Neurons: 300

|         | '0'     | '1'    | '2'  | '3'   | '4'   |
| ------- |:-------:| :-----:|:----:|:-----:|:-----:|
| **'0'** | 456 | 0  | 0 | 2 | 2 | 
| **'1'** | 0  |  564  | 2 | 4 | 1 | 
| **'2'** | 8   |  8  | 459 | 38 | 17 |
| **'3'** | 3  |  2  | 12 | 478 | 5 | 
| **'4'** | 1 |  2  | 2 | 2 | 493 |

Accuracy: ((456 + 564 + 459 + 478 + 493) / 2561) * 100 = **95.6658%**


