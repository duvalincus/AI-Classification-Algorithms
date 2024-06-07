#pragma once
#include "Data.h"
#include "Classifier.h"
using namespace std;

std::vector<int> forwardSelection(std::vector<Instance> data, int numFeatures, std::vector<int> features);
std::vector<int> backwardSelection(std::vector<Instance> data, int numFeatures, std::vector<int> features);