#include "Data.h"
#include <vector>
#include <algorithm>

class Classifier {
  public:
    Data* data = nullptr;
    void Train(std::vector<int> IDs) {
      std::vector<Instance* > temp = {};
      for (auto instance : data->_instances) {
        auto it = std::find(IDs.begin(), IDs.end(), instance->getID());
        if (it != IDs.end()) {
          temp.push_back(instance);
        }
      }
      data = new Data(temp, IDs.size());
    };
    double Test(Instance testInstance);
    double getEuclidianDistance();
    void Validator(std::vector<int>&);
    Classifier(Data* data);
};