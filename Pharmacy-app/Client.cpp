#include "Client.h"
#include <fstream>
#include <sstream>

Client::Client(int id, const std::string& name)
    : id_(id), name_(name)
{
}

int Client::getId() const {
    return id_;
}

std::string Client::getName() const {
    return name_;
}

void Client::setName(const std::string& name) {
    name_ = name;
}

void Client::setId(int id) {
    id_ = id;
}

std::vector<Client> Client::readClients() {
    std::vector<Client> clients;

    std::ifstream infile("clients.txt");
    if (!infile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return clients;
    }

    std::string line;
    while (std::getline(infile, line)) {
        int id;
        std::string name;

        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ',');
        id = std::stoi(token);
        std::getline(ss, token, ',');
        std::stringstream name_ss(token);
        std::getline(name_ss, name, '"');
        std::getline(name_ss, name, '"');

        Client c(id, name);
        clients.push_back(c);
    }

    return clients;
}

void Client::writeClients(const std::vector<Client>& clients) {
    std::ofstream outfile("clients.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    for (const auto& c : clients) {
        outfile << c.getId() << ',';
        outfile << '"' << c.getName() << '"' << std::endl;
    }
}

void Client::displayClients(const std::vector<Client>& clients) {
    std::cout << "ID\tName" << std::endl;
    std::cout << "--\t----" << std::endl;
    for (const auto& c : clients) {
        std::cout << c.getId() << '\t' << c.getName() << std::endl;
    }
}

void Client::addClient(Client& client) {
    auto clients = readClients();
    int id = Client::getNextClientId();
    client.setId(id);
    clients.push_back(client);
    writeClients(clients);
}

void Client::updateClient(int id, const Client& client) {
    auto clients = readClients();
    for (auto& c : clients) {
        if (c.getId() == id) {
            c = client;
            break;
        }
    }
    writeClients(clients);
}

void Client::deleteClient(int clientId) {
    std::vector<Client> clients = readClients(); // Get all clients
    auto clientIt = std::find_if(clients.begin(), clients.end(), [clientId](const Client& c) { return c.getId() == clientId; }); // Find client to delete
    if (clientIt != clients.end()) {
        clients.erase(clientIt); // Remove client from vector
        writeClients(clients); // Write updated vector to file
        std::cout << "Client with ID " << clientId << " deleted successfully.\n";
    }
    else {
        std::cout << "Client with ID " << clientId << " not found.\n";
    }
}

Client Client::getClientById(int id) {
    auto clients = readClients();
    for (auto& c : clients) {
        if (c.getId() == id) {
            return c;
        }
    }

    throw std::runtime_error("Client not found");
}