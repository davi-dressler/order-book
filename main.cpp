#include "Order.hpp"
#include "Transaction.hpp"
#include "OrderBook.hpp"

int main(){
    Order teste(1, 'B', 1, 1);
    Order teste1(2, 'B', 1, 0);
    OrderBook orderBook;
    orderBook.submit(teste);
    
    return 0;

}
