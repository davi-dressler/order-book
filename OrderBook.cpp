#include "OrderBook.hpp"

OrderBook::OrderBook(){}

OrderBook::~OrderBook(){}

bool OrderBook::submit(Order order){}

bool OrderBook::cancel(int id){}

Order* OrderBook::getBuyOrders(int* n){}
Order* OrderBook::getSellOrders(int* n){}
Transaction* OrderBook::getTransactions(int* n){}

void OrderBook::printBuyOrders(){}
void OrderBook::printSellOrders(){}
void OrderBook::printTransactions(){}