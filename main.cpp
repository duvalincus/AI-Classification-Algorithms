#include <iostream>
#include <limits>
#include "Data.h"
#include "Classifier.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

int getValidNumber(int min, int max);

void loadData(std::vector<Instance* > &data, std::string filename, int numFeatures);

double randomPercentage() {
  int integerPart = rand() % 100; // Generate a random integer between 0 and 99
  int decimalPart = rand() % 100; // Generate a random integer between 0 and 99
  double percentage =
      integerPart +
      (double)decimalPart / 100; // Combine the integer and decimal parts
  return percentage;
}

int main() {
  int input, numFeatures;
  std::vector<Instance * > data = {};

  cout << "Welcome to CS170 Feature Selection Algorithm.\n";

  // cout << "Please enter total number of features:\n";
  // int number_of_features = getValidNumber(1, numeric_limits<int>::max());

  cout << "Select a dataset to test:" << endl;
  cout << "1 - Small Dataset" << endl;
  cout << "2 - Large Dataset" << endl;

  input = getValidNumber(1, 2);

  if (input == 1) {
    loadData(data, "test_data/small-test-dataset.txt", 10);
    numFeatures = 10;
  }
  else if (input == 2) {
    loadData(data, "test_data/large-test-dataset.txt", 40);
    numFeatures = 40;
  }

  cout << "Type the number of the algorithm you want to run.\n1. Forward Selection\n2. Backward Elimination\n";
  int algo_num = getValidNumber(1, 2);


  vector<int> num_features = {};     //feature counter

  for (int i = 1; i <= numFeatures; ++i) {
    num_features.push_back(i);
  }

  vector<double> current_percentage = {};                         //calculated percentage
  vector<int> explored_features = {};

  double max_percentage = 50.0; // Initialize max percentage
  vector<int> max_features = {};    // Initialize max features vector

  if (algo_num == 1) {
  srand(time(0)); // Use current time as seed for random generator


    while (!num_features.empty()) {
      current_percentage.clear();
      for (int i = 0; i < num_features.size(); i++) {
        // get vector with the features being looked at
        std::vector<int> current_features = max_features;
        current_features.push_back(num_features[i]);
        Validator validator(data, current_features);
        double percentage = validator.evaluate(data); // EVAL FUNCTION
        current_percentage.push_back(percentage);
        cout << "Using feature(s) {";

        for (int i = 0; i < explored_features.size(); ++i) {
          cout << explored_features[i];
          if (i != explored_features.size() - 1) {
            cout << ", ";
          }
        }
        if (!explored_features.empty()) {
          cout << ", ";
        }

        cout << num_features[i] << "} accuracy is " << percentage << "%"
             << endl;
      }
      // Calculate the best percentage
      auto maxElementIter =
          max_element(current_percentage.begin(), current_percentage.end());
      int position = distance(current_percentage.begin(), maxElementIter);
      if (explored_features.empty()) {
        cout << "Beginning search.\n";
      }

      // If there is not a new max percentage, stop the loop
      if (*maxElementIter <= max_percentage) {
        cout << "No new max percentage found. Stopping search.\n";
        cout << "Max percentage: " << max_percentage << "%\n";
        cout << "Max percentage was achieved with the following features: {";
        for (int i = 0; i < max_features.size(); ++i) {
          cout << max_features[i];
          if (i != max_features.size() - 1) {
            cout << ", ";
          }
        }
        cout << "}\n";
        break;
      }

      // Update max percentage and max features
      max_percentage = *maxElementIter;
      max_features = explored_features;
      max_features.push_back(num_features[position]);

      // Move the best feature to explored_features and remove it from
      // num_features
      explored_features.push_back(num_features[position]);
      num_features.erase(num_features.begin() + position);

      cout << "Feature set {";

      for (int i = 0; i < explored_features.size(); ++i) {
        cout << explored_features[i];
        if (i != explored_features.size() - 1) {
          cout << ", ";
        }
      }

      cout << "} was best, accuracy is " << current_percentage[position] << "%"
           << endl;
    }
  }
    if (algo_num == 2) {
    while (!num_features.empty()) {
        current_percentage.clear();
        vector<int> current_features = num_features;
        for (int i = 0; i < num_features.size(); i++) {
            current_features.erase(current_features.begin() + i);
            double percentage = randomPercentage(); // EVAL FUNCTION
            current_percentage.push_back(percentage);
            cout << "Using feature(s) {";
            for (int j = 0; j < current_features.size(); ++j) {
                cout << current_features[j];
                if (j != current_features.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "} accuracy is " << percentage << "%" << endl;
            current_features = num_features; // Reset the features for the next iteration
        }
        // Calculate the best percentage
        auto maxElementIter = max_element(current_percentage.begin(), current_percentage.end());
        int position = distance(current_percentage.begin(), maxElementIter);
        if (explored_features.empty()) {
            cout << "Beginning search.\n";
        }
        // If there is not a new max percentage, stop the loop
        if (*maxElementIter <= max_percentage) {
            cout << "No new max percentage found. Stopping search.\n";
            cout << "Max percentage: " << max_percentage << "%\n";
            cout << "Max percentage was achieved with the following features: {";
            for (int i = 0; i < max_features.size(); ++i) {
                cout << max_features[i];
                if (i != max_features.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "}\n";
            break;
        }
        // Update max percentage and max features
        max_percentage = *maxElementIter;
        max_features = num_features;
        max_features.erase(max_features.begin() + position);
        // Remove the feature with the worst impact on accuracy
        num_features.erase(num_features.begin() + position);
        cout << "Feature set {";
        for (int i = 0; i < num_features.size(); ++i) {
            cout << num_features[i];
            if (i != num_features.size() - 1) {
                cout << ", ";
            }
        }
        cout << "} was best, accuracy is " << current_percentage[position] << "%" << endl;
    }
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