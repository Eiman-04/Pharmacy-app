// Pharmacy-app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Product.h"
#include "Client.h"
#include "Sale.h"
#include <iostream>
#include <string>
#include "Pharmacy-app.h"

int main()
{
	int choice;
	do {
		std::cout << "Please choose an option:\n";
		std::cout << "1. Manage Products\n";
		std::cout << "2. Manage Clients\n";
		std::cout << "3. Manage Sales\n";
		std::cout << "0. Exit\n";
		std::cout << "Your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			ManageProducts();
			break;
		}
		case 2: {
			ManageClients();
			break;
		}
		case 3: {
			ManageSales();
			break;
		}
		case 0: {
			std::cout << "Exiting program...\n";
			break;
		}
		default: {
			std::cout << "Invalid choice. Please choose again.\n";
			break;
		}
		}
	} while (choice != 0);

	return 0;
}

void ManageSales()
{
	// Code to manage sales
	int choice = 0;
	do {
		std::cout << "Choose an option: \n";
		std::cout << "1. Create sale\n";
		std::cout << "2. Display sales\n";
		std::cout << "0. Return to the previous menu\n";
		std::cout << "Your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			// Create sale
			try {
				Sale::createSale();
			}
			catch (std::runtime_error& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
			break;

		case 2:
			// Display sales
			Sale::displaySales();
			break;

		case 3:
			// Exit program
			std::cout << "Returning to the previous menu...\n";
			break;

		default:
			// Invalid input
			std::cout << "Invalid input\n";
			break;
		}

	} while (choice != 0);
	std::cout << "\n";
}

void ManageClients()
{
	// Code to manage clients
	int choice;

	do {
		std::cout << "Choose an option:\n";
		std::cout << "1. Create a new client\n";
		std::cout << "2. Update an existing client\n";
		std::cout << "3. Delete an existing client\n";
		std::cout << "4. Display all clients\n";
		std::cout << "0. Return to the previous menu\n";
		std::cout << "Your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			// Create a new client
			std::string name;
			std::cout << "Enter client name: ";
			std::getline(std::cin >> std::ws, name);

			Client client;
			client.setName(name);
			Client::addClient(client);

			std::cout << "Client created successfully!\n";
			break;
		}
		case 2: {
			// Update an existing client
			int id;
			std::cout << "Enter client id to update: ";
			std::cin >> id;

			try {
				Client client = Client::getClientById(id);
				std::cout << "Client found: ID = " << client.getId() << ", Name = " << client.getName() << std::endl;
				std::string name;
				std::cout << "Enter new client name: ";
				std::getline(std::cin >> std::ws, name);

				client.setName(name);
				Client::updateClient(id, client);
				std::cout << "Client updated successfully!\n";
			}
			catch (std::runtime_error& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}

			break;
		}
		case 3: {
			// Delete an existing client
			int id;
			std::cout << "Enter client id to delete: ";
			std::cin >> id;
			Client::deleteClient(id);

			break;
		}
		case 4: {
			// Display all clients
			std::vector<Client> clients = Client::readClients();
			Client::displayClients(clients);

			break;
		}
		case 0:
			std::cout << "Returning to the previous menu...\n";
			break;
		default:
			std::cout << "Invalid choice!\n";
			break;
		}
	} while (choice != 0);
	std::cout << "\n";
}

void ManageProducts()
{
	int choice;

	do {
		std::cout << "1. Create product\n";
		std::cout << "2. Update product\n";
		std::cout << "3. Delete product\n";
		std::cout << "4. Display products\n";
		std::cout << "0. Return to the previous menu\n";
		std::cout << "Your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			Product::addProduct();
			break;

		case 2:
			Product::updateProduct();
			break;

		case 3:
			Product::deleteProduct();
			break;

		case 4:
			Product::displayProducts();
			break;

		case 0:
			std::cout << "Returning to the previous menu...\n";
			break;

		default:
			std::cout << "Invalid choice. Please try again.\n";
			break;
		}
	} while (choice != 0);
	std::cout << "\n";
}
