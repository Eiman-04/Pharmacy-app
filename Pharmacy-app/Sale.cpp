#include "Sale.h"
#include "Client.h"
#include "Product.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

Sale::Sale(int id, int productId, int clientId, const std::string& productName, const std::string& clientName, int quantity, float price, const std::string& date) {
	this->id = id;
	this->productId = productId;
	this->clientId = clientId;
	this->productName = productName;
	this->clientName = clientName;
	this->quantity = quantity;
	this->price = price;
	this->date = date;
}

void Sale::createSale() {
	int productId, clientId, quantity;
	std::string productName, clientName;
	// Read input values from user
	std::cout << "Enter product ID: ";
	std::cin >> productId;

	Product product = Product::getProductById(productId);

	std::cout << "Enter client ID: ";
	std::cin >> clientId;

	Client client = Client::getClientById(clientId);

	std::cout << "Enter quantity: ";
	std::cin >> quantity;

	std::string date = Sale::getCurrentDateTime();

	Product::updateProductQuntity(product, product.getQuantity() - quantity);

	int id = Sale::getNextSaleId();
	// Create the sale object and add it to the file
	Sale sale(id, product.getId(), client.getId(), product.getName(), client.getName(), quantity, product.getPrice(), date);
	writeSale(sale);
	std::cout << "Sale added successfully!\n";
}

void Sale::writeSale(const Sale& sale) {
	std::ofstream outFile;
	outFile.open("sales.txt", std::ios_base::app);

	if (!outFile) {
		std::cerr << "Error opening sales file." << std::endl;
	}

	outFile << sale.id << ",";
	outFile << sale.productId << ",";
	outFile << sale.clientId << ",";
	outFile << sale.productName << ",";
	outFile << sale.clientName << ",";
	outFile << sale.quantity << ",";
	outFile << sale.price << ",";
	outFile << sale.date << std::endl;

	outFile.close();
}

int Sale::getNextSaleId() {
	std::ifstream inFile("sales.txt");
	int id = 0;
	std::string line;

	while (std::getline(inFile, line)) {
		std::istringstream ss(line);
		std::string token;
		std::getline(ss, token, ',');
		int currentId = std::stoi(token);
		if (currentId > id) {
			id = currentId;
		}
	}

	inFile.close();
	return id + 1;
}

std::vector<Sale> Sale::readSales() {
	std::vector<Sale> sales;
	std::ifstream inFile("sales.txt");
	std::string line;

	while (std::getline(inFile, line)) {
		std::istringstream ss(line);
		std::string token;

		// Read sale ID
		std::getline(ss, token, ',');
		int id = std::stoi(token);

		// Read product ID
		std::getline(ss, token, ',');
		int productId = std::stoi(token);

		// Read client ID
		std::getline(ss, token, ',');
		int clientId = std::stoi(token);

		// Read product name
		std::getline(ss, token, ',');
		std::string productName = token;

		// Read client name
		std::getline(ss, token, ',');
		std::string clientName = token;

		// Read quantity
		std::getline(ss, token, ',');
		int quantity = std::stoi(token);

		// Read price
		std::getline(ss, token, ',');
		float price = std::stoi(token);

		// Read date
		std::getline(ss, token, ',');
		std::string date = token;

		// Create sale object and add to vector
		Sale sale(id, productId, clientId, productName, clientName, quantity, price, date);
		sales.push_back(sale);
	}

	inFile.close();
	return sales;
}

void Sale::displaySales() {
	std::vector<Sale> sales = readSales();

	std::cout << "Sales:" << std::endl;
	std::cout << "ID\tProduct ID\tClient ID\tProduct Name\t\tClient Name\t\tQuantity\tPrice\tDate" << std::endl;

	for (const auto& sale : sales) {
		std::cout << sale.id << "\t" << sale.productId << "\t\t" << sale.clientId << "\t\t" << std::left << std::setw(16) << sale.productName << "\t" << std::left << std::setw(16) << sale.clientName << "\t" << sale.quantity << "\t\t" << std::fixed << std::setprecision(2) << sale.price << "\t" << sale.date << std::endl;
	}
}

std::string Sale::getCurrentDateTime() {
	// Get current system time
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// Convert system time to local time
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm local_now;
	localtime_s(&local_now, &now_c);

	// Format local date and time as string
	char buffer[80];
	std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &local_now);

	// Get local date and time as string
	std::string local_datetime = buffer;

	return local_datetime;
}
