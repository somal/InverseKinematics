#include "Connection.h"
#include "iostream"

using namespace std;


int Connection::open() {}

int Connection::close() {}

int Connection::send(std::vector<unsigned char> &data) {
    if (data.size() != 12) {
        throw std::invalid_argument("Data should defined by 12 bytes");
    }
    this->data = data;
}

int Connection::receive(std::vector<unsigned char> &data) {
    data = this->data;
}



