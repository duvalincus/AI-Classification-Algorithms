#include "Classifier.h"
using namespace std;

double Classifier::getEuclidianDistance() {
  double distance = 0;
  for (auto instance : data->_instances) {
    for(auto feature : instance->_features) {

    }
  }
  return distance;
}

void Classifier::Validator(std::vector<int> &features) {
  double tempFeature;

  for (auto instance : data->_instances) {
    std::vector<double> tempFeatureList = {};
    for (auto feature : features) {
      tempFeature = instance->_features[feature];
      tempFeatureList.push_back(tempFeature);
    }
  }
}