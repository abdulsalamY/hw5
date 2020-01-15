//
// Created by abdul on 1/14/2020.
//

#ifndef HW5_BOOLMANAGER_HPP
#define HW5_BOOLMANAGER_HPP

#include "abstract_class.hpp"
#include "RegisterManager.hpp"
#include "parser.hpp"
#include <unordered_map>

#define getReg() RegisterManager::getReg()
#define code_buffer CodeBuffer::instance()
#define makelist CodeBuffer::makelist

using std::unordered_map;
class BoolManager {
    unordered_map<string, string> op_translate;
public:
    BoolManager(){
        op_translate["=="] = "eq";
        op_translate["!="] = "ne";
        op_translate["<="] = "sle";
        op_translate["<"] = "slt";
        op_translate[">="] = "sge";
        op_translate[">"] = "sgt";

    }
    static BoolManager &instance();
    abstract_class* handleOr(const string& reg);
    string handleOrSecond(abstract_class*,string);
    abstract_class* handleAnd(const string& reg);
    string handleAndSecond(abstract_class*,string);
    string handleRelational(string token, string reg1, string reg2,TypeID reg1_type, TypeID reg2_type);
};


#endif //HW5_BOOLMANAGER_HPP
