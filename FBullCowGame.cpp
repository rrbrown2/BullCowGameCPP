#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map 

using int32 = int;
using FString = std::string;

void FBullCowGame::ResetGame()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	const FString HIDDEN_WORD = "pirate"; // Hidden Word MUST be an isogram and MUST be lowercase
	MyHiddenWord = HIDDEN_WORD;
	return;
}
FBullCowGame::FBullCowGame(){ResetGame();} // constructor
bool FBullCowGame::IsGameWon() const{return bGameIsWon;}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7}, {5,8},{6,10} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if guess is not an isogram
		return EGuessStatus::NOT_Isogram;
	
	else if (!IsLowercase(Guess))
		return EGuessStatus::Not_Lowercase;

	else if (Guess.length() != GetHiddenWordLength())
		return EGuessStatus::Wrong_Length;

	else
		return EGuessStatus::OK;
	

	
}


//recieves a VALid guess, increments turn, and focus on  the interface above
FBullCowCount FBullCowGame::submitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); //assuming Hidden word and Guess and the same length

	for (int32 MyHiddenWordChar = 0; MyHiddenWordChar < WordLength; MyHiddenWordChar++) //loop through all letters in the hidden word
	{
		for (int32 MyGuessChar = 0; MyGuessChar < WordLength; MyGuessChar++)
		{
			if (Guess[MyGuessChar] == MyHiddenWord[MyHiddenWordChar])
			{
				if (MyHiddenWordChar == MyGuessChar) 
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
		bGameIsWon = true;
	else
		bGameIsWon = false;
	
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; } // treat 0 and 1 letter words as isograms

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // loops through all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
			return false;
		else 
			LetterSeen[Letter] = true;
	}					
	return true; 
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}
