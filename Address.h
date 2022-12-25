//
// Created by Hope Crisafi on 12/16/22.
//

#ifndef UNTITLED2_ADDRESS_H
#define UNTITLED2_ADDRESS_H
#include <Python.h>
#include <string>
#include <unordered_map>


using namespace std;

int const CHARS_TO_IGNORE = 32767;

class Address {

private:
    string city_;
    string state_;
public:
    explicit Address(string city="", string state="");
    double get_distance(const Address& other);


};


#endif //UNTITLED2_ADDRESS_H
