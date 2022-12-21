//
// Created by Hope Crisafi on 12/16/22.
//

#include <Python/Python.h>
#include "ProfileDistanceFunctions.h"
#include "Address.h"

using namespace std;

Address::Address(string city, string state) :
        city_(std::move(city)),state_(std::move(state)){}


string Address::get_data() {

    return"";
}


