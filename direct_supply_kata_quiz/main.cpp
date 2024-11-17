#pragma once
#include "main.hpp"

int state = 0;

int main(int argc, char* args[])
{
	// Make and initialize the quiz
	Quiz* quiz = new Quiz();
	quiz->initQuiz();

	while (true) {
		switch (state) {
		case 0:	// Quiz category selection
			std::cout << "Welcome! Choose a category for your triva quiz:" << std::endl;
			std::cout << "[1]   General Knowledge" << std::endl;
			std::cout << "[2]   Books" << std::endl;
			std::cout << "[3]   Films" << std::endl;
			std::cout << "[4]   Music" << std::endl;
			std::cout << "[5]   Musicals/Theatre" << std::endl;
			std::cout << "[6]   Television" << std::endl;
			std::cout << "[7]   Video Games" << std::endl;
			std::cout << "[8]   Board Games" << std::endl;
			std::cout << "[9]   Science and Nature" << std::endl;
			std::cout << "[10]  Computers" << std::endl;
			std::cout << "[11]  Math" << std::endl;
			std::cout << "[12]  Mythology" << std::endl;
			std::cout << "[13]  Sports" << std::endl;
			std::cout << "[14]  Geography" << std::endl;
			std::cout << "[15]  History" << std::endl;
			std::cout << "[16]  Politics" << std::endl;
			std::cout << "[17]  Art" << std::endl;
			std::cout << "[18]  Celebrities" << std::endl;
			std::cout << "[19]  Animals" << std::endl;
			std::cout << "[20]  Vehicles" << std::endl;
			std::cout << "[21]  Comics" << std::endl;
			std::cout << "[22]  Gadgets" << std::endl;
			std::cout << "[23]  Anime and Manga" << std::endl;
			std::cout << "[24]  Cartoons and Animations" << std::endl;

			// Read in the user's choice and generate a quiz with the corresponding category
			int cat;
			while (scanf_s("%d", &cat) != 1 || cat < 1 || cat > 24) {
				std::cout << "Enter the number beside the category to choose it" << std::endl;
			}
			quiz->selectCategory(cat + 8);
			quiz->generateQuiz();
			state = 1;
			std::cout << std::endl;
			break;

		case 1:	// Quiz is currently ongoing
			std::cout << "Question " << quiz->currentQuestion + 1 << ":" << std::endl;
			std::cout << quiz->displayQuestion();
			int answer;
			while (scanf_s("%d", &answer) != 1 || answer < 1 || answer > 4) {
				std::cout << "Enter the number beside the answer to choose it" << std::endl;
			}
			if (quiz->checkAnswer(answer)) {
				std::cout << "Correct!" << std::endl << std::endl;
			}
			else {
				std::cout << "Incorrect" << std::endl << std::endl;
			}
			if (quiz->currentQuestion == 10) {
				state = 2;
			}
			break;

		case 2:	// Quiz is over
			std::cout << "Congratulations! You've completed the quiz! Your final score was " << quiz->getScore() << "!" << std::endl;
			std::cout << "Play again?" << std::endl;
			std::cout << "[1] Yeah!" << std::endl;
			std::cout << "[2] Nah" << std::endl;

			int response;
			while (scanf_s("%d", &response) != 1 || response < 1 || response > 2) {
				std::cout << "Enter the number beside the answer to choose it" << std::endl;
			}
			std::cout << std::endl;
			if (response == 1) {
				state = 0;
			}
			else {
				std::cout << "Thanks for playing!" << std::endl;
				exit(0);
			}
			break;
		}
	}
}