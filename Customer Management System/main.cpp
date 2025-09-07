#include <iostream>
#include <vector>
#include <algorithm>
#include "Customer.h"





#include <fstream>
#include <sstream>


void saveToFile(const std::vector<Customer> &customers, const std::string &filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto &c : customers) {
        outFile << c.getId() << ";"
                << c.getTitle() << ";"
                << c.getName() << ";"
                << c.getType() << ";";

        std::vector<int> purchases = c.getPurchases();
        outFile << purchases.size();

        for (int p : purchases) {
            outFile << ";" << p;
        }
        outFile << "\n";
    }
    outFile.close();
    std::cout << "Customers saved to " << filename << "\n";
}


void loadFromFile(std::vector<Customer> &customers, const std::string &filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "No existing customer file found.\n";
        return;
    }

    customers.clear();
    std::string line;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string token;

        int id;
        std::string title, name, type;
        int purchaseCount;
        std::vector<int> purchases;

        std::getline(ss, token, ';');
        id = std::stoi(token);

        std::getline(ss, title, ';');
        std::getline(ss, name, ';');
        std::getline(ss, type, ';');

        std::getline(ss, token, ';');
        purchaseCount = std::stoi(token);

        purchases.clear();
        for (int i = 0; i < purchaseCount; i++) {
            if (std::getline(ss, token, ';')) {
                purchases.push_back(std::stoi(token));
            }
        }

        Customer c(id, title, name, type, purchases);
        customers.push_back(c);
    }

    inFile.close();
    std::cout << "Customers loaded from " << filename << "\n";
}








void displayMenu() {
    std::cout << "\n=== Customer Management System ===\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. Display All Customers\n";
    std::cout << "3. Find Customer by ID\n";
    std::cout << "4. Find Customer by Purchase Number\n";
    std::cout << "5. Load Customers from File\n";
    std::cout << "6. Save Customers to File\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    std::vector<Customer> customers;
    int choice;


    loadFromFile(customers, "customers.txt");


    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Customer c;
                std::cin >> c;  // use overloaded >> operator
                customers.push_back(c);
                std::cout << "Customer added successfully!\n";
                break;
            }

            case 2: {
                if (customers.empty()) {
                    std::cout << "No customers available.\n";
                    break;
                }

                int subChoice;
                std::cout << "\n--- Display Options ---\n";
                std::cout << "1. By Name (Alphabetical)\n";
                std::cout << "2. By Type (New/Regular)\n";
                std::cout << "Choose an option: ";
                std::cin >> subChoice;

                if (subChoice == 1) {
                    std::vector<Customer> sorted = customers;
                    std::sort(sorted.begin(), sorted.end(),
                              [](const Customer &a, const Customer &b) {
                                  return a.getName() < b.getName();
                              });

                    std::cout << "\n--- Customers Sorted by Name ---\n";
                    for (const auto &c : sorted) {
                        std::cout << c << "\n";
                    }

                } else if (subChoice == 2) {
                    std::string filterType;
                    std::cout << "Enter type (New/Regular): ";
                    std::cin >> filterType;

                    std::cout << "\n--- Customers of type: " << filterType << " ---\n";
                    for (const auto &c : customers) {
                        if (c.getType() == filterType) {
                            std::cout << c << "\n";
                        }
                    }
                } else {
                    std::cout << "Invalid option.\n";
                }
                break;
            }


            case 3: {
                int id;
                std::cout << "Enter customer ID: ";
                std::cin >> id;

                auto it = std::find_if(customers.begin(), customers.end(),
                                       [id](const Customer &c) { return c.getId() == id; });

                if (it != customers.end()) {
                    std::cout << "Customer found: " << *it << "\n";
                } else {
                    std::cout << "Customer not found.\n";
                }
                break;
            }

            case 4: {
                int purchaseNum;
                std::cout << "Enter purchase number: ";
                std::cin >> purchaseNum;

                bool found = false;
                for (const auto &c : customers) {
                    auto purchases = c.getPurchases();
                    if (std::find(purchases.begin(), purchases.end(), purchaseNum) != purchases.end()) {
                        std::cout << "Customer found: " << c << "\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    std::cout << "No customer found with that purchase number.\n";
                }
                break;
            }

            case 5: {
                loadFromFile(customers, "customers.txt");
                break;
            }

            case 6: {
                saveToFile(customers, "customers.txt");
                break;
            }

            case 0: {
                saveToFile(customers, "customers.txt");
                std::cout << "Exiting... Goodbye!\n";
                break;
            }

            default:
                std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
