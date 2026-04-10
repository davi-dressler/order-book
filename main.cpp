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
    Order teste5(6, 'B', 2, 90);

    OrderBook orderBook;

    orderBook.submit(teste0);
    orderBook.submit(teste1);
    orderBook.submit(teste2);
    orderBook.cancel(2);
    orderBook.submit(teste3);
    orderBook.submit(teste4);
    orderBook.cancel(2);
    orderBook.submit(teste5);
    orderBook.cancel(2);

    
    return 0;

}
