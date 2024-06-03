#include "Data.h"

void Data::normalize() {
  double average, stdev;

  //calculate average
  for (int i = 0; i < _numFeatures; i++) {
    double sum = 0.0;
    for (auto instance : _instances) {
      sum += instance->_features[i];
    }
    average = sum / static_cast<double>(_instances.size());
    sum = 0.0;
    for (auto instance : _instances) {
      sum += pow((instance->_features[i] - average), 2);
    }
    stdev = sqrt(sum / static_cast<double>(_instances.size()));

    // std::cout << "For feature " << i << " stdev is: " << stdev << std::endl;

    for (auto instance: _instances) {
      double old = instance->_features[i];
      instance->_features[i] = (old - average) / stdev;
    }
  }
  
  std::cout << "Data normalized." << std::endl;
}