//
// Created by abdul on 1/14/2020.
//

#ifndef HW5_BOOLMANAGER_HPP
#define HW5_BOOLMANAGER_HPP

#include "abstract_class.hpp"
#include "RegisterManager.hpp"

#define getReg() RegisterManager::getReg()
#define code_buffer CodeBuffer::instance()
#define makelist CodeBuffer::makelist

class BoolManager {
public:
    static BoolManager &instance();
    abstract_class* handleOr(const string& reg);
    string handleOrSecond(abstract_class*,string);
};


#endif //HW5_BOOLMANAGER_HPP
