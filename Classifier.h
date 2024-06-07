#pragma once
#include "Data.h"
#include <vector>
#include <algorithm>

class Classifier {
  public:
    std::vector<Instance> data = {};
    std::vector<Instance> trainingData = {};
    void Train(std::vector<Instance> trainingInstances) {
      trainingData = trainingInstances;
    };
    double Test(const Instance &testInstance);
    double getEuclidianDistance(const Instance &x, const Instance &y);
    Classifier(std::vector<Instance> data) : data(data) {};
    Classifier() : data({}) {};
};

class Validator : public Classifier {
public:
  Validator(std::vector<Instance> data, std::vector<int> features) : Classifier(data) {
    for (size_t i = 0; i < data.size(); ++i)
    {
      std::vector<double> newFeatureList = {};
      for (size_t j = 0; j < features.size(); j++)
      {
        newFeatureList.push_back(data[i]._features[features[j] - 1]);
      }
      data[i]._features = newFeatureList;
    }
    this->data = data;
  }

  // using leave one out validation, check the accuracy of this specific featureset
  double evaluate();

};