#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

class Instance {
  private:
    int _instanceID;
    double _classLabel;

  public:
    std::vector <double> _features;
    Instance(int instanceID, double classLabel, std::vector<double> &features) {
      _instanceID = instanceID;
      _classLabel = classLabel;
      _features = features;
    }

    int getID() {
      return _instanceID;
    }

    double getClass() {
      return _classLabel;
    }
};

class Data {
  public:
    int _numFeatures;
    std::vector<Instance*> _instances;

    Data(std::string filename, int numFeatures);
    Data(std::vector<Instance*> instances, int numFeatures) {
      _instances = instances;
      _numFeatures = numFeatures;
      normalize();
    }
    
    void normalize();
};

