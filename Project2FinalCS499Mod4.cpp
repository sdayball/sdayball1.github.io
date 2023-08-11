/*
 * main.cpp
 *
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <openssl/sha.h> // Using OpenSSL's SHA-256 implementation for simplicity



using namespace std;

struct Client {
	std::string name;
	int accountOption;
};

void DisplayInfo(const std::vector<Client>& clients){
	std::cout<< "Clients name    Service Selected (1 = brokerage,2 = retirement)" << std::endl;
	for(int i = 0; i <clients.size(); ++i){
		std::cout << i +1 << "." << clients[i].name << ", option" << clients[i].accountOption << std::endl;
	}
}

void ChangeCustomerChoice(std::vector<Client>& clients, int clientIndex, int newOption){
	clients[clientIndex].accountOption = newOption;

}
//First security vulnerability is spotted here. We need a more secure way of storing the password.
//bool CheckUserPermission(const std::string& password){
	//return password == "123";

//}

//Code enhancement #1 to fix security issue surrounding password security
// Function to generate a random salt
std::string GenerateSalt() {
	
	const int saltLength = 16; // Adjust the length as needed
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string salt;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

	for (int i = 0; i < saltLength; ++i) {
		salt += alphanum[dis(gen)];
	}

	return salt;
}

// Function to hash the password with the salt using SHA-256
std::string HashPassword(const std::string& password, const std::string& salt) {
	std::string saltedPassword = password + salt;
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256(reinterpret_cast<const unsigned char*>(saltedPassword.c_str()), saltedPassword.length(), hash);
	std::string hashedPassword(reinterpret_cast<const char*>(hash), SHA256_DIGEST_LENGTH);
	return hashedPassword;
}

// Function to check user permission using hashed password and salt
bool CheckUserPermission(const std::string& enteredPassword, const std::string& storedHashedPassword, const std::string& storedSalt) {
	std::string enteredPasswordHash = HashPassword(enteredPassword, storedSalt);
	return storedHashedPassword == enteredPasswordHash;
}

int main() {
	// Example usage
	std::string storedSalt = GenerateSalt();
	std::string storedPassword = HashPassword("user_password", storedSalt);


	std::string enteredPassword;
	std::cout << "Enter your password: ";
	std::cin >> enteredPassword;

	if (CheckUserPermission(enteredPassword, storedPassword, storedSalt)) {
		std::cout << "Access granted!" << std::endl;
	}
	else {
		std::cout << "Access denied!" << std::endl;
	}

	return 0;
}


int main(){
	//No error handling if username or password are invalid inputs
	std::cout <<"Created by Sam Dayball CS410 05/31/2023" << std::endl;
	std::cout << "Hello! Welcome to our Investment Company" << std::endl;
	std::string username;
	std::cout << "Enter your username: ";

	std::string password;
	std::cout <<"Enter your password: ";
	std::getline(std::cin, password);
	//validate username and password inputs
	if (username.empty() || password.empty()){
		std::cout << "Username or password cannot be empty. Please try again" << std::endl;
	}else{

	//No error handling to start so adding else statement to fix
	if(CheckUserPermission(password)){
		std::cout << "What would you like to do?" << std::endl;

		int option = 0;
		// this by default opens an infinite loop while the option is not 3
		while (option != 3){
			std::cout << "DISPLAY the client list (enter 1) " << std:: endl;
			std::cout << "CHANGE a clients choice (enter 2) " << std:: endl;
			std::cout << "EXIT the program..(enter 3) " << std:: endl;
			//No validation or sanitization of user input, commented out old vulnerable code to allow for the fix to be active.
			//int option;
			//std::cin >> option;

			int userOption;//defines user input option as int type
			std::cin >> userOption;

			if (userOption >= 1 && userOption <=3){//sets parameters for valid inputs
				option = userOption;
			}else {
				std::cout << "Invalid choice. Please make a valid selection." << std::endl;//throws error if user makes an invalid input.
			}

		switch (option){
			case 1:
				std::vector<Client> clients = {
					{"Bob Jones selected option ", 1},
					{"Sarah Davis selected option ", 2},
					{"Amy Friendly selected option ", 1},
					{"Johnny Smith selected option ", 1},
					{"Carol Spears selected option ", 2},

			};

			DisplayInfo(clients);
			std::cout << "What would you like to do?" << std::endl;
			std::cout << "DISPLAY the client list (enter 1) " << std:: endl;
			std::cout << "CHANGE a clients choice (enter 2) " << std:: endl;
			std::cout << "EXIT the program..(enter 3) " << std:: endl;
			std::cin >> option;

			//Does not avalidate user input by default
			if (option == 2) {
				int clientIndex;
				std::cout << "Enter the number of the client you wish to change." << std::endl;
				std::cin >> clientIndex;

				//adds parameters to throw error if input is invalid
				if (std::cin.fail()){
					std::cout << "Invalid input." << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue; //goes back to the beginning of the loop
				}
				//adds protections against selecting an invalid client #
				if (clientIndex < 0 || clientIndex >= clients.size()) {
					std::cout << "Invalid client selection." << std::endl;
					continue;
				}

				if(clientIndex >= 0 && clientIndex < clients.size()){
					int newOption;
					std::cout << "Please enter the clients new services choice" << std::endl;
					std::cin >> newOption;
					//fails the function if the input is invalid.
					if(std::cin.fail()){
						std::cout << "Invalid input." << std::endl;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					//throws error if user inputs anything other than a 1 or 2
					if(newOption != 1 && newOption != 2){
						std::cout << "invalid option. Please enter either 1 or 2" <<std::endl;
						continue;
					}

					if(newOption == 1 || newOption == 2){
						ChangeCustomerChoice(clients, clientIndex, newOption);
					}
				//fix to close the infinite loop
				if(option == 3){
					break;
				}

				if (option <1&& option >= 4){
					std::cout << "Invalid option." << std::endl; //throw an error if an option is selected that is not valid.
				}
			
			
				}else{
					return 0;
					}
			
			
				}
		
			}

		}

	}else{
		std::cout << "Invalid Password. Please try again" << std::endl;//error handling for invalid password
	}
	return 0;
}
}
