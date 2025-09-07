//
// Created by arago on 06/09/2025.
//

#include "Customer.h"
#include <stdexcept>


Customer::Customer()
    : customerId(0), title(""), name(""), type("New"), purchaseNumbers({}) {}

Customer::Customer(int id, const std::string &t, const std::string &n, const std::string &ty, const std::vector<int> &purchases) {
    setId(id);
    setTitle(t);
    setName(n);
    setType(ty);
    setPurchases(purchases);
}


Customer::Customer(const Customer &other)
    : customerId(other.customerId),
      title(other.title),
      name(other.name),
      type(other.type),
      purchaseNumbers(other.purchaseNumbers) {}


Customer::~Customer() {

}


Customer& Customer::operator=(const Customer &other) {
    if (this != &other) {
        customerId = other.customerId;
        title = other.title;
        name = other.name;
        type = other.type;
        purchaseNumbers = other.purchaseNumbers;
    }
    return *this;
}


int Customer::getId() const { return customerId; }
std::string Customer::getTitle() const { return title; }
std::string Customer::getName() const { return name; }
std::string Customer::getType() const { return type; }
std::vector<int> Customer::getPurchases() const { return purchaseNumbers; }


void Customer::setId(int id) {
    if (id <= 0) throw std::invalid_argument("ID must be positive.");
    customerId = id;
}

void Customer::setTitle(const std::string &t) {
    if (t.empty()) throw std::invalid_argument("Title cannot be empty.");
    title = t;
}

void Customer::setName(const std::string &n) {
    if (n.empty()) throw std::invalid_argument("Name cannot be empty.");
    name = n;
}

void Customer::setType(const std::string &ty) {
    if (ty != "New" && ty != "Regular")
        throw std::invalid_argument("Type must be 'New' or 'Regular'.");
    type = ty;
}

void Customer::setPurchases(const std::vector<int> &purchases) {
    for (int p : purchases) {
        if (p <= 0) throw std::invalid_argument("Purchase numbers must be positive.");
    }
    purchaseNumbers = purchases;
}

//Overloaded Operators
bool Customer::operator==(const Customer &other) const {
    return customerId == other.customerId;
}

bool Customer::operator!=(const Customer &other) const {
    return !(*this == other);
}

// print customer
std::ostream& operator<<(std::ostream &os, const Customer &c) {
    os << "ID: " << c.customerId
       << " | Title: " << c.title
       << " | Name: " << c.name
       << " | Type: " << c.type
       << " | Purchases: ";
    for (size_t i = 0; i < c.purchaseNumbers.size(); i++) {
        os << c.purchaseNumbers[i];
        if (i != c.purchaseNumbers.size() - 1) os << ", ";
    }
    return os;
}

// read custome
std::istream& operator>>(std::istream &is, Customer &c) {
    int id;
    std::string t, n, ty;
    int purchaseCount;
    std::vector<int> purchases;

    std::cout << "Enter ID: ";
    is >> id;
    std::cout << "Enter Title: ";
    is >> t;
    std::cout << "Enter Name: ";
    is >> n;
    std::cout << "Enter Type (New/Regular): ";
    is >> ty;
    std::cout << "Enter number of purchases: ";
    is >> purchaseCount;

    purchases.clear();
    for (int i = 0; i < purchaseCount; i++) {
        int purchaseNum;
        std::cout << "Enter purchase number " << (i + 1) << ": ";
        is >> purchaseNum;
        purchases.push_back(purchaseNum);
    }

    c.setId(id);
    c.setTitle(t);
    c.setName(n);
    c.setType(ty);
    c.setPurchases(purchases);

    return is;
}
