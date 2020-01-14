#ifndef ARITHMETIC_LIBRARY_HPP
#define ARITHMETIC_LIBRARY_HPP

#include "RegisterManager.hpp"
#include "parser.hpp"
#include <string>

#define getReg() RegisterManager::getReg()
#define code_buffer CodeBuffer::instance()

string handle_operation(string r1, string r2, string op_char, bool is_int);

/// creates a new register with type
string init_exp(Exp* id);

string init_reg_int(int num);

string init_reg_byte(int num);

#endif //ARITHMETIC_LIBRARY_HPP
