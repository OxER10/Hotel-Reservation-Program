#include<iostream>
#include<sys/stat.h>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

void inputCheck() {
    std::cout << "Error. Check your input!" << std::endl;
	std::cin.clear();
	std::cin.ignore(80, '\n');
}

void roomGen() { // Void that generates new rooms if needed
	int room;
    const char* file = "Rooms.txt";
    struct stat sb;
	char confirmation;
	bool error;
    if (stat(file, &sb) == 0 && !(sb.st_mode & S_IFDIR)) { // Checks that Rooms.txt exists
        do {
            std::cout << "Do you want to generate rooms again? (y/n)" << std::endl;
            std::cin >> confirmation;
            if (std::cin.fail()) {
                error = true;
                inputCheck();
            }
            else {
                if (confirmation == 'y' || confirmation == 'Y') { // Generates new rooms
                    std::ofstream Rooms("Rooms.txt");
                    srand(time(NULL));
                    int rooms = rand() % (300 - 40 - 1);
                    for (int i = 1; i < rooms; i++) {
                        if (i <= rooms / 2) {
                            Rooms << i << "\n1pr\nunreserved\n";
                        }
                        else if (i > rooms / 2) {
                            Rooms << i << "\n2pr\nunreserved\n";
                        }
                    }
                    error = false;
                }
                else if (confirmation == 'n' || confirmation == 'N') {
                    error = false;
                }
                else {
                    std::cout << "Please select y or n\n";
                    error = true;
                }
            }
        } while (error == true);
    }
    else{ // Automatically generates rooms if Rooms.txt doesn't exist
        std::cout << "Rooms.txt file doesn't exist. Automatically generated the file.\n";
        std::ofstream Rooms("Rooms.txt");
        srand(time(NULL));
        int rooms = rand() % (300 - 40 - 1);
        for (int i = 1; i < rooms; i++) {
            if (i <= rooms / 2) {
                Rooms << i << "\n1pr\nunreserved\n";
            }
            else if (i > rooms / 2) {
                Rooms << i << "\n2pr\nunreserved\n";
            }
        }
    }
} 