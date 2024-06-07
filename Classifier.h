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
    Classifier() : data({}) {};
};

class Validator : public Classifier {
public:
  Validator(std::vector<Instance *> &data, std::vector<int> &features) : Classifier(data) {
    std::vector<Instance *> tempData = data;
    for (auto instance : tempData)
    {
      std::vector<double> newFeatureList = {};
      for (auto feature : features)
      {
        newFeatureList.push_back(instance->_features[feature - 1]);
      }
      instance->_features = newFeatureList;
    }
    this->data = tempData;
  }

  // using leave one out validation, check the accuracy of this specific featureset
  double evaluate(std::vector<Instance*> &data) {
    double correctCount = 0;
    double numInstances = data.size();

    for (int i = 0; i < numInstances; i++) {
      std::vector<Instance*> trainingData = data;
      trainingData.erase(trainingData.begin() + i);
      Train(trainingData);
      correctCount += (data[i]->getClass() == Test(*data[i])); 
    }
    return (correctCount / numInstances) * 100;
  }

};