/*
The game logic(no user interaction here)
A random word is given to the user 
the user guesses the word if the user gets a letter in the word correct they recieve a cow
if the user gets a letter correct but is in the wrong place in the word they recieve a bull
if a user get all letters in the correct places recieving all bull and no cows they have won the game!

*/
#pragma once
#include <string>

//unreal game friendly syntax
using FString = std::string;
using int32 = int;

// count the amount of bull and cows
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	NOT_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{
public:
	FBullCowGame(); // constructor
	void ResetGame();
	bool IsGameWon() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	FBullCowCount submitValidGuess(FString);

private:
	//see constructor for initilizations
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};