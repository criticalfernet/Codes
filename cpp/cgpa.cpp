#include <iostream>


int main(int argc, char const *argv[])
{
	int length;

	std::cout<<"Enter number of subjects: ";
	std::cin>>length;

	int marks[length] = {0};

	std::cout<<"Enter Marks:"<<'\n';
	for (int i = 0; i < length; ++i)
	{
		std::cin>> marks[i];
	}

	int total = 0;
	for (int val : marks){
		total += val;
	}

	float cgpa = total/length;

	std::cout<<"Your CGPA is: "<<cgpa<<'\n';

	return 0;
}
