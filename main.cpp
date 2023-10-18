#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

static int current_PnL = 0;
static int n_of_trades = 0;

struct Stock {
    string name;
    int price;
    int quantity;
    char order;
};

void trade_decision(vector<Stock>& stocks, Stock s){
    int trading = 0;
    if (stocks.empty() && s.order == 's'){ // Initial Trade of stock (First time buying)
            stocks.push_back(s);
            current_PnL -= s.price;
            trading = 1;
            n_of_trades++;
    }else{
        for (int i = 0; i < stocks.size(); ++i){
            if (stocks[i].name != s.name && s.order=='s' && i == stocks.size() - 1){ // Initial Trade of new stock (We are buying)
                stocks.push_back(s);
                current_PnL -= s.price;
                trading = 1;
                n_of_trades++;
            }
            else if (stocks[i].name == s.name && stocks[i].price > s.price && stocks[i].order == s.order && s.order == 's'){ // Case we buy more at cheaper price
                stocks[i].price = s.price;
                stocks[i].quantity++; 
                current_PnL -= s.price;
                trading = 1;
                n_of_trades++;
            }
            else if (stocks[i].name == s.name && stocks[i].price < s.price && stocks[i].order == 's'  && s.order == 'b'){ // Case we sell to make profit
                if (stocks[i].quantity == 1){
                    stocks.erase(stocks.begin() + i); 
                }else{
                    stocks[i].quantity--; 
                }
                current_PnL += s.price;
                trading = 1;
                n_of_trades++;
            }
        }
    }

    cout << (trading == 0 ? "No Trade" : (s.name + " " + to_string(s.price) + " " +s.order)) << endl;

}


int main() {
    vector<Stock> stocks;

    string line;
    while (getline(cin, line)) {
        if (line.back() == '#') {
            istringstream ss(line);

            Stock stock;
            ss >> stock.name >> stock.price >> stock.order;
            stock.quantity = 0;

            trade_decision(stocks, stock);
        }
    }
    cout << "After " << to_string(n_of_trades) << " trades : " << to_string(current_PnL) << endl;
    return 0;

}

