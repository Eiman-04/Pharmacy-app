#include "Product.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

void Product::addProduct() {
	std::string productName;
	float price;
	int quantity;

	std::cout << "Enter product name: ";
	std::getline(std::cin >> std::ws, productName);

	std::cout << "Enter product price: ";
	std::cin >> price;

	std::cout << "Enter product quantity: ";
	std::cin >> quantity;

	Product product(getNextProductId(), productName, price, quantity);

	std::ofstream outfile("products.txt", std::ios::app);
	outfile << product.getId() << ',' << product.getName() << ',' << product.getPrice() << ',' << product.getQuantity() << '\n';
	outfile.close();

	std::cout << "Product added successfully!" << std::endl;
}

void Product::displayProducts() {
	std::vector<Product> products = readProducts();

	std::cout << std::left << std::setw(10) << "ID"
		<< std::left << std::setw(20) << "Name"
		<< std::left << std::setw(10) << "Price"
		<< std::left << std::setw(10) << "Quantity" << std::endl;

	for (const auto& product : products) {
		std::cout << std::left << std::setw(10) << product.getId()
			<< std::left << std::setw(20) << product.getName()
			<< std::left << std::setw(10) << product.getPrice()
			<< std::left << std::setw(10) << product.getQuantity() << std::endl;
	}
}

void Product::updateProduct() {
	std::vector<Product> products = readProducts();

	std::cout << "Enter product ID to update: ";
	int id;
	std::cin >> id;

	bool found = false;
	for (auto& product : products) {
		if (product.getId() == id) {
			std::cout << "Enter new product name: ";
			std::getline(std::cin >> std::ws, product.name);

			std::cout << "Enter new product price: ";
			std::cin >> product.price;

			std::cout << "Enter new product quantity: ";
			std::cin >> product.quantity;

			found = true;
			break;
		}
	}

	if (!found) {
		std::cerr << "Product with ID " << id << " not found." << std::endl;
		return;
	}

	std::ofstream outfile("products.txt");
	if (!outfile.is_open()) {
		std::cerr << "Error opening file." << std::endl;
		return;
	}

	for (const auto& product : products) {
		outfile << product.getId() << ',' << product.getName() << ',' << product.getPrice() << ',' << product.getQuantity() << '\n';
	}

	std::cout << "Product updated successfully!" << std::endl;
}


void Product::deleteProduct() {
	std::vector<Product> products = readProducts();

	std::cout << "Enter product ID to delete: ";
	int id;
	std::cin >> id;

	bool found = false;
	for (auto iter = products.begin(); iter != products.end(); ++iter) {
		if (iter->getId() == id) {
			products.erase(iter);
			found = true;
			break;
		}
	}

	if (!found) {
		std::cerr << "Product with ID " << id << " not found." << std::endl;
		return;
	}

	std::ofstream outfile("products.txt");
	if (!outfile.is_open()) {
		std::cerr << "Error opening file." << std::endl;
		return;
	}

	for (const auto& product : products) {
		outfile << product.getId() << ',' << product.getName() << ',' << product.getPrice() << ',' << product.getQuantity() << '\n';
	}

	std::cout << "Product deleted successfully!" << std::endl;
}

std::vector<Product> Product::readProducts() {
	std::vector<Product> products;

	std::ifstream infile("products.txt");
	if (!infile.is_open()) {
		std::cerr << "Error opening file." << std::endl;
		return products;
	}

	std::string line;
	while (std::getline(infile, line)) {
		int id, quantity;
		double price;
		std::string name;

		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, ',');
		id = std::stoi(token);
		std::getline(ss, token, ',');
		std::stringstream name_ss(token);
		std::getline(name_ss, name, '"');
		std::getline(name_ss, name, '"');
		std::getline(ss, token, ',');
		price = std::stod(token);
		std::getline(ss, token, ',');
		quantity = std::stoi(token);

		Product p(id, name, price, quantity);
		products.push_back(p);
	}

	return products;
}

void Product::displayProduct() const {
	std::cout << "ID: " << id << ", Name: " << name << ", Price: $" << price
		<< ", Quantity: " << quantity << std::endl;
}

Product Product::getProductById(int id) {
	std::vector<Product> products = readProducts();
	
	for (auto& product : products) {
		if (product.getId() == id) {
			return product;
		}
	}

	throw std::runtime_error("Product not found");
}

void Product::updateProductQuntity(Product& product, int quantity) {
	auto products = Product::readProducts();

	product.setQuantity(quantity);

	for (auto& p : products) {
		if (p.getId() == product.getId()) {
			p = product;
			break;
		}
	}

	std::ofstream outfile("products.txt");
	if (!outfile.is_open()) {
		std::cerr << "Error opening file." << std::endl;
		return;
	}

	for (const auto& product : products) {
		outfile << product.getId() << ',' << product.getName() << ',' << product.getPrice() << ',' << product.getQuantity() << '\n';
	}
}
