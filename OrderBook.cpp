#include "OrderBook.hpp"
#include "Order.hpp"
#include "Transaction.hpp"
#include <exception>
#include <iostream>

using namespace std;

OrderBook::OrderBook(){
  this->sellOrders = nullptr;
  this->buyOrders = nullptr;
  this->transactions = nullptr;
  this->size_sell = 0;
  this->size_buy = 0;

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

void OrderBook::insertTransaction(TransactionNode** newNode){
  (*newNode)->next = this->transactions;
  this->transactions = *newNode;
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
  Node** prevNode = nullptr;
  Node * newNode = new Node;
  newNode->order = new Order(order);



  if(order.getType() == 'B'){
    currentNode = &this->buyOrders;
    complementNode = &this->sellOrders;
    this->size_buy++;
  } 
  
  else if(order.getType() == 'S') {
    currentNode = &this->sellOrders;
    complementNode = &this->buyOrders;
    this->size_sell++;
  }

  // cout << "currentNode " << (*currentNode) << endl;
  // if((*currentNode)){
  //   cout << "next " << (*currentNode)->next << endl;
  // }
  // cout << "complementNode " << (*complementNode) << endl;
  // cout << endl;
  
  //Tratando a primeira inserção de uma ordem no sistema
  if(*currentNode == nullptr && *complementNode == nullptr){
    cout << "[Abertura de Ordem] A ordem ID " << order.getId() << " esta em aberto." << endl;
    (*currentNode) = newNode;
    (*currentNode)->next = nullptr;
    (*currentNode)->order = new Order(order);

    // cout << "Node: " << (*currentNode)->order->getId() << endl;
    // cout << endl;
    // cout << endl;

    return false;
  } 
  
  else if(*currentNode != nullptr && *complementNode == nullptr){
    insert(currentNode, &newNode);

    // printDebug(currentNode);
    cout << "[Abertura de Ordem] A ordem ID " << order.getId() << " esta em aberto." << endl;

    // cout << "Node: " << (*currentNode)->order->getId() << endl;
    // cout << endl;
    // cout << endl;

    return false;
  }

  // executar venda instantanea aqui
  if(order.getType() == 'B'){
    do{
      if((*complementNode)->order->getPrice() <= newNode->order->getPrice()){//Procura uma ordem de venda com preço menor que a de compra que estamos inserindo
        cout << "[Execucao] A Ordem de compra com ID " << order.getId() << " foi executada." << endl;
        cout << "[Execucao] A Ordem de venda com ID " << (*complementNode)->order->getId() << " foi executada." << endl;
        Transaction* newTransaction = new Transaction(order.getId(), (*complementNode)->order->getId(), (*complementNode)->order->getPrice());
        TransactionNode* newTransactionNode = new TransactionNode;
        newTransactionNode->transaction = newTransaction;
        newTransactionNode->next = nullptr;
        insertTransaction(&newTransactionNode);
        nodeDelete(prevNode, complementNode);
        this->size_sell--;
        this->size_buy--;
        return true; 
      }

      prevNode = complementNode;
      complementNode = &(*complementNode)->next; 
    }while((*complementNode)->next != nullptr);
  } 
  
  else if(order.getType() == 'S'){
    do{
      if((*complementNode)->order->getPrice() >= newNode->order->getPrice()){//Procura uma ordem de compra com preço maior que a de compra que estamos inserindo
        cout << "[Execucao] A Ordem de compra com ID " << (*complementNode)->order->getId() << " foi executada." << endl;
        cout << "[Execucao] A Ordem de venda com ID " << order.getId() << " foi executada." << endl;
        Transaction* newTransaction = new Transaction(order.getId(), (*complementNode)->order->getId(), (*complementNode)->order->getPrice());
        TransactionNode* newTransactionNode = new TransactionNode;
        newTransactionNode->transaction = newTransaction;
        newTransactionNode->next = nullptr;
        insertTransaction(&newTransactionNode);
        nodeDelete(prevNode, complementNode);
        this->size_sell--;
        this->size_buy--;
        return true; 

      }

      prevNode = complementNode;
      complementNode = &(*complementNode)->next; 
    }while((*complementNode)->next != nullptr);
  }
  //

  if(*currentNode == nullptr){
    (*currentNode) = newNode;
    (*currentNode)->next = nullptr;
    (*currentNode)->order = new Order(order);

    // printDebug(currentNode);

    return false;
  }

  insert(currentNode, &newNode);
  // printDebug(currentNode);
  
  return false;
}

void OrderBook::nodeDelete(Node** prevNode, Node** currentNode){
  if(currentNode == nullptr || *currentNode == nullptr) return;

  Node* temp = *currentNode;

  // Caso 1: removendo o primeiro nó
  if(prevNode == nullptr){
    *currentNode = temp->next;
  }
  // Caso 2: removendo nó no meio ou final
  else{
    (*prevNode)->next = temp->next;
  }

  delete temp->order;
  delete temp;
}
bool OrderBook::cancel(int id){
  Node** currentNode = &this->sellOrders;
  Node** prevNode = nullptr;

  while(*currentNode != nullptr) {
    if((*currentNode)->order->getId() == id){
      nodeDelete(prevNode, currentNode);
      return true;
    }
    prevNode = currentNode;
    currentNode = &((*currentNode)->next);
  }
  currentNode = &this->buyOrders;
  prevNode = nullptr;
  while(*currentNode != nullptr) {
    if((*currentNode)->order->getId() == id){
      nodeDelete(prevNode, currentNode);
      return true;
    }
    prevNode = currentNode;
    currentNode = &((*currentNode)->next);
  }
  return false;
}

//Não testada ainda
Order* OrderBook::getBuyOrders(int* n){
  *n = this-> size_buy;
  Order* buy_array = new Order[*n]; //Destrutor desse??
  Node* atual_buy = buyOrders;
  int idx = 0;

  if(buyOrders == nullptr) return nullptr;

  cout << *n;
  while(atual_buy != nullptr){
    buy_array[idx] = *atual_buy->order;
    atual_buy = atual_buy -> next;
    idx++;
  }

  return buy_array;
}

//Não testada ainda
Order* OrderBook::getSellOrders(int* n){
  *n = this-> size_buy;
  Order* sell_array = new Order[*n]; //Destrutor desse??
  Node* atual_sell = buyOrders;
  int idx = 0;

  if(buyOrders == nullptr) return nullptr;

  cout << *n;
  while(atual_sell != nullptr){
    sell_array[idx] = *atual_sell->order;
    atual_sell = atual_sell -> next;
    idx++;
  }

  return sell_array;
}

Transaction* OrderBook::getTransactions(int* n){return nullptr;}

void OrderBook::printBuyOrders(){
  Node* atual_buy = buyOrders;

  cout << endl;
  cout << "[ --- BuyOrders --- ]" << endl;

  while(atual_buy != nullptr){
    cout << "[" << atual_buy->order->getId() << " | " << atual_buy->order->getPrice() << " | " << atual_buy->order->getTimestamp() << "]" << endl;


    atual_buy = atual_buy -> next;
  }
}

void OrderBook::printSellOrders(){
  Node* atual_sell = sellOrders;

  cout << endl;
  cout << "[ --- SellOrders --- ]" << endl;

  while(atual_sell != nullptr){
    cout << "[" << atual_sell->order->getId() << " | " << atual_sell->order->getPrice() << " | " << atual_sell->order->getTimestamp() << "]" << endl;


    atual_sell = atual_sell -> next;
  }
}

void OrderBook::printTransactions(){
  TransactionNode* atual_transaction = transactions;

  cout << endl;
  cout << "[ --- Transactions --- ]" << endl;

  while(atual_transaction != nullptr){
    cout << "[" << atual_transaction->transaction->getBuyOrderId() << " | " <<
     atual_transaction->transaction->getSellOrderId() << " | " << atual_transaction->transaction->getExecutionPrice() << "]" << endl;


    atual_transaction = atual_transaction -> next;
  }
}
