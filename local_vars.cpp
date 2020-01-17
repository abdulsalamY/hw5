//
// Created by t-nakara on 1/14/2020.
//

#include "local_vars.hpp"

string init_local_vars_stack(){
    string stack_ptr = getReg();
    code_buffer.emit("entry:");
    code_buffer.emit(stack_ptr + " = alloca [50 x i32]");
    return stack_ptr;
}

string get_var_as_reg_from_stack(string stack_pointer, int off_set, TypeID type){

    string var_ptr = getReg();
    string var = getReg();
    string casted_var = getReg();
    code_buffer.emit(var_ptr + "= getelementptr [50 x i32],[50 x i32]* "+ stack_pointer +", i32 0 , i32 " + to_string(off_set));
    code_buffer.emit(var +  " = load i32, i32* "+ var_ptr );
    if (type == INTTYPE || type == ENUMTYPE) {
        return var;
    }
    else if (type == BYTETYPE) {
        code_buffer.emit(casted_var + " = trunc i32 " + var + " to i8");
    }
    else if (type == BOOLTYPE) {
        code_buffer.emit(casted_var + " = trunc i32 " + var + " to i1");
    }
    else if (type == STRINGTYPE) {
        code_buffer.emit(casted_var + " = trunc i32 " + var + " to i8*");
    }

    return casted_var;
}

void set_var(string stack_pointer, int off_set, int value){

    string var_ptr = getReg();
    code_buffer.emit(var_ptr + "= getelementptr [50 x i32],[50 x i32]* "+ stack_pointer +", i32 0 , i32 " + to_string(off_set));
    code_buffer.emit("store i32 "+ to_string(value) +", i32* " + var_ptr );
}

void set_var_from_reg(string stack_pointer, int off_set, string reg_source, TypeID type) {

    string var_ptr = getReg();
    string source_i32_reg = getReg();
    if (type == INTTYPE) {
        source_i32_reg = reg_source;
    }
    else if (type == BYTETYPE) {
        code_buffer.emit(source_i32_reg + " = zext i8 " + reg_source + " to i32");
    }
    else if (type == BOOLTYPE) {
        code_buffer.emit(source_i32_reg + " = zext i1 " + reg_source + " to i32");
    }

    code_buffer.emit(var_ptr + "= getelementptr [50 x i32],[50 x i32]* " + stack_pointer + ", i32 0 , i32 " + to_string(off_set));
    code_buffer.emit("store i32 " + source_i32_reg + ", i32* " + var_ptr);
}

