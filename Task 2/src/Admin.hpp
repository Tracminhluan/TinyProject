#pragma once
#include "User.hpp"
#include <vector>
using namespace std;

class Admin : public User {
public:
/*
The administrator can manage products (such as adding, editing, deleting products) 
and view system statistics (most viewed products, best-selling products, and active users)
*/
    void addProduct();
    void editProduct();
    void deleteProduct();
    void viewStatistics();

    void menu() override;
};