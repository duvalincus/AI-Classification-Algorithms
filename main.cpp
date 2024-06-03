#include <iostream>
#include <limits>
#include "Data.h"
#include "Classifier.h"

using namespace std;

int getValidNumber(int min, int max);

void loadData(std::vector<Instance *> &);

int main() {
  int input, numFeatures;
  std::vector<Instance * > data = {};

  cout << "Welcome to CS170 Feature Selection Algorithm.\n";

  // cout << "Please enter total number of features:\n";
  // int number_of_features = getValidNumber(1, numeric_limits<int>::max());

  cout << "Select a dataset to test:" << endl;
  cout << "1 - Small Dataset" << endl;
  cout << "2 - Large Dataset" << endl;

  input = getValidNumber(1, 1000);

  if (input == 1) {
    loadData(data, "test_data/small-test-dataset.txt", 10);
  }
  else if (input == 2) {
    loadData(data, "test_data/large-test-dataset.txt", 40);
  }

  cout << "Type the number of the algorithm you want to run.\n1. Forward Selection\n2. Backward Elimination\n3. Our Special Algorithm.\n";
  int algo_num = getValidNumber(1, 3);

  if (algo_num == 1) {
    Classifier forwardSelection(data);
    Validator validate(data, {3,5,7});
    validate.evaluate();
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

      Instance *addData = new Instance(instanceID, classLabel, featureList);
      data.push_back(addData);
      featureList = {};
    }
  }
  else
  {
    std::cout << "Error opening file." << std::endl;
    return;
  }
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