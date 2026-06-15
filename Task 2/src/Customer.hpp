#pragma once
#include "User.hpp"
#include "Cart.hpp"
#include "Product.hpp"
#include "Order.hpp"
#include <map>
#include <vector>
using namespace std;

class Customer : public User {
private:
    Cart cart;
    vector<Order> orderHistory;

    map<int, int> viewedProducts;
    map<int, int> purchasedProducts;

public:
    void browseProducts();
    void addToCart(Product& p, int qty);
    void checkout();

    void viewRecommendations();

    void menu() override;

    void setUsername(const string& value);
    const Cart& getCart() const;

    void setHistory(const map<int, int>& views, const map<int, int>& purchases);
    const map<int, int>& getViewedProducts() const;
    const map<int, int>& getPurchasedProducts() const;
};