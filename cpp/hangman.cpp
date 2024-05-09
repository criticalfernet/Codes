#include <iostream>
#include <algorithm>
#include "./hangmanlist.h"

struct letter
{
	char value;
	bool guessed;
};
struct word
{
	std::string str;
	int length;
};
struct word makeword(char const input[16]){
	int len = 0;
	for (int i = 0; i < 16; ++i)
	{
		if(input[i] == '\0'){
			len = i;
			break;
		}
	}
	struct word output = {input,len};
	return output;
}

//struct word INPUT = makeword(getword()); //Capitals Only, 16 letters, ^TEXT
struct word INPUT = "HELLOWORLDSSS";


char capitalize(char value){
	if(value>=97 && value<=122){
	   value -= 32; // Converts to UpperCase
	   return value;
	}
	return value;
}

bool containsChar(struct word* string, char value){
	for (int i = 0; i < string->length; ++i)
	{
		if(string->str[i]==value){return true;}
	}
	return false;
}

void convert(struct word* string, struct letter array[]){
	for (int i = 0; i < string->length; ++i)
	{
		struct letter l = {string->str[i], 0};
		array[i] = l;
	}
}

void showOutput(char display[], int* lives){
	std::cout << display <<" LIVES: "<< *lives <<'\n';
}

void checklose(int* lives){
	if (*lives <= 0)
	{
		std::cout << "You Lose" << '\n';
		std::cout << "The word was: " << INPUT.str << '\n';
		exit(1);
	}
}
void wingame(){
	std::cout << "Correct Guess, You Win!" << '\n';
	std::cout << "The word was: " << INPUT.str << '\n';
	exit(0);
}

char guesses[32] = {};
int guessesIndex = 0;
int guessed = 0;
void inputval(struct word* string, char val,char display[], int* lives){
	val = capitalize(val);
	if(std::find(std::begin(guesses), std::end(guesses), val) != std::end(guesses)){
		std::cout << "Already Guessed this value" <<'\n';
		return;
	}
	if(!containsChar(string,val)){
		*lives -=1;
		guesses[guessesIndex] = val;
		guessesIndex += 1;
		checklose(lives);
	}else
	{
	guesses[guessesIndex] = val;
	guessesIndex += 1;
	for (int i = 0; i < string->length; ++i)
	{
		if(string->str[i]==val){
			display[i] = string->str[i];
			guessed+=1;
		}
	}
	if (guessed >= string->length){wingame();}
	}
	showOutput(display,lives);
}

void getInput(struct word* string,char display[], int* lives){
	while (true){
		char response;
		std::cout << "Guess: ";
		std::cin >> response;
		while(std::cin.fail()) {
			std::cout << "Invalid Response, Try Again \n";
	        std::cin.clear();
	        std::cin.ignore(256,'\n');
	        std::cin >> response;
	    }
	    inputval(string,response,display,lives);
	}
}

int main(int argc, char const *argv[])
{
	int lives = 8; //declare ^LIVES
	int length = INPUT.length;
	struct letter word[length] = {};

	char display[length] = {}; // makes the output/display
	for (int i = 0; i < length; ++i)
	{
		display[i] = '-';
	}

	convert(&INPUT,word);
	showOutput(display, &lives);
	getInput(&INPUT,display,&lives);

	return 0;
}
