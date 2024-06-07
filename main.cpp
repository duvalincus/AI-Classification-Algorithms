#include "Data.h"
#include "Classifier.h"
#include "selection.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

int getValidNumber(int min, int max);
void loadData(std::vector<Instance* > &data, std::string filename, int numFeatures);
int getChoices(std::vector<Instance *> &data, int &numFeatures);

int main() {
  int input, numFeatures;
  std::vector<Instance * > data = {};

  input = getChoices(data, numFeatures);

  vector<int> features = {};     //feature set

  for (int i = 1; i <= numFeatures; ++i) {
    features.push_back(i);
  }

  if (input == 1) {
    // std::vector<int> testFeatures = {1};
    // Validator test(data, testFeatures);
    // test.evaluate(data);

    // testFeatures = {5};
    // Validator test2(data, testFeatures);
    // test2.evaluate(data);
    forwardSelection(data, numFeatures, features);
  }
    
  if (input == 2) {
    backwardSelection(data, numFeatures, features);
  }

  return 0;
}

void loadData(std::vector<Instance* > &data, std::string filename, int numFeatures) {
  std::ifstream inFile;
  inFile.open(filename);
  int instanceID = 0;
  std::vector<double> featureList;
  double classLabel, feature;

  if (inFile.is_open())
  {

    std::string streamString;

    while (getline(inFile, streamString))
    {
      std::stringstream inputStream(streamString);
      inputStream >> classLabel;

      for (int i = 0; i < numFeatures; i++)
      {
        inputStream >> feature;
        featureList.push_back(feature);
      }

      Instance *addData = new Instance(++instanceID, classLabel, featureList);
      data.push_back(addData);
      featureList = {};
    }
  }
  else
  {
    std::cout << "Error opening file." << std::endl;
    return;
  }
  double average, stdev;

  // calculate average
  for (int i = 0; i < numFeatures; i++)
  {
    double sum = 0.0;
    for (auto instance : data)
    {
      sum += instance->_features[i];
    }
    average = sum / static_cast<double>(data.size());
    sum = 0.0;
    for (auto instance : data)
    {
      sum += pow((instance->_features[i] - average), 2);
    }
    stdev = sqrt(sum / static_cast<double>(data.size()));

    // std::cout << "For feature " << i << " stdev is: " << stdev << std::endl;

    for (auto instance : data)
    {
      instance->_features[i] = (instance->_features[i] - average) / stdev;
    }
  }

  std::cout << "Data normalized." << std::endl;
}

int getValidNumber(int min, int max) {
  int num = 0;
  while (true)
  {
    cin >> num;

    if (cin.fail() || num < min || num > max)
    {
      cout << "Invalid input, please enter a number between " << min << " and " << max << ".\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
      break;
    }
  }
  return num;
}

int getChoices(std::vector<Instance*> &data, int &numFeatures) {
  cout << "Welcome to CS170 Feature Selection Algorithm.\n";

  // cout << "Please enter total number of features:\n";
  // int number_of_features = getValidNumber(1, numeric_limits<int>::max());

  cout << "Select a dataset to test:" << endl;
  cout << "1 - Small Dataset" << endl;
  cout << "2 - Large Dataset" << endl;

  int input = getValidNumber(1, 2);

  if (input == 1)
  {
    loadData(data, "test_data/small-test-dataset.txt", 10);
    numFeatures = 10;
  }
  else if (input == 2)
  {
    loadData(data, "test_data/large-test-dataset.txt", 40);
    numFeatures = 40;
  }

  cout << "Type the number of the algorithm you want to run.\n1. Forward Selection\n2. Backward Elimination\n";
  int algo_num = getValidNumber(1, 2);

  return algo_num;
}