# OrderBook System
Neste projeto, implementamos um sistema de negociação de um ativo financeiro. É possível registra ordens de compra e venda de uma ação e se as condições de compra/venda forem cumpridas as ordens são executadas e uma transação registra a negociação.

## Instruções de compilação
Certifique-se de ter um compilador c++ instalado. 
Para compilar o projeto, digite no terminal:

`g++ main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book`

## Instruções de execução
Após a compilação, execute: `.\order_book`

# Estruturação dos Dados
Para armazenar as ordens de compra, ordens de venda e transações, foram criadas listas encadeadas a partir das structs `Node` e `TransactionNode`.

A classe principal do nosso sistema, `OrderBook`, armazena as seguintes informações:

- `buyOrders`: Nó inicial da lista encadeada de ordens de compra.
- `sellOrders`: Nó inicial da lista encadeada de ordens de venda.
- `transactions`:  Nó inicial da lista encadeada de ordens de transações.
- `size_buy`: Número de ordens de compra em aberto.
- `size_sell`: Número de ordens de venda em aberto.
- `size_transactions`: Número de transações registradas.

Nosso sistema faz uso de duas outras classes: `Order`e `Transaction`.

A classe `Order` arazena as informações:
-`id`: Identificador único da ordem.
-`type`: "B" se buy/compra, "S" se sell/venda.
-`price`: Preço de negócio da ordem.
-`timestamp`: Registro utiizado para ordenar as ordens dentro do sistema.

A classe `Transaction` armazena as informações:
-`buy_order_id`: Identificador único da ordem de compra da transação.
-`sell_order_id`: Identificador único da ordem de venda da transação.
-`execution_price`: Preço de execução da negociação.

# Exemplo de execução

```cpp

OrderBook orderBook;

Order ordem0(1, 'S', 9, 1);
Order ordem1(2, 'S', 9, 3);
Order ordem2(3, 'S', 5, 4);
Order ordem3(4, 'B', 6, 5);

int n; 

orderBook.submit(teste0);  
orderBook.submit(teste1);
orderBook.submit(teste2);
orderBook.cancel(2)
orderBook.submit(teste3); //Executa uma transação com a ordem2

orderBook.printBuyOrders();    
orderBook.printSellOrders(); 
orderBook.printTransactions();

Order* arr = orderBook.getSellOrders(&n);

```
