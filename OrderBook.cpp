#include "OrderBook.hpp"
#include "Order.hpp"
#include <iostream>

using namespace std;

OrderBook::OrderBook(){
  this->size = 0;
}

OrderBook::~OrderBook(){}

bool OrderBook::submit(Order order){
  Node * currentNode;
  Node * complementNode;
  if(order.getType() == 'B'){
    currentNode = this->buyOrders;
    complementNode = this->sellOrders;
  } else {
    currentNode = this->sellOrders;
    complementNode = this->buyOrders;
  }

  // while(complementNode->next != nullptr){
  //   if(complementNode)
  // }
  
  // inicializa a fila caso ela não exista ainda  
  // eu provavelmente preciso checar se ela foi inicializada quando checar se a ordem
  // pode ser executada imediatamente
  if(this->size == 0){
    currentNode = new Node(order);
    currentNode->next = nullptr;
    return false;
  }

  Node * prevNode;
  Node * newNode = new Node(order);
  newNode->order = order;

  // Isso é muito confuso mas não tem jeito mt melhor
  while(currentNode->next != nullptr){
    prevNode = currentNode;
    currentNode = currentNode->next;

    // Garantindo a ordenação
    if(currentNode->order.getTimestamp() < order.getTimestamp()){
      prevNode->next = newNode;
      newNode->next = currentNode;
    }
  }
  return false;
}

bool OrderBook::cancel(int id){}

Order* OrderBook::getBuyOrders(int* n){}
Order* OrderBook::getSellOrders(int* n){}
Transaction* OrderBook::getTransactions(int* n){}

void OrderBook::printBuyOrders(){}
void OrderBook::printSellOrders(){}
void OrderBook::printTransactions(){}
