#include <string>
#include <vector>

class Sale {
private:
    int id;
    int productId;
    int clientId;
    std::string productName;
    std::string clientName;
    int quantity;
    float price;
    std::string date;
public:
    Sale(int id, int productId, int clientId, const std::string& productName, const std::string& clientName, int quantity, float price, const std::string& date);
    static void createSale();
    static std::vector<Sale> readSales();
    static void writeSale(const Sale& sale);
    static void displaySales();
    static int getNextSaleId();
    static std::string getCurrentDateTime();
};
