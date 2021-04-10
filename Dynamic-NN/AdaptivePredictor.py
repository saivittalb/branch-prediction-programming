"""
 * EE 318 - Computer Architecture and Design
 * Assignment 1 - Branch Prediction Programming 
 *
 * @code `Dynamic-NN` (Dynamic Adaptive Neural Network using Perceptrons)
 * @author Sai Vittal B
 * @copyright 2021
 * MIT License
"""
 
import sys
import os
from collections import deque
import time

class Perceptron:
    weights = []
    N = 0
    bias = 0
    threshold = 0

    def __init__(self, N):
        self.N = N
        self.bias = 0
        self.threshold = 2 * N + 14                 # optimal threshold depends on history length
        self.weights = [0] * N

    def predict(self, global_branch_history):
        running_sum = self.bias
        for i in range(0, self.N):                  # dot product of branch history with the weights
            running_sum += global_branch_history[i] * self.weights[i]
        prediction = -1 if running_sum < 0 else 1
        return (prediction, running_sum)

    def update(self, prediction, actual, global_branch_history, running_sum):
        if (prediction != actual) or (abs(running_sum) < self.threshold):
            self.bias = self.bias + (1 * actual)
            for i in range(0, self.N):
                self.weights[i] = self.weights[i] + (actual * global_branch_history[i])


def perceptron_pred(trace, l=1, tablesize=None):
    global_branch_history = deque([])
    global_branch_history.extend([0] * l)

    p_list = {}
    num_correct = 0

    for br in trace:                                # iterating through each branch
        if tablesize:
            index = hash(br[0]) % tablesize
        else:
            index = hash(br[0])

        if index not in p_list:                     # if no previous branch from this memory location
            p_list[index] = Perceptron(l)
        results = p_list[index].predict(global_branch_history)
        pr = results[0]
        running_sum = results[1]
        actual_value = 1 if br[1] else -1
        p_list[index].update(pr, actual_value, global_branch_history, running_sum)
        global_branch_history.appendleft(actual_value)
        global_branch_history.pop()
        if pr == actual_value:
            num_correct += 1
    return num_correct, len(p_list)

def getTableSize(ratio,k):
    return int(ratio * k)

fileIn = str(input('Provide the filepath for the trace (along with quotes " "): '))
assert os.path.exists(fileIn), 'ERROR: The input file does not exist.'
with open(fileIn, 'r') as branchfile:
    trace = []
    for line in branchfile.readlines():
        tok = line.split(' ')
        trace.append([tok[0], int(tok[1])])

num_correct, num_p = perceptron_pred(trace, 5)
print('\nLength of Perceptrons list: ' + str(num_p) + '\n') 

# Used if the number of unique addresses are not known
results = []
for i in range (1, 50):
    start_time = time.time()
    num_correct, num_p = perceptron_pred(trace, i)
    end_time = time.time()
    results.append((num_correct/float(len(trace)), end_time - start_time))
    print('i:' + str(i) + ' --> ')
    print(results[-1])
print('\nAccuracy: ' + str(num_correct/float(len(trace))*100) + '\n')
fileOut = open('results', 'a')
fileOut.write(str(num_correct/float(len(trace))*100) + '\n')
fileOut.close()

# Used if the number of unique addresses are known
""" ratios = [i*.033 for i in range(1, 31)]
results = []
for ratio in ratios:
    uniqueAddr = 33     # define number of unique addresses
    tablesize = getTableSize(ratio, uniqueAddr)
    start_time = time.time()
    num_correct, num_p = perceptron_pred(trace, 5, tablesize=tablesize)
    end_time = time.time()
    results.append((num_correct/float(len(trace)), end_time - start_time, ratio, tablesize))
    print('ratio:' + str(ratio) + ' --> ')
    print(results[-1])
print('\nAccuracy: ' + str(num_correct/float(len(trace))*100) + '\n')
fileOut = open('results', 'a')
fileOut.write(str(num_correct/float(len(trace))*100) + '\n')
fileOut.close() """
