#pragma once
#include "windowStructs.hpp"
#include "init.hpp"
#include "draw.hpp"
#include "quiz.hpp"

/** Used to track if the user has yet to begin a quiz (0), is in a quiz (1), or is done and ready to replay (2) */
extern int state;

int main(int argc, char* argv[]);