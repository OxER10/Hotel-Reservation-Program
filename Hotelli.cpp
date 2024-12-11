//Oskari Järvinen
//Hotellin varausjärjestelmä
//5 Hopefully

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<time.h>
#include"functions.h"

// Const ints for prices so you can change them easily
const int onePersonPrice = 100;
const int twoPersonPrice = 150;

// struct to save customer data in reservation
struct ReserveInfo { 
	int nights, people, onePersonRoomAmount, TwoPersonRoomAmount;
	double discount, totalSum;
	std::string reserver;
};

// struct to save room data temporarily
struct HotelInfo { 
	int room, persons;
	bool reserved = false;
	std::string name;
};

void menu() {
	int roomCount = roomAmount();
	// Array from struct that stores temporary changes
	HotelInfo admin[300];
	std::ifstream HotelData("Input.txt");
	// This loop pulls data from file and changes it to variables for easier data manipulation
	for (int i = 0; i < roomCount * 2; i++){ 
		// Because data is stored in two lines per room, for have to use multiplier and divisor of 2
		std::string Text;
        getline(HotelData, Text);
		if (i == 0){
			admin[i].room = 1;
			admin[i].persons = 1;
		}
		// If line is odd, that line stores the name of reserver
		else if (i % 2 != 0){
			if (Text == "unreserved"){
				admin[i/2].reserved = false;
				admin[i/2].name = "unreserved";
			}
			else{
				admin[i/2].reserved = true;
				admin[i/2].name = Text;
			}
		}
		// If line is even, that line stores the room number
		else if (i % 2 == 0){
			if (i/2 < roomCount / 2){
				admin[(i+1)/2].room = (i+3)/2;
				admin[(i+1)/2].persons = 1;
			}
			else{
				admin[(i+1)/2].room = (i+3)/2;
				admin[(i+1)/2].persons = 2;
			}
		}
	}
	bool again = true;
	char selection;
	do { 
		int free1prRooms = 0, free2prRooms = 0;
		// Loop to check how many rooms are available
		for (int i = 0; i < roomCount; i++){
			if(admin[i].persons == 1){
				if (admin[i].reserved == false){
					free1prRooms++;
				}
			}
			else{
				if (admin[i].reserved == false){
					free2prRooms++;
				}
			}
		}
		// Main menu graphics
		std::cout << "\n--------------------------------------" << std::endl;
		std::cout << "Please select what you want to do:" << std::endl;
		std::cout << "a = Show how many available rooms" << std::endl;
		std::cout << "n = Check room occupancy by room number" << std::endl;
		std::cout << "o = Show detailed room occupancy" << std::endl;
		std::cout << "p = Show room pricing info" << std::endl;
		std::cout << "r = Reserve rooms" << std::endl;
		std::cout << "s = Search reservations with name" << std::endl;
		std::cout << "q = Quit and save" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		// Input validation
		selection = charInputCheck();
		// Shows how many rooms are available
		switch (selection){
			case 'a': {
				std::cout << "1 Person rooms available: " << free1prRooms << std::endl;
				std::cout << "2 Person rooms available: " << free2prRooms << std::endl;
				std::cout << "Total rooms available: " << free1prRooms + free2prRooms << std::endl;
			}
			break;
			// Check room status with room number
			case 'n': {
				int roomNumber;
				// Checks user's input in case of mistakes
				do{
					std::cout << "Input the room number: ";
					// Checks user input
					roomNumber = intInputCheck();
					// In case user inputs invalid room number
					if(roomNumber > roomCount || roomNumber <= 0){
						std::cout << "Couldn't find the room. Check your input.\n";
						std::cout << "Reminder: Hotel has " << roomCount << " rooms.\n";
					}
					// Loops until user inputs a valid number
				} while (roomNumber > roomCount || roomNumber <=0);
				for (int i = 0; i < roomCount; i++) {
					if(admin[i].room == roomNumber){
						if(admin[i].reserved == true){
							std::cout << "The room is reserved under the name of " << admin[i].name << ".\n";
						}
						else{
							std::cout << "The room is unreserved.\n";
						}
					}
				}
			}
			break;
			// Lists all rooms and reservation statuses
			case 'o': {
				for (int i = 0; i < roomCount; i++)
				{
					std::cout << "Room: " << admin[i].room << ", " << admin[i].persons << "pr, " << admin[i].name << std::endl;
				}
			}
			break;
			case 'p': {
				std::cout << "1 Person room price is: " << onePersonPrice << std::endl;
				std::cout << "2 Person price is: " << twoPersonPrice << std::endl;
				std::cout << "We will also apply random discount (0%, 10% or 20%) at the checkout!" << std::endl;
			}
			break;
			// Reserves the room/rooms for user and aplies a discount
			case 'r': {
				char confirmation;
				ReserveInfo customer;
				// Checks that input is correct
				do{
					std::cout << "How many persons are in this reservation?: ";
					customer.people = intInputCheck();
					if (customer.people > 2){
						std::cout << "You have too many persons for one reservation. Max persons per reservation is 2.\n";
					}
					if (customer.people <= 0){
						std::cout << "Please select positive number for persons.\n";
					}	
				}while (customer.people > 2 || customer.people <= 0);
				//checks that input is correct
				do{
					std::cout << "How many nights are you going to spend? (1-31)";
					customer.nights = intInputCheck();
					if (customer.nights > 31){
						std::cout << "Too many nights per reservation. Max nights per reservation is 31.\n";
					}
					if (customer.nights <= 0){
						std::cout << "Please select positive number for nights.\n";
					}	
				}while (customer.nights > 31 || customer.nights <=0);
				//If there is one person and rooms are available
				if(customer.people == 1 && free1prRooms >= customer.people){
					bool error = false;
					// Calculates the price
					customer.onePersonRoomAmount = customer.people;
					customer.totalSum = customer.onePersonRoomAmount * onePersonPrice * customer.nights;
					customer.discount = customer.totalSum * discountRandomizer();
					std::cout << "Your total price before discount were " << customer.totalSum << std::endl;
					customer.totalSum -= customer.discount;
					std::cout << "Your total price after discount is " << customer.totalSum << std::endl;
					// Confirms that you want to proceed with reservation
					std::cout << "Do you want to reserve " << customer.people << " one person room? (y/n): " << std::endl;
					confirmation = charInputCheck();
					if (confirmation == 'y'){
						std::cout << "Please enter the reserver's name: ";
						customer.reserver = lowerCase(stringInput());
						do{
							// User can choose to input or randomize room
							std::cout << "Do you want to choose the room or randomize? (c/r): ";
							confirmation = charInputCheck();
							if(confirmation == 'c'){
								do{
									int input;
									do{
										// Checks that input is correct
										std::cout << "Please input a room between "; 
										if (roomCount % 2 == 0){
											std:: cout << "1 - " << roomCount / 2 << ": ";
										}
										else {
											std:: cout << "1 - " << (roomCount + 1) / 2 << ": ";
										}
										input = intInputCheck();
										if(input > roomCount){
											std::cout << "The hotel doesn't have that many rooms!";
										}
										if(input > roomCount/2){
											"That room is two person room!";
										}
										if(input < 1){
											"Please enter positive number!";
										}
									} while(input < 0 || input > roomCount / 2);
									//lets user reserve te room if it's available
									if (admin[input-1].reserved == false){
										admin[input-1].name = customer.reserver;
										admin[input-1].reserved = true;
										error = false;
									}
									else {
										std::cout << "This room is reserved.\nFree rooms are: ";
											for (int i = 0; i < roomCount; i++){
												if (admin[i].reserved == false && admin[i].persons == 1){
													std::cout << admin[i].room << ", ";
												}
												
											}
										error = true;
									}
								} while (error == true);
							}
							// randomizes the room for user
							else if (confirmation == 'r'){
								std::cout << "Reserved room: " ;
								// In case that the total roomcount / 2 is even
								if (roomCount % 2 == 0){									
									int roomNumber;
									// Loops until it finds available room
									do{
										error = true;
										srand(time(NULL));
										roomNumber = 1 + rand() % ((roomCount/2) - 1 + 1);
										if (admin[roomNumber-1].reserved == false){
											admin[roomNumber-1].name = customer.reserver;
											admin[roomNumber-1].reserved = true;
											error = false;
											std::cout << roomNumber;
										}
									}while (error == true);
								}
								// In case that the total roomcount / 2 is odd
								else{
									int roomNumber;
									do{
										error = true;
										srand(time(NULL));
										roomNumber = rand() % (((roomCount+1)/2) + 1);
										if (admin[roomNumber-1].reserved == false){
											admin[roomNumber-1].name = customer.reserver;
											admin[roomNumber-1].reserved = true;
											error = false;
											std::cout << roomNumber;
										}
									}while (error == true);
								}
							}
							else{
								std::cout << "Check your input!";
								error = true;
							}
						}while(error == true);
					}
					else if (confirmation == 'n'){
						std::cout << "Reservation is cancelled.\n";
					}
				}
				// If there two persons and rooms are available. Same function with one person check, but changed values to fit two persons
				else if(customer.people == 2 && free2prRooms >= customer.people / 2){
						bool error = false;
						customer.TwoPersonRoomAmount = customer.people / 2;
						customer.totalSum = customer.TwoPersonRoomAmount * twoPersonPrice * customer.nights;
						customer.discount = customer.totalSum * discountRandomizer();
						std::cout << "Your total price before discount were " << customer.totalSum << std::endl;
						customer.totalSum -= customer.discount;
						std::cout << "Your total price is " << customer.totalSum << std::endl;
						std::cout << "Do you want to reserve " << customer.people / 2 << " two person room? (y/n): " << std::endl;
						confirmation = charInputCheck();
						if (confirmation == 'y'){
							std::cout << "Please enter the reserver's name: ";
							customer.reserver = lowerCase(stringInput());
							do{
								std::cout << "Do you want to choose the rooms or randomize? (c/r): ";
								confirmation = charInputCheck();
								if(confirmation == 'c'){
									do{
										int input;
										do{
											std::cout << "Please input a room between "; 
											if (roomCount % 2 == 0){
												std:: cout << roomCount / 2 + 1 << "-" << roomCount << ": ";
											}
											else {
												std:: cout << (roomCount + 1) / 2 + 1 << "-" << roomCount << ": ";
											}
											input = intInputCheck();
											if(input > roomCount){
												std::cout << "The hotel doesn't have that many rooms!";
											}
											if(input < roomCount/2){
												"That room is one person room!";
											}
											if(input < 1){
												"Please enter positive number!";
											}
										} while(input < roomCount/2 || input > roomCount);
										if (admin[input-1].reserved == false){
											admin[input-1].name = customer.reserver;
											admin[input-1].reserved = true;
											error = false;
										}
										else {
											std::cout << "This room is reserved.\nFree rooms are: ";
											for (int i = 0; i < roomCount; i++){
												if (admin[i].reserved == false && admin[i].persons == 2){
													std::cout << admin[i].room << ", ";
												}
												
											}
											
											error = true;
										}
									} while (error == true);
								}
								else if (confirmation == 'r'){
									std::cout << "Reserved room: " ;
									if (roomCount % 2 == 0){									
										int roomNumber;
										do{
											error = true;
											srand(time(NULL));
											roomNumber = ((roomCount / 2) + 1) + rand() % (roomCount - ((roomCount/2)+1) + 1);
											if (admin[roomNumber-1].reserved == false){
												admin[roomNumber-1].name = customer.reserver;
												admin[roomNumber-1].reserved = true;
												error = false;
												std::cout << roomNumber << " ";
											}
										}while (error == true);
									}
									else{
										int roomNumber;
										do{
											error = true;
											srand(time(NULL));
											roomNumber = ((roomCount + 1 / 2) + 1) + rand() % (roomCount - (roomCount/2) + 1);
											if (admin[roomNumber-1].reserved == false){
												admin[roomNumber-1].name = customer.reserver;
												admin[roomNumber-1].reserved = true;
												error = false;
											}
										}while(error == true);
									}
								}
								else{
									std::cout << "Check your input!";
									error = true;
								}
							}while(error == true);
						}
						else if (confirmation == 'n'){
							std::cout << "Reservation is cancelled.\n";
					}
				}
				// If there are no more free rooms
				else {
					std::cout << "Sorry not enough rooms to make reservation :(";
				}
				
			}
			break;
			// Searches for rooms with name input
			case 's': {
				int roomsUnderName = 0;
				std::cout << "Input name to search: ";
				std::string searchName = lowerCase(stringInput());
				// Calculates how many rooms under inputted name
				for (int i = 0; i < roomCount; i++){
					if (admin[i].name == searchName){
						roomsUnderName++;
					}
				}
				if(roomsUnderName > 0){
					std::cout << "Found " << roomsUnderName << " rooms reserved with inputted name." << std::endl;
					std::cout << "The reserved rooms with inputted name are: ";
					for (int i = 0; i < roomCount; i++){
						if (admin[i].name == searchName){
							std::cout << admin[i].room << " ";
						}
					}
					
				}
				else{
					std::cout << "No rooms reserved with inputted name." << std::endl;
				}
			}
			break;
			// Closes loop and saves data from struct array to file
			case 'q': {
				std::ofstream HotelData("Input.txt");
					for (int i = 0; i < roomCount; i++) {
						HotelData << admin[i].room << "\n" << admin[i].name << "\n";
					}
				again = false;
			}
			break;
			// In case of error or mistake
			default: {
				std::cout << "Please select correct character!" << std::endl;
			}
		}
		// Loops until user quits
	} while (again == true);
}

int main() {
	roomGen();
	menu();
	return 0;
}