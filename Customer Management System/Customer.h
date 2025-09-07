//
// Created by arago on 06/09/2025.
//

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>

class Customer {
private:
    int customerId;
    std::string title;
    std::string name;
    std::string type; // "New" or "Regular"
    std::vector<int> purchaseNumbers;

public:

    Customer();
    Customer(int id, const std::string &t, const std::string &n, const std::string &ty, const std::vector<int> &purchases);


    Customer(const Customer &other);


    ~Customer();

    Customer& operator=(const Customer &other);

    int getId() const;
    std::string getTitle() const;
    std::string getName() const;
    std::string getType() const;
    std::vector<int> getPurchases() const;

    void setId(int id);
    void setTitle(const std::string &t);
    void setName(const std::string &n);
    void setType(const std::string &ty);
    void setPurchases(const std::vector<int> &purchases);

    bool operator==(const Customer &other) const;
    bool operator!=(const Customer &other) const;

    friend std::ostream& operator<<(std::ostream &os, const Customer &c);
    friend std::istream& operator>>(std::istream &is, Customer &c);
};

#endif
