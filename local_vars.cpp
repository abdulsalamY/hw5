//
// Created by t-nakara on 1/14/2020.
//

#include "local_vars.hpp"

string init_local_vars_stack(){
    string stack_ptr = getReg();
    code_buffer.emit(stack_ptr + " = alloca [50 x i32]");
    return stack_ptr;
}

string get_var_as_reg_from_stack(string stack_pointer, int off_set){

    string var_ptr = getReg();
    string var = getReg();
    code_buffer.emit(var_ptr + "= getelementptr [50 x i32],[50 x i32]* "+ stack_pointer +", i32 0 , i32 " + to_string(off_set));
    code_buffer.emit(var +  " = load i32, i32* "+ var_ptr );
    return var;
}

void set_var(string stack_pointer, int off_set, int value){

    string var_ptr = getReg();
    code_buffer.emit(var_ptr + "= getelementptr [50 x i32],[50 x i32]* "+ stack_pointer +", i32 0 , i32 " + to_string(off_set));
    code_buffer.emit("store i32 "+ to_string(value) +", i32* " + var_ptr );
}

void set_var_from_reg(string stack_pointer, int off_set, string reg_source){

    string var_ptr = getReg();
    code_buffer.emit(var_ptr + "= getelementptr [50 x i32],[50 x i32]* "+ stack_pointer +", i32 0 , i32 " + to_string(off_set));
    code_buffer.emit("store i32 "+ reg_source +", i32* " + var_ptr );
}

