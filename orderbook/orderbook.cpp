#include <iostream>
#include <queue>
#include <cstdint>
#include <algorithm>
#define SELL true
#define BUY false

using namespace std;

struct Order {
    int64_t user_id;
    int64_t amount;
    float price;
    bool side;
    bool operator<(const Order& rhs) const {
        if(rhs.side == BUY) {
            return price < rhs.price;
            }
        else{
            return price > rhs.price;
            }
    }
};

void transaction(Order& top_sell, Order& top_buy) {
    float total;
    int quantity = min(top_sell.amount, top_buy.amount);
    total = top_sell.price * quantity;
    cout << "BalanceChange{" << top_sell.user_id << ";" << total << ";" << "USD" << "}" << '\n';
    cout << "BalanceChange{" << top_buy.user_id << ";" << total*(-1) << ";" << "USD" << "}" << '\n';
    top_sell.amount -= quantity;
    top_buy.amount -= quantity;
}

int main() {

    priority_queue<Order> buy;
    priority_queue<Order> sell;

    int64_t user_id_in;
    int64_t amount_in;
    float price_in;
    string string_side_in;


     while (cin >> user_id_in >> amount_in >> price_in >> string_side_in) {
        bool side_in;
        if (string_side_in == "SELL") {
            side_in = SELL;
            sell.push(Order{user_id_in, amount_in, price_in, side_in});
        } else if (string_side_in == "BUY") {
            side_in = BUY;
            buy.push(Order{user_id_in, amount_in, price_in, side_in});
        } else {
            cerr << "ERROR"<< '\n';
            continue;         
        }
        while(!buy.empty() && !sell.empty() && (sell.top().price <= buy.top().price)) {
                Order top_sell = sell.top();
                Order top_buy = buy.top();
                sell.pop();
                buy.pop();
                transaction(top_sell, top_buy);                
                if(top_sell.amount > 0)
                    sell.push(top_sell);
                if(top_buy.amount > 0)
                    buy.push(top_buy);    
            }
   }


    return 0;
}