#pragma once
#include "Data.h"
#include <vector>
#include <algorithm>

class Classifier {
  public:
    std::vector<Instance*> data = {};
    void Train(std::vector<Instance*> & trainingInstances) {
      
      data = trainingInstances;

    };
    double Test(Instance testInstance);
    Classifier(std::vector<Instance*> &data) : data(data) {};
};

class Validator {
public:
  Validator(std::vector<Instance *> &data, std::vector<int> &features) {

    for (auto instance : data)
    {
      std::vector<double> newFeatureList = {};
      for (auto feature : features)
      {
        newFeatureList.push_back(instance->_features[feature]);
      }
      instance->_features = newFeatureList;
    }
  }

  // using leave one out validation, check the accuracy of this specific featureset
  double evaluate(std::vector<Instance*> &data, Classifier classifier) {
    int correctCount = 0;
    for (int i = 0; i < data.size(); i++) {
      std::vector<Instance*> trainingData = data;
      trainingData.erase(trainingData.begin() + i);
      classifier.Train(trainingData);
      correctCount += (data[i]->getClass() == classifier.Test(*data[i])); 
      
    }
    return correctCount / data.size();
  }
};