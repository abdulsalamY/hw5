//
// Created by abdul on 1/17/2020.
//

#ifndef HW5_FUNCTIONMANAGER_HPP
#define HW5_FUNCTIONMANAGER_HPP

#include "abstract_class.hpp"
#include "RegisterManager.hpp"
#include "parser.hpp"
#include <unordered_map>


#define getReg() RegisterManager::getReg()
#define code_buffer CodeBuffer::instance()
#define makelist CodeBuffer::makelist

class FunctionManager {
public:
    FuncID function;
    explicit FunctionManager(FuncID func);
    string handle_call(string function_name, TypeID ret_type);
    string handle_call(string function_name, TypeID ret_type, ExpList* exp_list);
};


#endif //HW5_FUNCTIONMANAGER_HPP
