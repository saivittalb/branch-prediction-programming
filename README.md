# Branch Prediction Programming
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![PR's Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat)](http://makeapullrequest.com) 
[![GitHub followers](https://img.shields.io/github/followers/saivittalb.svg?style=social&label=Follow)](https://github.com/saivittalb?tab=followers) 
[![Twitter Follow](https://img.shields.io/twitter/follow/saivittalb.svg?style=social)](https://twitter.com/saivittalb) 

Implementation of several Branch Prediction algorithms and analysis on their effectiveness on real-world program traces.

The following algorithms were implemented:

- **Static ALWAYS TAKEN Branch Predictor (Static-T)**: All branches are predicted to be taken
- **Static ALWAYS NOT TAKEN Branch Predictor (Static-NT)**: All branches are predicted to be not taken.
- **Dynamic BIMODAL Branch Predictor (Dynamic-BM)**: The simplest dynamic branch direction predictor is an array of 2^n two-bit saturating counters. 
- **Dynamic BIMODAL Branch Predictor with Global Branch History (Dynamic-GSHARE)**: A more advanced dynamic branch predictor that uses the history of recently executed branches to predict the next branch.
- **Dynamic NEURAL NETWORK using Perceptrons (Dynamic-NN)**: An adaptive neural network that contains dynamic predictor which uses a list of perceptrons to perform branch predictions. This designed unique algorithm can work on any hardware and trace.

Developed as a part of an assignment for the course EE 318 – Computer Architecture and Design.

###### Note 
Developed with C++ and Python 3.9.2.
Editor used was Visual Studio Code 1.55.1.

## Table of contents

* [License](#license)
* [Setup](#setup)
  * [Traces](#traces)
  * [Static and Dynamic predictors (except Dynamic Neural Network)](#static-and-dynamic-predictors-except-Dynamic-Neural-network)
  * [Dynamic Neural Network](#dynamic-neural-network)
* [Results](#results)
    * [Static-T](#static-t)
    * [Static-NT](#static-nt)
    * [Dynamic-BM](#dynamic-bm)
    * [Dynamic-GSHARE](#dynamic-gshare)
    * [Dynamic-NN](#dynamic-nn)
* [Contributing](#contributing)

## License
This project is licensed under the MIT License, a short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications and larger works may be distributed under different terms and without source code.

<p align="center"> Copyright (c) 2021 Sai Vittal B. All rights reserved.</p>

## Setup

### Traces
Traces used are available via a compressed file named ```traces.7z```. Download this repo and unzip the file to get access to 16 unique traces.

### Static and Dynamic predictors (except Dynamic Neural Network)
- Run the following commands in terminal/console window:
```bash
$ cd <your-predictor-folder>
$ make
$ ./predictor <InputFilename> <OutputFilename>
```

```InputFilename``` is the path to your input trace file containing branch outcomes in the following format: address 1/0 (1 = taken, 0 = not taken).
```OutputFilename``` is the file where the result is printed to.

### Dynamic Neural Network
- Install Python 3.9.2 (preferred).
- Run the following command in terminal/console window:
```bash
$ python AdaptivePredictor.py
```
- The above would return the following statement where you are required to provide the input filepath:
```bash
Provide the filepath for the trace (along with quotes " "): "<input-file-path-here>"
```

## Results

Results can viewed in the ```results``` file in each predictor folder. It contains the accuracy of that predictor in a line-by-line fashion for the 16 traces.

#### Comparison in decreasing reliablity: Dynamic-NN >> Dynamic-GSHARE > Dynamic-BM >> Static-T >= Static-NT

Results are also showcased in the MS Word document named ```Branch Prediction Programming Report.docx```.

The output formats in the ```results``` file for each predictor are explained below.

### Static-T
Direct accuracy reported in single value for a trace. 

### Static-NT
Direct accuracy reported in single value for a trace.

### Dynamic-BM
Direct accuracy reported with 7 different table size (8, 16, 32, 128, 256, 512, and 1024 entries) for a trace.

### Dynamic-GSHARE
Direct accuracy reported with 9 different global register size range from 2 bits to 10 bits for a table size of 1024 entries for a trace.

### Dynamic-NN
Direct accuracy reported in a single value when the number of unique addresses are unknown for a trace. If the number of unique addresses are known for a trace, then a commented out function in the code file ```AdaptivePredictor.py``` can be used to achieve accuracy in that scenario.

## Contributing
- Fork this project by clicking the ```Fork``` button on top right corner of this page.
- Open terminal/console window. 
- Clone the repository by running following command in git:
 ```bash
$ git clone https://github.com/[YOUR-USERNAME]/branch-prediction-programming.git
```
- Add all changes by running this command.
```bash
$ git add .
```
- Or to add specific files only, run this command.
```bash
$ git add path/to/your/file
```
- Commit changes by running these commands.
```bash
$ git commit -m "DESCRIBE YOUR CHANGES HERE"

$ git push origin
```
- Create a Pull Request by clicking the ```New pull request``` button on your repository page.

[![ForTheBadge built-with-love](http://ForTheBadge.com/images/badges/built-with-love.svg)](https://GitHub.com/saivittalb/) 
[![ForTheBadge powered-by-electricity](http://ForTheBadge.com/images/badges/powered-by-electricity.svg)](http://ForTheBadge.com)

<p align="center"> Copyright (c) 2021 Sai Vittal B. All rights reserved.</p>
<p align="center"> Made with ❤ by <a href="https://github.com/saivittalb">Sai Vittal B</a></p>
