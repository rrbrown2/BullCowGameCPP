/* *This is the console executable, that makes use of the BullCow class
 For game logic see the FBullCowGame class.* 
*/
#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// *to make syntax Unreal Game friendly*
using FText = std::string;
using int32 = int;

// *function prototypes* 
void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
FText GetValidGuess();
FBullCowGame BCGame; // *instantiate a new game object, which we re-use across plays*
					
int main()  //*entry point for our application*
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // *exit the application*
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame() // *plays a single game to completion*
{
	BCGame.ResetGame();
	int32 MaxTries = BCGame.GetMaxTries();

	// *loop asking for guesses while the game*
	// *is NOT won and there are still tries remaining*
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.submitValidGuess(Guess); // *submit valid guess to the game, and receive counts*
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


FText GetValidGuess() // *loop continually until the user gives a valid guess*
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do { // *get a guess from the player*
		
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// *check status of the guess and give feedback*
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::NOT_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// *assume the guess is valid*
			break;
		}
	} while (Status != EGuessStatus::OK); // *keep looping until we get no errors*
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	system("cls"); // *clear screen for new game*
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
		std::cout << "WELL DONE - YOU WIN!\n";
	
	else
		std::cout << "Better luck next time!\n";

	return;
}
