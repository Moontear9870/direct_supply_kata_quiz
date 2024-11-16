#pragma once
#include <vector>
#include <string>

/**
* Holds the data from one trivia question, including all the answers and which one is correct.
*/
class Question
{
public:
	// The trivia question being asked
	std::wstring question;
	// All the answers for a trivia question
	std::vector<std::wstring> options;
	// The correct answer
	int correctAnswer;
};
