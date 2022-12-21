//
// Created by Hope Crisafi on 12/16/22.
//

#ifndef UNTITLED2_ADDRESS_H
#define UNTITLED2_ADDRESS_H
#include <string>
#include <map>


using namespace std;

int const CHARS_TO_IGNORE = 32767;

class Address {

private:
    string city_;
    string state_;
public:
    explicit Address(string city="", string state="");
    string get_data();


};


#endif //UNTITLED2_ADDRESS_H
