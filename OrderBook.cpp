#include "OrderBook.hpp"
#include "Order.hpp"
#include <iostream>

using namespace std;

OrderBook::OrderBook(){
  this->sellOrders = nullptr;
  this->buyOrders = nullptr;

}

void printDebug(Node** currentNode){
  while((*currentNode)->next != nullptr) {
    cout << "Node: " << (*currentNode)->order->getId() << " " <<
     "Timestemp: " << (*currentNode)->order->getTimestamp() << endl;
    currentNode = &(*currentNode)->next;
  }
  cout << "Node: " << (*currentNode)->order->getId() << " " <<
  "Timestemp: " << (*currentNode)->order->getTimestamp() << endl;

  cout << endl;
  cout << endl;
  
}

void OrderBook::insert(Node** currentNode, Node** newNode){
  if((*currentNode)->next == nullptr || (*newNode)->order->getTimestamp() > (*currentNode)->order->getTimestamp()){
    (*newNode)->next = (*currentNode);
    *currentNode = *newNode;
    return;
  }
  Node** prevNode = nullptr;
  while((*currentNode) != nullptr){
    if(prevNode != nullptr && (*newNode)->order->getTimestamp() > (*currentNode)->order->getTimestamp()){
      (*newNode)->next = (*currentNode);
      (*prevNode)->next = (*newNode);
      return;
    }

    prevNode = currentNode;
    currentNode = &(*currentNode)->next;
  }
}

OrderBook::~OrderBook(){}

// talvez compense mais criar funções auxiliares de adição de node TALVEZ
bool OrderBook::submit(Order order){
  Node** currentNode;
  Node** complementNode;
  Node** prevNode;
  Node * newNode = new Node;
  newNode->order = new Order(order);



  if(order.getType() == 'B'){
    currentNode = &this->buyOrders;
    complementNode = &this->sellOrders;
  } else if(order.getType() == 'S') {
    currentNode = &this->sellOrders;
    complementNode = &this->buyOrders;
  }

  cout << "currentNode " << (*currentNode) << endl;
  if((*currentNode)){
    cout << "next " << (*currentNode)->next << endl;
  }
  cout << "complementNode " << (*complementNode) << endl;
  cout << endl;
  
  if(*currentNode == nullptr && *complementNode == nullptr){
    cout << "primeira inserção" << endl;
    (*currentNode) = newNode;
    (*currentNode)->next = nullptr;
    (*currentNode)->order = new Order(order);

    cout << "Node: " << (*currentNode)->order->getId() << endl;
    cout << endl;
    cout << endl;

    return false;
  } else if(*currentNode != nullptr && *complementNode == nullptr){
    insert(currentNode, &newNode);

    printDebug(currentNode);

    cout << "Node: " << (*currentNode)->order->getId() << endl;
    cout << endl;
    cout << endl;

    return false;
  }

  // executar venda instantanea aqui
  if(order.getType() == 'B'){
    do{
      if((*complementNode)->order->getPrice() <= newNode->order->getPrice()){
        //cancela
        cout << "ordem com id " << (*complementNode)->order->getId() << " apagada" << endl;
        return true; 
      }
      complementNode = &(*complementNode)->next;
    }while((*complementNode)->next != nullptr);
  } else if((*currentNode)->order->getType() == 'S'){
    do{
      if((*complementNode)->order->getPrice() >= newNode->order->getPrice()){
        //cancela
        cout << "ordem com id " << (*complementNode)->order->getId() << " apagada" << endl;
        return true; 
      }

      complementNode = &(*complementNode)->next;
    }while((*complementNode)->next != nullptr);
  }
  //

  if(*currentNode == nullptr){
    (*currentNode) = newNode;
    (*currentNode)->next = nullptr;
    (*currentNode)->order = new Order(order);

    printDebug(currentNode);

    return false;
  }
  insert(currentNode, &newNode);
  printDebug(currentNode);
  
  return false;
}

bool OrderBook::cancel(int id){return false;}

Order* OrderBook::getBuyOrders(int* n){return nullptr;}
Order* OrderBook::getSellOrders(int* n){return nullptr;}
Transaction* OrderBook::getTransactions(int* n){return nullptr;}

void OrderBook::printBuyOrders(){}
void OrderBook::printSellOrders(){}
void OrderBook::printTransactions(){}
