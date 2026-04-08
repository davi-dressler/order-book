#include "Order.hpp"
#include "Transaction.hpp"
#include "OrderBook.hpp"
#include <iostream>

using namespace std;

int main(){
    Order teste0(1, 'S', 1, 1);
    Order teste1(2, 'S', 1, 0);
    Order teste2(3, 'S', 1, 0);
    Order teste3(4, 'S', 1, 0);
    Order teste4(5, 'B', 1, 0);

    OrderBook orderBook;

    orderBook.submit(teste0);
    orderBook.submit(teste1);
    orderBook.submit(teste2);
    orderBook.submit(teste3);
    orderBook.submit(teste4);
    
    return 0;

}
