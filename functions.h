// This header stores common functions and the file generation function

#include<iostream>
#include<sys/stat.h>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>

// Void that checks user int input for errors
int intInputCheck() {
    int input;
    bool error;
    do{
        std::cin >> input;
        if (std::cin.fail()){
            std::cout << "Error. Check your input!" << std::endl;
            std::cin.clear();
            std::cin.ignore(80, '\n');
        }
        else {
            error = false;
        }
    }while (error == true);
    return input;
}

// Void that checks user char input for errors and converts it to lowercase
char charInputCheck() {
    char input;
    bool error;
    do{
        std::cin >> input;
        if (std::cin.fail()){
            std::cout << "Error. Check your input!" << std::endl;
            std::cin.clear();
            std::cin.ignore(80, '\n');
        }
        else {
            error = false;
        }
    }while (error == true);
    return tolower(input);
}

// Void that prepares the command line for string input
std::string stringInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;
	getline(std::cin, input);
    return input;			
    }

// void that changes every character in a string to lower case. This is used to minimize the user error.
std::string lowerCase(std::string i){
    std::transform(i.begin(), i.end(), i.begin(), [](unsigned char c){ return std::tolower(c); });
    return i;
}

// Void that ranzomizes the discount
double discountRandomizer(){
    int rng;
    srand(time(NULL));
    rng = 1 + rand() % (3 - 1 + 1);
    switch (rng){
        case 1: {
            return 0.0;
        }
        break;
        case 2: {
            return 0.1;
        }
        break;
        case 3: {
            return 0.2;
        }
        default: {
            return 0;
        }
    }
}

// Void that generates new rooms if needed
void roomGen() { 
	int rooms;
    const char* file = "Input.txt";
    struct stat sb;
	char confirmation;
	bool error = false;
    // Checks that Rooms.txt exists
    if (stat(file, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
        do {
            std::cout << "Do you want to generate rooms again? (y/n)" << std::endl;
            confirmation = tolower(charInputCheck());
            // Generates new rooms
            if (confirmation == 'y') {
                std::ofstream HotelData("Input.txt");
                srand(time(NULL));
                do{
                rooms = 40 + rand() % (300 - 40 + 1);
                } while(rooms % 2 == 0);
                for (int i = 1; i < rooms; i++) {
                    HotelData << i << "\nunreserved\n";
                }
            }
            else if (confirmation == 'n') {
                error = false;
            }
            else {
                std::cout << "Please select y or n\n";
                error = true;
            }
        } while (error == true);
    }
    // Automatically generates rooms if Rooms.txt doesn't exist
    else{ 
        std::cout << "Input.txt file doesn't exist. Automatically generated the file.\n";
        std::ofstream HotelData("Rooms.txt");
        srand(time(NULL));
        do{
            rooms = 40 + rand() % (300 - 40 + 1);
        }while (rooms % 2 == 0);
        for (int i = 1; i < rooms; i++) {
            HotelData << i << "\nunreserved\n";
        }
    }
} 

int roomAmount(){
    int rooms = 0;
    std::ifstream HotelData("Input.txt");
    for (int i = 1; i < 800; i++){
            std::string Text;
            getline(HotelData, Text);
            if (Text == "") {
            }
            else{           
                rooms++;
            }
    }
    rooms = rooms/2;
    return rooms;
}
