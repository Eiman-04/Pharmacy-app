#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Product {
private:
    int id;
    std::string name;
    double price;
    int quantity;

public:
    Product() {}
    Product(int id, std::string name, double price, int quantity) : id(id), name(name), price(price), quantity(quantity) {}

    void setId(int id) {
        this->id = id;
    }

    int getId() const {
        return id;
    }

    void setName(const std::string& name) {
        this->name = name;
    }

    const std::string& getName() const {
        return name;
    }

    void setPrice(double price) {
        this->price = price;
    }

    double getPrice() const {
        return price;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }

    int getQuantity() const {
        return quantity;
    }

    static void addProduct();
    static void displayProducts();
    static void updateProduct();
    static void deleteProduct();
    static std::vector<Product> readProducts();
    void displayProduct() const;
    static Product getProductById(int id);
    static void updateProductQuntity(Product& product, int quantity);

    static int getNextProductId() {
        std::ifstream inputFile("products.txt");
        int maxId = 0;
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            int id;
            iss >> id;
            if (id > maxId) {
                maxId = id;
            }
        }
        return maxId + 1;
    }

};


