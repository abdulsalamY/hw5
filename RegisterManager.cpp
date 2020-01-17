//
// Created by abdul on 1/14/2020.
//

#include "RegisterManager.hpp"

int RegisterManager::count = 0;
int RegisterManager::global_count = 0;

string RegisterManager::getReg() {
    count++;
    string ret="%var";
    return ret.append(to_string(count));
}

string RegisterManager::getGlobal() {
    global_count++;
    string ret="@global";
    return ret.append(to_string(global_count));
}
