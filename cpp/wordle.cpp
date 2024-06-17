
#include <algorithm>
#include <cstring>
#include <iostream>

struct letter {
  char value;
  bool guessed;
};
char INPUT[5 + 1] = "BOOKS";
// struct word INPUT = "HELLOWORLDSSS";

char capitalize(char value) {
  if (value >= 97 && value <= 122) {
    value -= 32; // Converts to UpperCase
    return value;
  }
  return value;
}

bool containsChar(char string[6], char value[6]) {
  for (int i = 0; i < 5; ++i) {
    if (string[i] == value[i]) {
      return true;
    }
  }
  return false;
}

void convert(char string[6], struct letter array[]) {
  for (int i = 0; i < 5; ++i) {
    struct letter l = {string[i], 0};
    array[i] = l;
  }
}

void showOutput(char display[], int *lives) {
  std::cout << display << " LIVES: " << *lives << '\n';
}

void checklose(int *lives) {
  if (*lives <= 0) {
    std::cout << "You Lose" << '\n';
    std::cout << "The word was: " << INPUT << '\n';
    exit(1);
  }
}
void wingame() {
  std::cout << "Correct Guess, You Win!" << '\n';
  std::cout << "The word was: " << INPUT << '\n';
  exit(0);
}

char guesses[32][6] = {};
int guessesIndex = 0;
int guessed = 0;
void inputval(char string[6], char val[6], char display[], int *lives) {
  for (int i = 0; i < 5; ++i) {
    val[i] = capitalize(val[i]);
  }
  if (!containsChar(string, val)) {
    *lives -= 1;
    strcpy(guesses[guessesIndex], val);
    guessesIndex += 1;
    checklose(lives);
  } else {
    strcpy(guesses[guessesIndex], val);
    guessesIndex += 1;
    for (int i = 0; i < 5; ++i) {
      if (string[i] == val[0]) {
        display[i] = string[i];
        guessed += 1;
      }
    }
    if (guessed >= 5) {
      wingame();
    }
  }
  showOutput(display, lives);
}

void getInput(char string[6], char display[], int *lives) {
  while (true) {
    char response[6] = {};
    std::cout << "Guess: ";
    std::cin >> response;
    while (std::cin.fail()) {
      std::cout << "Invalid Response, Try Again \n";
      std::cin.clear();
      std::cin.ignore(256, '\n');
      std::cin >> response;
    }
    inputval(string, response, display, lives);
  }
}

int main(int argc, char const *argv[]) {
  int lives = 8; // declare ^LIVES
  int length = 5;
  struct letter word[length];

  char display[length]; // makes the output/display
  for (int i = 0; i < length; ++i) {
    display[i] = '-';
  }

  convert(INPUT, word);
  showOutput(display, &lives);
  getInput(INPUT, display, &lives);

  return 0;
}
