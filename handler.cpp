//
// Created by abdul on 1/15/2020.
//

#include "handler.hpp"
#include "RegisterManager.hpp"
#include "bp.hpp"
#include <iostream>
#include <assert.h>

string handle_operation(string r1, string r2, string op_char, TypeID reg1_type, TypeID reg2_type){
    string type = "i32";
    if(reg1_type == BYTETYPE && reg2_type == BYTETYPE){
        type = "i8";
    }
    if(type == "i32"){
        if(reg1_type == BYTETYPE){
            string new_reg = getReg();
            code_buffer.emit(new_reg + " = zext i8 " + r1 + " to i32");
            r1 = new_reg;
        }
        if(reg2_type == BYTETYPE){
            string new_reg = getReg();
            code_buffer.emit(new_reg + " = zext i8 " + r2 + " to i32");
            r2 = new_reg;
        }
    }
    string res = getReg();
    switch(op_char[0]){

        case('-'): {
            code_buffer.emit(res + " = sub " + type + " " + r1 + ", " + r2);
            break;
        }
        case('+'): {
            code_buffer.emit(res + " = add " + type + " " + r1 + ", " + r2);
            break;
        }
        case('*'): {
            code_buffer.emit(res + " = mul " + type + " " + r1 + ", " + r2);
            break;
        }
        case('/'): {
            string is_zero_reg = getReg();
            code_buffer.emit(is_zero_reg + " = icmp eq " + type + " 0 , " + r2);
            int location = code_buffer.emit("br i1 " + is_zero_reg + " , label @, label @");
            string error_label = code_buffer.genLabel();
            code_buffer.emit("call void @error_division_by_zero()");
            int stam_location = code_buffer.emit("br label @");
            string continue_label = code_buffer.genLabel();
            code_buffer.emit(res + " = sdiv " + type + " " + r1 + ", " + r2);
            code_buffer.bpatch(code_buffer.makelist({location, SECOND}), continue_label);
            code_buffer.bpatch(code_buffer.makelist({location, FIRST}), error_label);
            code_buffer.bpatch(code_buffer.makelist({stam_location, FIRST}), continue_label);
            break;
            }

        default:
            code_buffer.emit("errrrorr!!! nayakat ya bahjat");
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

string init_reg_bool(bool value){
    string new_reg = getReg();
    if( value ){
        code_buffer.emit(new_reg + " = add i1 0, 1");
    }else{
        code_buffer.emit(new_reg + " = add i1 0, 0");
    }
    return new_reg;
}

string init_reg_not(string reg){

    //assert(reg != "");
    string new_reg = getReg();
    code_buffer.emit(new_reg + " = xor i1 1, " + reg);
    return new_reg;
}

string init_reg_enum(int enum_id) {
    string new_reg = getReg();
    code_buffer.emit(new_reg + " = add i32 0, " + to_string(enum_id));
    return new_reg;
}

string init_reg_string(const string& value) {
    string global_var_name = getGlobal();
    string ptr_reg = getReg();
    string size = to_string(value.size()-1);
    code_buffer.emitGlobal(global_var_name + " = constant [" + size + " x i8] c" + value.substr(0,value.size()-1) + "\\00\"");
    code_buffer.emit(ptr_reg + " = getelementptr [" + size +" x i8], [" + size +" x i8]* " + global_var_name + ", i32 0, i32 0");
    return ptr_reg;
}

int handle_bool_exp_jump(Exp exp) {

    string boolean_value = exp.reg;
    return code_buffer.emit("br i1 " + boolean_value + ", label @, label @");

}
