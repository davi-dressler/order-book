#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "Order.hpp"
#include "Transaction.hpp"

struct Node {
    Order * order;
    Node * next;
};
struct TransactionNode {
    Transaction * transaction;
    TransactionNode * next;
};

class OrderBook {

private:
    Node * sellOrders;
    Node * buyOrders;
    TransactionNode * transactions;
    int size_buy;
    int size_sell;
    int size_transactions;

public:

    OrderBook();
    ~OrderBook();

    void insertTransaction(TransactionNode** newNode);
    void insert(Node** currentNode, Node** newNode);
    void nodeDelete(Node** prevNode, Node** currentNode);
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
