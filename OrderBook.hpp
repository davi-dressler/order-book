#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "Order.hpp"
#include "Transaction.hpp"

struct Node {
    Order order;
    Node * next;
    // inicializador de order pq não podemos alterar a assinatura de submit
    Node(Order o) : order(o), next(nullptr){}
};

class OrderBook {

private:
    int size;
    Node * sellOrders;
    Node * buyOrders;

public:

    OrderBook();
    ~OrderBook();

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
