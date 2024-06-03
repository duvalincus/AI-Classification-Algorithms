#include <cstdlib>
#include <vector>

std::vector<int> backwardSelection(std::vector<int> featureList, std::vector<int> current)
{
	std::vector<int> optimal, trial;
	optimal = featureList;
	for (int i = 0; i < featureList.size(); i++)
	{
		trial = current;
		// add new feature
		trial.push_back(i);
		if (trial.at(0) > 1)
			optimal = trial;
		backwardSelection(featureList, optimal);
	}
	return optimal;
}

std::vector<int> forwardsSelection(std::vector<int> featureList) {
	return {};
}

// stub
double evaluate(std::vector<int> t)
{
	return rand() % 1 / 1.5;
}