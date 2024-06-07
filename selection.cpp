#include "selection.h"

std::vector<int> forwardSelection(std::vector<Instance> inputData, int numFeatures, std::vector<int> features) {
  vector<double> current_percentage = {}; // calculated percentage
  vector<int> explored_features = {};

  double max_percentage = 50.0;  // Initialize max percentage
  vector<int> max_features = {}; // Initialize max features vector

  while (!features.empty())
  {
    current_percentage.clear();
    for (int i = 0; i < features.size(); i++)
    {
      // get vector with the features being looked at
      vector<int> current_features = max_features;
      current_features.push_back(features[i]);
      Validator validator(inputData, current_features);
      double percentage = validator.evaluate(); // EVAL FUNCTION
      current_percentage.push_back(percentage);
      cout << "Using feature(s) {";

      for (int i = 0; i < explored_features.size(); ++i)
      {
        cout << explored_features[i];
        if (i != explored_features.size() - 1)
        {
          cout << ", ";
        }
      }
      if (!explored_features.empty())
      {
        cout << ", ";
      }

      cout << features[i] << "} accuracy is " << percentage << "%"
           << endl;
    }
    // Calculate the best percentage
    auto maxElementIter =
        max_element(current_percentage.begin(), current_percentage.end());
    int position = distance(current_percentage.begin(), maxElementIter);
    if (explored_features.empty())
    {
      cout << "Beginning search.\n";
    }

    // If there is not a new max percentage, stop the loop
    if (*maxElementIter <= max_percentage)
    {
      cout << "No new max percentage found. Stopping search.\n";
      cout << "Max percentage: " << max_percentage << "%\n";
      cout << "Max percentage was achieved with the following features: {";
      for (int i = 0; i < max_features.size(); ++i)
      {
        cout << max_features[i];
        if (i != max_features.size() - 1)
        {
          cout << ", ";
        }
      }
      cout << "}\n";
      break;
    }

    // Update max percentage and max features
    max_percentage = *maxElementIter;
    max_features = explored_features;
    max_features.push_back(features[position]);

    // Move the best feature to explored_features and remove it from
    // features
    explored_features.push_back(features[position]);
    features.erase(features.begin() + position);

    cout << "Feature set {";

    for (int i = 0; i < explored_features.size(); ++i)
    {
      cout << explored_features[i];
      if (i != explored_features.size() - 1)
      {
        cout << ", ";
      }
    }

    cout << "} was best, accuracy is " << current_percentage[position] << "%"
         << endl;
  }
  return max_features;
}

std::vector<int> backwardSelection(std::vector<Instance> inputData, int numFeatures, std::vector<int> features) {

  vector<double> current_percentage = {}; // calculated percentage
  vector<int> explored_features = {};

  double max_percentage = 50.0;  // Initialize max percentage
  vector<int> max_features = {}; // Initialize max features vector

  while (!features.empty())
  {
    current_percentage.clear();
    vector<int> current_features = features;
    for (int i = 0; i < features.size(); i++)
    {
      current_features.erase(current_features.begin() + i);
      Validator validator(inputData, current_features);
      double percentage = validator.evaluate(); // EVAL FUNCTION
      current_percentage.push_back(percentage);
      cout << "Using feature(s) {";
      for (int j = 0; j < current_features.size(); ++j)
      {
        cout << current_features[j];
        if (j != current_features.size() - 1)
        {
          cout << ", ";
        }
      }
      cout << "} accuracy is " << percentage << "%" << endl;
      current_features = features; // Reset the features for the next iteration
    }
    // Calculate the best percentage
    auto maxElementIter = max_element(current_percentage.begin(), current_percentage.end());
    int position = distance(current_percentage.begin(), maxElementIter);
    if (explored_features.empty())
    {
      cout << "Beginning search.\n";
    }
    // If there is not a new max percentage, stop the loop
    if (*maxElementIter <= max_percentage)
    {
      cout << "No new max percentage found. Stopping search.\n";
      cout << "Max percentage: " << max_percentage << "%\n";
      cout << "Max percentage was achieved with the following features: {";
      for (int i = 0; i < max_features.size(); ++i)
      {
        cout << max_features[i];
        if (i != max_features.size() - 1)
        {
          cout << ", ";
        }
      }
      cout << "}\n";
      break;
    }
    // Update max percentage and max features
    max_percentage = *maxElementIter;
    max_features = features;
    max_features.erase(max_features.begin() + position);
    // Remove the feature with the worst impact on accuracy
    features.erase(features.begin() + position);
    cout << "Feature set {";
    for (int i = 0; i < features.size(); ++i)
    {
      cout << features[i];
      if (i != features.size() - 1)
      {
        cout << ", ";
      }
    }
    cout << "} was best, accuracy is " << current_percentage[position] << "%" << endl;
  }
  return max_features;
}