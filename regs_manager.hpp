#ifndef REGISTERS_MANAGER_LIBRARY_HPP
#define REGISTERS_MANAGER_LIBRARY_HPP

#include<string>

using namespace std;

class RegisterManager{
    int count;
public:

    RegisterManager() {
        count=0;
    }

    string getReg() {
        count++;
        string ret="%var";
        return ret.append(to_string(count));
    }
};

#endif //REGISTERS_MANAGER_LIBRARY_HPP