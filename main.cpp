#include <iostream>
#include <limits>

using namespace std;

int getValidNumber(int min, int max) {
  int num = 0;
  while (true) {
    cin >> num;

    if (cin.fail() || num < min || num > max) {
      cout << "Invalid input, please enter a number between " << min << " and " << max << ".\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      break;
    }
  }
  return num;
}

int main() {
  cout << "Welcome to CS170 Feature Selection Algorithm.\n";

  cout << "Please enter total number of features:\n";
  int number_of_features = getValidNumber(1, numeric_limits<int>::max());

  cout << "Type the number of the algorithm you want to run.\n 1. Forward Selection\n 2. Backward Elimination\n 3. Bertie’s Special Algorithm.\n";
  int algo_num = getValidNumber(1, 3);

cout <<"Number of Features: " <<number_of_features <<" Type of Algorithm: " <<algo_num <<endl;
  
  return 0;
}
