//Oskari Järvinen
//Hotellin varausjärjestelmä
//5 Toivottavasti

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<time.h>
#include"functions.h"

struct Customer { // struct to pull data from txt
	bool reserved;
	std::vector<std::string> name [2];
	int nights, persons;
};

void menu() {
	bool again;
	char selection;
	do {
		std::cout << "\n----------------------------------" << std::endl;
		std::cout << "Please select what you want to do:" << std::endl;
		std::cout << "s = See rooms" << std::endl;
		std::cout << "r = Reserve room" << std::endl;
		std::cout << "q = Quit" << std::endl;
		std::cout << "----------------------------------" << std::endl;
		std::cin >> selection;
		if (std::cin.fail()) {
			again = true;
			inputCheck();
		}
		else {
			if (selection == 's' || selection == 'S') {
				std::ifstream Rooms("Rooms.txt");
				std::string Text;
				getline(Rooms, Text);
				
			}
			else if (selection == 'r' || selection == 'R') {

			}
			else if (selection == 'q' || selection == 'Q') {
				again = false;
			}
			else {
				std::cout << "Please select correct character!" << std::endl;
			}
		}
	} while (again == true);
}

int main() {
	roomGen();
	menu();
	return 0;
}