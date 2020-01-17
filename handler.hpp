//
// Created by abdul on 1/15/2020.
//

#ifndef HW5_HANDLER_HPP
#define HW5_HANDLER_HPP

#include "RegisterManager.hpp"
#include "parser.hpp"
#include <string>

#define getReg() RegisterManager::getReg()
#define getGlobal() RegisterManager::getGlobal()
#define code_buffer CodeBuffer::instance()


string handle_operation(string r1, string r2, string op_char, TypeID reg1_type, TypeID reg2_type);

string init_reg_int(int num);

string init_reg_byte(int num);

string init_reg_bool(bool value);

string init_reg_enum(int enum_id);

string init_reg_string(const string& value);

string init_reg_not(string reg);

int handle_bool_exp_jump(Exp exp);
#endif //HW5_HANDLER_HPP
