#include "Cell.h"

Cell::Cell()
{
	m_value = 0;
	m_given = false;

	// Generate candidate list
	for (int i = 1; i <= 9; i++)
	{
		m_candidateList.push_back(i);
	}
}

Cell::Cell(const int p_value, const bool p_given)
{
	m_value = p_value;
	m_given = p_given;

	if (p_given != true)
	{
		// Generate candidate list
		for (int i = 1; i <= 9; i++)
		{
			m_candidateList.push_back(i);
		}
	}
}

int Cell::getValue() const
{
	return m_value;
}

bool Cell::isGiven() const
{
	return m_given;
}

int Cell::getCandListSize() const
{
	return m_candidateList.size();
}

int Cell::getCandidateAt(int index) const
{
	return m_candidateList[index];
}

bool Cell::isCandidate(int candidate)
{
	return std::find(m_candidateList.begin(), m_candidateList.end(), candidate) != m_candidateList.end();
}

std::vector<int> Cell::getCandidateList()
{
	return m_candidateList;
}

void Cell::setValue(int p_value)
{
	m_value = p_value;
}

void Cell::setGiven(bool p_given)
{
	m_given = p_given;
}

void Cell::addCandidate(int p_candidate)
{
	m_candidateList.push_back(p_candidate);
}

void Cell::clearCandidateList()
{
	m_candidateList.clear();
}

void Cell::removeCandidate(int p_candidate)
{
	// Remove the candidate from the list
	for (size_t i = 0; i < m_candidateList.size(); ++i)
	{
		if (m_candidateList[i] == p_candidate) 
		{
			m_candidateList.erase(m_candidateList.begin() + i);
		}
	}
}
