//
// Created by abdul on 1/15/2020.
//

#ifndef HW5_LOCAL_VARS_HPP
#define HW5_LOCAL_VARS_HPP

#include "RegisterManager.hpp"
#include "parser.hpp"
#include "handler.hpp"
#include <string>

string init_local_vars_stack();

string get_var_as_reg_from_stack(string stack_pointer, int off_set);

void set_var(string stack_pointer, int off_set, int value);

void set_var_from_reg(string stack_pointer, int off_set, string reg_source);

#endif //HW5_LOCAL_VARS_HPP