#include "handler.hpp"
#include "RegisterManager.hpp"
#include "bp.hpp"
#include <iostream>

string handle_operation(string r1, string r2, string op_char, bool is_int){
    string res = getReg();
    string bites = "i8";
    if(is_int){
        bites = "i32";
    }

    switch(op_char[0]){

        case('-'):
            code_buffer.emit(res + " = sub " + bites + " " + r1 + ", " + r2);
            break;

        case('+'):
            code_buffer.emit(res + " = add " + bites + " " + r1 + ", " + r2);
            break;

        case('*'):
            code_buffer.emit(res + " = mul " + bites + " " + r1 + ", " + r2);
            break;

        case('/'):
            code_buffer.emit(res + " = sdiv " + bites + " " + r1 + ", " + r2);
            break;

        default: code_buffer.emit("errrrorr!!! nayakat ya bahjat");
    }
    return res;
}

string init_reg_int(int num){

    string new_reg = getReg();
    code_buffer.emit(new_reg + " = add i32 0, " + to_string(num));
    return new_reg;
}

string init_reg_byte(int num){

    string new_reg = getReg();
    code_buffer.emit(new_reg + " = add i8 0, " + to_string(num));
    return new_reg;
}
