#include "Order.hpp"

Order::Order() {
    this->id = 0;
    this->type = ' ';
    this->price = 0.0f;
    this->timestamp = 0;
}

Order::Order(int id, char type, float price, int timestamp){
    this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
}

Order::~Order(){}

int Order::getId(){
    return id;
}

char Order::getType(){
    return type;
}

float Order::getPrice(){
    return price;
}

int Order::getTimestamp(){
    return timestamp;
}
