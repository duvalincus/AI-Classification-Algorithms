#include "Classifier.h"
using namespace std;

double Classifier::Test(Instance test) {
  double distance, closestClass;
  double minDistance = std::numeric_limits<double>::max();
  
  for (auto instance : data) {
    double sum = 0;
    for(int i = 0; i < test._features.size(); i++) {
      sum += pow(test._features[i] - instance->_features[i], 2); 
    }
    distance = sqrt(sum);
    if (distance < minDistance) {
      minDistance = distance;
      closestClass = instance->getClass();
    }
  }
  return closestClass;
}

