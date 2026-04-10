#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "Order.hpp"
#include "Transaction.hpp"

struct Node {
    Order * order;
    Node * next;
};

class OrderBook {

private:
    Node * sellOrders;
    Node * buyOrders;
    int size_buy;
    int size_sell;

public:

    OrderBook();
    ~OrderBook();

    void insert(Node** currentNode, Node** newNode);
    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
};

#endif
