#include "Data.h"
#include <vector>
#include <algorithm>

class Classifier {
  public:
    std::vector<Instance*> data = {};
    void Train(std::vector<int> IDs) {
      std::vector<Instance* > temp = {};
      for (auto instance : data) {
        auto it = std::find(IDs.begin(), IDs.end(), instance->getID());
        if (it != IDs.end()) {
          temp.push_back(instance);
        }
      }
      data = temp;
    };
    double Test(Instance testInstance);
    double getEuclidianDistance(Instance testInstance);
    Classifier(std::vector<Instance*> data) : data(data) {};
};

class Validator {
public:
  Validator(std::vector<Instance *> data, std::vector<int> features) {

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
  double checkAccuracy(std::vector<Instance*> data, Classifier classifier) {
    for (auto testInstance : data) {
      for (auto instance : data) {
        if (instance == testInstance) {
          continue;
        }
        else {
          
        }
      }
    }
  }
};