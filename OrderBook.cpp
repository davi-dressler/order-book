#include "OrderBook.hpp"
#include "Order.hpp"
#include <iostream>

using namespace std;

OrderBook::OrderBook(){
  this->buySize = 0;
  this->sellSize = 0;
  this->sellOrders = nullptr;
  this->buyOrders = nullptr;

}

void OrderBook::insert(Node* currentNode, Node* newNode){
  Node * prevNode;
  // Isso é muito confuso mas não tem jeito mt melhor
  // Essa parte aparenta funcionar mas precisa ser testada
  while(currentNode->next != nullptr){
    prevNode = currentNode;
    currentNode = currentNode->next;

    // Garantindo a ordenação
    if(currentNode->order->getTimestamp() < newNode->order->getTimestamp()){
      prevNode->next = newNode;
      newNode->next = currentNode;
      return;
    }
  }
  cout << "Inserindo " << newNode->order->getId() << endl;
  cout << "Em " << currentNode->order->getId() << endl;
  cout << endl;
  currentNode->next = newNode;
  
  if(newNode->order->getType() == 'B'){
    this->buySize += 1;
  } else {
    this->sellSize += 1;
  } 
}

OrderBook::~OrderBook(){}

// talvez compense mais criar funções auxiliares de adição de node TALVEZ
bool OrderBook::submit(Order order){
  Node** currentNode;
  Node** complementNode;
  Node * prevNode;
  Node * newNode = new Node;
  newNode->order = new Order(order);


  cout << "Sell " << this->sellOrders << endl;
  cout << "Buy " << this->buyOrders << endl;
  cout << endl;

  if(order.getType() == 'B'){
    currentNode = &this->buyOrders;
    complementNode = &this->sellOrders;
  } else if(order.getType() == 'S') {
    currentNode = &this->sellOrders;
    complementNode = &this->buyOrders;
  }

  cout << "currentNode " << currentNode << endl;
  cout << "complementNode " << complementNode << endl;
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
    insert(*currentNode, newNode);

    while((*currentNode)->next != nullptr) {
      cout << "Node: " << (*currentNode)->order->getId() << endl;
      currentNode = &(*currentNode)->next;
    }

    cout << "Node: " << (*currentNode)->order->getId() << endl;
    cout << endl;
    cout << endl;

    return false;
  }

  // TODO: transformar em função
  // if(order.getType() == 'B'){
  //   float lesserPrice = (*complementNode)->order->getPrice(); // essa linha tá dando segfault
  //   Node * prevLesserPrice = nullptr;
  //   Node * lesserPriceNode = *currentNode;
  //   // checa menor preço e se existe um preço que valha a pena
  //   while((*complementNode)->next != nullptr){
  //     float currentPrice = (*complementNode)->order->getPrice();
  //     if(currentPrice < lesserPrice){
  //       lesserPrice = currentPrice;
  //       lesserPriceNode = *complementNode;
  //       prevLesserPrice = prevNode;
  //     }
  //     prevNode = *complementNode;
  //     *complementNode = (*complementNode)->next;
  //   }

  //   // se existe um ou mais preços adequados executa a transação aqui
  //   cout << "menor " << lesserPrice << endl;
  //   cout << "ordem " << order.getPrice() << endl;
  //   // if(lesserPrice <= order.getPrice()){
  //   //   prevLesserPrice->next = lesserPriceNode->next;
  //   //   // nessa linha executarei a transação //
  //   //   // delete lesserPriceNode;
  //   //   return true;
  //   // }
  // }
  // else {
  //   while((*complementNode)->next != nullptr){
  //     break;
  //   }
  // }

  cout << "Erro misterioso" << endl;
  insert(*currentNode, newNode);
  while((*currentNode)->next != nullptr) {
    cout << "Node: " << (*currentNode)->order->getId() << endl;
    currentNode = &(*currentNode)->next;
  }
  cout << "Node: " << (*currentNode)->order->getId() << endl;
  cout << endl;
  cout << endl;
  
  return false;
}

bool OrderBook::cancel(int id){return false;}

Order* OrderBook::getBuyOrders(int* n){return nullptr;}
Order* OrderBook::getSellOrders(int* n){return nullptr;}
Transaction* OrderBook::getTransactions(int* n){return nullptr;}

void OrderBook::printBuyOrders(){}
void OrderBook::printSellOrders(){}
void OrderBook::printTransactions(){}
