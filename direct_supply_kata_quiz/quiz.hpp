#pragma once
#include <vector>
#include <curl/curl.h>
#include "question.hpp"

/**
* Manages all the data for the quizzes. The trivia questions are drawn from the Open Trivia Database.
*/
class Quiz
{
private:
	/* The curl used to get the trivia questions and answers */
	CURL* curl;
	/* A count of the number of questions the user has gotten correct */
	int score;
	/* The function that takes in all the data from the curl perform and stores it in the questions vector */
	static size_t readQuiz(char* data, size_t size, size_t nmemb, void* readData);
	/* Resets the questions vector to fill it with new questions upon quiz replay */
	void resetQuestions();

public:
	/* A collection of the trivia questions in the current version of the quiz */
	static std::vector<Question*> questions;
	/* The index of the question currently being posed to the user */
	int currentQuestion;

	/* The category of the trivia quiz. Used to alter the API URL to get the trivia questions */
	enum CATEGORY
	{
		GENERAL_KNOWLEDGE = 9,
		BOOKS,
		FILM,
		MUSIC,
		MUSICALS_AND_THEATRE,
		TV,
		VIDEO_GAMES,
		BOARD_GAMES,
		SCIENCE_AND_NATURE,
		COMPUTERS,
		MATH,
		MYTHOLOGY,
		SPORTS,
		GEOGRAPHY,
		HISTORY,
		POLITICS,
		ART,
		CELEBRITIES,
		ANIMALS,
		VEHICLES,
		COMICS,
		GADGETS,
		ANIME_AND_MANGA,
		CARTOONS_AND_ANIMATIONS,
	};

	/* Initializes the quiz, creating the CURL and setting some of its options */
	void initQuiz();

	/* Uses the given category to set the URL the CURL will be drawing the questions from */
	void selectCategory(CATEGORY cat);

	/* Uses the given category to set the URL the CURL will be drawing the questions from */
	void selectCategory(int cat);

	/* Fetches the trivia questions and loads them into the questions collection */
	void generateQuiz();

	/* Returns a string representing the current question */
	std::string displayQuestion();

	/* Checks if the index of the option chosen by the user is the correct answer for the question */
	bool checkAnswer(int answer);

	/* Returns the user's current score */
	int getScore() { return score; };

	/* Destroys the quiz, doing some cleanup for the CURL */
	void killQuiz();
};
