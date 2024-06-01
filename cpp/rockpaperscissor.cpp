#include <iostream>
#include <random>
#include <time.h>

char rules[3][64] = {"rock", "paper", "scissor"};
/*
        This version allows for games with more than three rules,
                But the rules must be in ascending order of winning
        Example of a Four Rules Game:
*/
// char rules[4][64] = {"fire", "water", "thunder","grass"};

int length = sizeof(rules) / sizeof(char[64]);

std::random_device dev;
std::mt19937 generator(dev());
std::uniform_int_distribution<std::mt19937::result_type>
    distribution(0, length - 1);

int response(int length) { return distribution(generator); }

void declareRules(char (*rulesList)[64], int length) {

  for (int i = 0; i < length; ++i) {
    std::cout << "Enter " << i << " for " << rulesList[i] << '\n';
  }
}

/*
        -1: Error
        1: win
        2: Lose
        0: Draw
        3: Nothing
*/
int evaluate(int player, int computer, int length) {

  if (player < 0 || computer < 0) {
    return -1; // Invalid values
  }

  if (computer == player) {
    return 0; // Draw
  }

  if (player == (computer + 1) % length) {
    return 1; // Player wins
  }
  if (computer == (player + 1) % length) {
    return 2; // Computer wins
  }

  return 3;
}

int main(int argc, char const *argv[]) {
  srand(time(0));
  declareRules(rules, length);
  std::cout << "Enter -1 to exit" << '\n';

  while (true) {
    int input;
    std::cout << "Value: ";
    std::cin >> input;
    while (std::cin.fail()) {
      std::cout << "Invalid Response(), Try Again \n";
      std::cin.clear();
      std::cin.ignore(256, '\n');
      std::cin >> input;
    }

    if (input == -1) {
      break;
    }

    int res = response(length);

    std::cout << "You chose " << rules[input % length] << " & Computer chose "
              << rules[res] << '\n';

    int result = evaluate(input % length, res, length);

    switch (result) {
    case -1:
      std::cout << "Error" << '\n';
      break;
    case 0:
      std::cout << "Draw" << '\n';
      break;
    case 1:
      std::cout << "You Win" << '\n';
      break;
    case 2:
      std::cout << "Computer Wins" << '\n';
      break;
    case 3:
      std::cout << "Nothing Happened" << '\n';
      break;
    }
  }
  return 0;
}
