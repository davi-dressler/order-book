#include "Order.hpp"
#include "Transaction.hpp"
#include "OrderBook.hpp"
#include <iostream>

using namespace std;

int main(){
    Order teste0(1, 'S', 1, 1);
    Order teste1(2, 'S', 1, 3);
    Order teste2(3, 'S', 1, 4);
    Order teste3(4, 'S', 1, 5);
    Order teste4(5, 'B', 5, 9);
    Order teste5(6, 'B', 2, 10);
    Order teste6(7, 'B', 2, 11);
    Order teste7(8, 'B', 2, 12);

    OrderBook orderBook;

    int n;
    orderBook.submit(teste0);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.submit(teste1);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.submit(teste2);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.cancel(2);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.submit(teste3);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.submit(teste4);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.submit(teste5);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.submit(teste6);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.submit(teste7);
    orderBook.printBuyOrders();
    orderBook.printSellOrders();
    orderBook.getBuyOrders(&n);
    
    

    
    return 0;

}
