#include <iostream>
#include <random>

/* 
Two Die are at random
user chooses upper or lower
User puts a bid of min 100
if Total > User, and user chose upper, they win
similar for other cases
If total = 7, user always win
incase of win, user gets double the bid
else they get nothing
Their initial money is set to 2000
*/


std::random_device dev; // creates a seed using devicd
std::mt19937 generator(dev()); // pseudo random number generator
std::uniform_int_distribution<std::mt19937::result_type> distribution(1,6); // distributer

int getDie(){
	//return random between 1 and 6
	return distribution(generator);
}

bool startRound(){
	std::cout << "Press 1 to play \n";
	std::cout << "Press 0 to exit \n";
	int response;
	std::cin >> response;
	while(std::cin.fail()) {
		std::cout << "Invalid Response(non integer), Try Again \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> response;
    }
	if (response != 1 && response !=0){
		std::cout << "Invalid Response, Try Again \n";
		return startRound();
	}
	return response;
}

int getBid(int total){
	int bid;
	std::cout << "Enter Bid: ";
	std::cin >> bid;
	while(std::cin.fail()) {
		std::cout << "Invalid Response(non a number), Try Again \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> bid;
    }
	if (bid < 100 || bid > total){
		std::cout << "invalid bid, Try again. \n";
		return getBid(total);
	}
	return bid;
}

bool getResult(int total, bool prediction){
	if(total == 7){return true;}
	if(total > 7 ){return prediction;}
	if(total < 7){return !prediction;}
	else{return -1;}
}

// checks for error
bool testPrediction(){
	try{
		int temp;
		std::cin >> temp;
		while(std::cin.fail()) {
	        std::cout << "Error, Not a Number, Try Again: ";
	        std::cin.clear();
	        std::cin.ignore(256,'\n');
	        std::cin >> temp;
    	}

		if(temp != 1 && temp != 0){throw temp;}

		return (bool)temp;
	}
	catch(int &e){
		std::cout << "Invalid Value("<< e<<"), try Again: ";
		return testPrediction();
	}
	catch(...){
		std::cout << "Unknown Error";
		return 0;
	}

}

int main(int argc, char const *argv[])
{
	int totalMoney = 2000;

	while (true) {
		if(!startRound()){break;}

		int bid = getBid(totalMoney);
		totalMoney -= bid;

		bool prediction;
		std::cout << "choose Higher(1) or Lower(0) : ";
		prediction = testPrediction();

		int total = getDie() + getDie();

		bool victory = getResult(total, prediction);

		std::cout << "The Total came out to be "<< total<<", ";
		std::cout << ((victory)? "You Win \n": "You Lose \n");
		if (victory){totalMoney += 2*bid;}
		std::cout << "Total Money: "<<totalMoney<<'\n';

	}

	return 0;
}
