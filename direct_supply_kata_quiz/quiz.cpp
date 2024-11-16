#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <curl/curl.h>
#include <cwchar>
#include "quiz.hpp"

// The portion of the api that is always the same, regardless of category
std::string quizString = "https://opentdb.com/api.php?amount=10&category=";

struct memory {
	char* response;
	size_t size;
};

struct memory chunk = { nullptr, 0 };

std::vector<Question*> Quiz::questions = { new Question(), new Question(), new Question(),
											new Question(), new Question(), new Question(),
											new Question(), new Question(), new Question(), new Question(), };

size_t Quiz::readQuiz(char* data, size_t size, size_t nmemb, void* readData)
{
	// The following block of code is from libcurl's API, specifically the page on the CURLOPT_WRITEFUNCTION explained page
	size_t realsize = size * nmemb;
	struct memory* mem = (struct memory*)readData;

	//std::cout << "readData pointer: " << readData << std::endl;
	//std::cout << "size: " << size << std::endl;
	//std::cout << "nmemb: " << nmemb << std::endl;
	//std::cout << "mem->size: " << mem->size << std::endl;
	//std::cout << "readData size: " << sizeof(readData) << std::endl;
	//std::cout << "mem size: " << sizeof(mem) << std::endl;
	//std::cout << "realsize: " << realsize << std::endl;
	//std::cout << mem->size + realsize + 1 << std::endl;
	//std::cout << mem->response << std::endl;


	char* ptr = (char *)realloc(mem->response, mem->size + realsize + 1);
	if (!ptr) {
		return 0;  /* out of memory */
	}

	mem->response = ptr;
	memcpy(&(mem->response[mem->size]), data, realsize);
	mem->size += realsize;
	mem->response[mem->size] = 0;
	// End code from libcurl's API; everything after this is original again

	//std::cout << mem->response;

	std::string quizData(mem->response);

	int start = quizData.find_first_of('[');
	quizData.erase(0, start + 1);

	/**
	* Example data:
	* {"response_code":0,"results":[{"type":"multiple","difficulty":"easy","category":"General Knowledge",
	* "question":"What kind of aircraft was developed by Igor Sikorsky in the United States in 1942?",
	* "correct_answer":"Helicopter","incorrect_answers":["Stealth Blimp","Jet","Space Capsule"]},
	* {"type":"multiple,"difficulty":"easy","category":"General Knowledge",
	* "question":" Which chemical element, number 11 in the Periodic table, has the symbol Na?"
	* "correct_answer":"Sodium","incorrect_answers":["Carbon","Lead","Nitrogen"]}]}
	*/
	for (int i = 0; i < 10; i++) {
		std::wstring findstring = L"\"question\"";
		int questionStart = quizData.find("\"question\"");
		if (questionStart == std::wstring::npos) {
			std::cerr << "bad data" << std::endl;
			exit(1);
		}
		quizData.erase(0, questionStart + 12);	// Erases up to and including the opening quotation for the question title
		int answerStart = quizData.find(",\"correct_answer\"");
		std::wstring question(quizData.begin(), quizData.begin() + answerStart - 1);

		quizData.erase(0, answerStart + 19);	// Erases up to and including the opening quotation mark for the correct answer
		int incorrectStart = quizData.find(",\"incorrect_answers\"");
		std::wstring correctAnswer(quizData.begin(), quizData.begin() + incorrectStart - 1);

		quizData.erase(0, incorrectStart + 23);	// Erases up to and including the open quotation for the first incorrect answer
		int nextAnswer = quizData.find("\",\"");
		std::wstring incorrectOne(quizData.begin(), quizData.begin() + nextAnswer);

		quizData.erase(0, nextAnswer + 3);	// Erases up to the start of the next incorrect answer
		nextAnswer = quizData.find("\",\"");
		std::wstring incorrectTwo(quizData.begin(), quizData.begin() + nextAnswer);

		quizData.erase(0, nextAnswer + 3);	// Erases up to start of the next incorrect answer
		int questionEnd = quizData.find("\"]}");
		std::wstring incorrectThree(quizData.begin(), quizData.begin() + questionEnd);

		// Add the strings into the current question
		questions.at(i)->question = question;

		// Genereate randomm number to use to shuffle the answer order
		int shuffler = rand() % 4;

		// Temporary vector used for copying the various strings into the actual questions vector
		std::vector<std::wstring> temp = { correctAnswer, incorrectOne, incorrectTwo, incorrectThree };

		// Put the answers in the options array but in a shuffled order
		questions.at(i)->options.push_back(temp.at(shuffler % 4));
		questions.at(i)->options.push_back(temp.at((1 + shuffler) % 4));
		questions.at(i)->options.push_back(temp.at((2 + shuffler) % 4));;
		questions.at(i)->options.push_back(temp.at((3 + shuffler) % 4));

		// Find where the correct answer is supposed to go
		if (shuffler % 4 == 0) {
			questions.at(i)->correctAnswer = 0;
		}
		else if ((1 + shuffler) % 4 == 0) {
			questions.at(i)->correctAnswer = 1;
		}
		else if ((2 + shuffler) % 4 == 0) {
			questions.at(i)->correctAnswer = 2;
		}
		else {
			questions.at(i)->correctAnswer = 3;
		}
	}
	return realsize;
}

void Quiz::resetQuestions()
{
	questions = { new Question(), new Question(), new Question(), new Question(), new Question(),
				  new Question(), new Question(), new Question(), new Question(), new Question(), };
}

void Quiz::initQuiz()
{
	curl = curl_easy_init();
	if (!curl) {
		std::cerr << "could not make quiz." << std::endl;
		exit(1);
	}
	//struct memory* chunk = (struct memory*)malloc(sizeof(struct memory));
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Quiz::readQuiz);

	// Set the random seed to be used to shuffle question answers
	srand(time(NULL));

	//for (int i = 0; i < 10; i++) {
	//	questions.at(i)->options = { "", "", "", "" };
	//}
}

void Quiz::selectCategory(CATEGORY cat)
{
	curl_easy_setopt(curl, CURLOPT_URL, (quizString + std::to_string(cat) + "&type=multiple&encode=url3986").c_str());
}

void Quiz::selectCategory(int cat)
{
	//std::string url = quizString + std::to_string(cat) + "&type=multiple";
	//std::cout << url << std::endl;
	curl_easy_setopt(curl, CURLOPT_URL, (quizString + std::to_string(cat) + "&type=multiple").c_str());
}

void Quiz::generateQuiz()
{
	// Make sure to empty the questions vector if it had contents before this
	resetQuestions();
	// Reset the pointer in which the trivia data is placed
	chunk = { nullptr, 0 };

	CURLcode res;
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		std::cerr << "perform failed." << std::endl;
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		exit(1);
	}
	currentQuestion = 0;
	score = 0;
}

std::wstring Quiz::displayQuestion()
{
	std::wstring ret = questions.at(currentQuestion)->question + L"\n";
	ret += L"[1] " + questions.at(currentQuestion)->options.at(0) + L"\n";
	ret += L"[2] " + questions.at(currentQuestion)->options.at(1) + L"\n";
	ret += L"[3] " + questions.at(currentQuestion)->options.at(2) + L"\n";
	ret += L"[4] " + questions.at(currentQuestion)->options.at(3) + L"\n";
	return ret;
}

bool Quiz::checkAnswer(int answer)
{
	if (answer - 1 == questions.at(currentQuestion)->correctAnswer) {
		score++;
		currentQuestion++;
		return true;
	}
	currentQuestion++;
	return false;
}

void Quiz::killQuiz()
{
	curl_easy_cleanup(curl);
}
