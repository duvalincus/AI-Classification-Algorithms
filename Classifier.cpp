#include "Classifier.h"
using namespace std;

// tests test instance against the trained data
double Classifier::Test(const Instance &test) {
  double distance, closestClass;
  double minDistance = 1000;
  
  for (size_t i = 0; i < trainingData.size(); ++i) {
    
    distance = getEuclidianDistance(trainingData[i], test);
    if (distance < minDistance) {
      minDistance = distance;
      closestClass = trainingData[i].getClass();
    }
  }
  return closestClass;
}

double Classifier::getEuclidianDistance(const Instance &x, const Instance &y) {
  double sum = 0.0;
  for (size_t i = 0; i < x._features.size(); ++i)
  {
    sum += pow(x._features[i] - y._features[i], 2);
  }
  return sqrt(sum);
}

double Validator::evaluate() {
  double correctCount = 0;
  double numInstances = data.size();

  for (size_t i = 0; i < numInstances; ++i)
  {
    std::vector<Instance> trainingData(data);
    trainingData.erase(trainingData.begin() + i);
    Train(trainingData);
    correctCount += (data[i].getClass() == Test(data[i]));
  }
  return (correctCount / numInstances) * 100;
}