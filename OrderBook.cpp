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
  this->size_transactions = 0;

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

OrderBook::~OrderBook(){
    // Libera lista de buyOrders
    Node* current = this->buyOrders;
    while(current != nullptr){
        Node* next = current->next;
        delete current->order;
        delete current;
        current = next;
    }

    // Libera lista de sellOrders
    current = this->sellOrders;
    while(current != nullptr){
        Node* next = current->next;
        delete current->order;
        delete current;
        current = next;
    }

    // Libera lista de transactions
    TransactionNode* currentTrans = this->transactions;
    while(currentTrans != nullptr){
        TransactionNode* next = currentTrans->next;
        delete currentTrans->transaction;
        delete currentTrans;
        currentTrans = next;
    }
}

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

  //Tratando a primeira inserção de uma ordem no sistema
  if(*currentNode == nullptr && *complementNode == nullptr){
    cout << "[Abertura de Ordem] A ordem ID " << order.getId() << " esta em aberto." << endl;
    (*currentNode) = newNode;
    (*currentNode)->next = nullptr;
    (*currentNode)->order = new Order(order);

    return false;
  } 
  
  else if(*currentNode != nullptr && *complementNode == nullptr){
    insert(currentNode, &newNode);

    cout << "[Abertura de Ordem] A ordem ID " << order.getId() << " esta em aberto." << endl;
    return false;
  }

  // executar venda instantanea aqui
  if(order.getType() == 'B'){
    do{
      if((*complementNode)->order->getPrice() <= newNode->order->getPrice()){//Procura uma ordem de venda com preço menor que a de compra que estamos inserindo
        cout << "[Execucao] A Ordem de compra com ID " << order.getId() << " foi executada." << endl;
        cout << "[Execucao] A Ordem de venda com ID " << (*complementNode)->order->getId() << " foi executada." << endl;

        //Cria a transação e atribui ela a um nó 
        Transaction* newTransaction = new Transaction(order.getId(), (*complementNode)->order->getId(), (*complementNode)->order->getPrice());
        TransactionNode* newTransactionNode = new TransactionNode;
        newTransactionNode->transaction = newTransaction;
        newTransactionNode->next = nullptr;
        this->size_transactions++;
        insertTransaction(&newTransactionNode);

        nodeDelete(prevNode, complementNode); //Deleta a ordem executada

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

        //Cria a transação e atribui ela a um nó 
        Transaction* newTransaction = new Transaction(order.getId(), (*complementNode)->order->getId(), (*complementNode)->order->getPrice());
        TransactionNode* newTransactionNode = new TransactionNode;
        newTransactionNode->transaction = newTransaction;
        newTransactionNode->next = nullptr;
        this->size_transactions++;
        insertTransaction(&newTransactionNode);

        nodeDelete(prevNode, complementNode); //Deleta a ordem executada

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

    return false;
  }

  insert(currentNode, &newNode);//Caso não seja executada e nem for um caso de inserção especial, a ordem é inserida normalmente ao sistema
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
      cout << "[Cancelamento] A Ordem de venda com ID " << id << " foi cancelada." << endl;
      size_sell--;
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
      cout << "[Cancelamento] A Ordem de venda com ID " << id << " foi cancelada." << endl;
      size_buy--;
      return true;
    }
    prevNode = currentNode;
    currentNode = &((*currentNode)->next);
  }
  return false;
}

Order* OrderBook::getBuyOrders(int* n){
  *n = this-> size_buy;
  Order* buy_array = new Order[*n];
  Node* atual_buy = buyOrders;
  int idx = 0;

  if(buyOrders == nullptr) return nullptr;

  cout << *n;
  while(atual_buy != nullptr){
    buy_array[idx] = *atual_buy->order;
    atual_buy = atual_buy -> next;
    idx++;
  }

  return buy_array; //Lembrar de implementar o destrutor no main
}

Order* OrderBook::getSellOrders(int* n){
  *n = this-> size_sell;
  Order* sell_array = new Order[*n];
  Node* atual_sell = sellOrders;
  int idx = 0;

  if(sellOrders == nullptr) return nullptr;

  while(atual_sell != nullptr){
    sell_array[idx] = *atual_sell->order;
    atual_sell = atual_sell -> next;
    idx++;
  }

  return sell_array; //Lembrar de implementar o destrutor no main
}

Transaction* OrderBook::getTransactions(int* n){
  *n = this-> size_transactions;
  Transaction* transaction_array = new Transaction[*n];
  TransactionNode* atual_transaction = transactions;
  int idx = 0;

  if(sellOrders == nullptr) return nullptr;

  while(atual_transaction != nullptr){
    transaction_array[idx] = *atual_transaction -> transaction;
    atual_transaction= atual_transaction -> next;
    idx++;
  }

  return transaction_array; //Lembrar de implementar o destrutor no main
}

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
