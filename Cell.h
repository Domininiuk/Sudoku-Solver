#pragma once
#include <vector>
class Cell
{
public:
	// Constructors
	Cell();
	Cell(const int p_value, const bool p_given);

	// Getters

	int getValue() const;
	bool isGiven() const;
	int getCandListSize() const;
	int getCandidateAt(int index) const;
	bool isCandidate(int candidate);
	std::vector<int> getCandidateList();


	// Setters
	void setValue(int p_value);
	void setGiven(bool p_given);
	void addCandidate(int p_candidate);
	void clearCandidateList();
	void removeCandidate(int p_candidate);
private:
	// Member variables
	int m_value;
	bool m_given;
	std::vector<int> m_candidateList;
};

