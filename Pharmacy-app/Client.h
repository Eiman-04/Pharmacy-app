#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

class Client {
private:
    int id_;
    std::string name_;

public:
    Client() {};
    Client(int id, const std::string& name);

    int getId() const;
    void setId(int id);

    std::string getName() const;
    void setName(const std::string& name);

    static std::vector<Client> readClients();
    static void writeClients(const std::vector<Client>& clients);
    static void displayClients(const std::vector<Client>& clients);
    static void addClient(Client& client);
    static void updateClient(int id, const Client& client);
    static void deleteClient(int id);
    static Client getClientById(int id);

    static int getNextClientId() {
        std::ifstream inputFile("clients.txt");
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