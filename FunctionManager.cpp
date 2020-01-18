//
// Created by abdul on 1/17/2020.
//

#include "FunctionManager.hpp"
#include <sstream>
extern std::unordered_map<TypeID, std::string> typeId_to_type;

FunctionManager::FunctionManager(FuncID func):function(func.func_name, func.ret_type, func.formals) {}

string FunctionManager::handle_call(string function_name, TypeID ret_type) {
    std::stringstream call_stream;
    string return_res;
    if(ret_type != VOIDTYPE){
        return_res = getReg();
        call_stream << return_res +" = ";
    }
    call_stream << "call " + typeId_to_type[ret_type] +" @" + function_name + "()";
    code_buffer.emit(call_stream.str());
    return return_res;
}
string FunctionManager::handle_call(string function_name, TypeID ret_type, ExpList* exp_list) {
    std::stringstream call_stream;
    std::stringstream exp_list_stream;
    string trunc_reg = "";
    string return_res;
    if(ret_type != VOIDTYPE){
        return_res = getReg();
        call_stream << return_res +" = ";
    }
    call_stream << "call " + typeId_to_type[this->function.ret_type.type] +" @" + function_name;
    if(exp_list->exp_list[0].type.type == BYTETYPE && this->function.formals.formals[0].type.type == INTTYPE){
        trunc_reg = getReg();
        code_buffer.emit(trunc_reg + " = zext i8 " + exp_list->exp_list[0].reg + " to i32");
        exp_list_stream << "i32 " + trunc_reg;
    }else {
        exp_list_stream << typeId_to_type[exp_list->exp_list[0].type.type] + " " + exp_list->exp_list[0].reg;
    }
    for (int i = 1; i < exp_list->exp_list.size() ; ++i) {
        if(exp_list->exp_list[i].type.type == BYTETYPE && this->function.formals.formals[i].type.type == INTTYPE){
            trunc_reg = getReg();
            code_buffer.emit(trunc_reg + " = trunc i8 " + exp_list->exp_list[i].reg + " to i32");
            exp_list_stream << ", i32 " + trunc_reg;
        }
        else{
            exp_list_stream << ", " + typeId_to_type[exp_list->exp_list[i].type.type] + " " + exp_list->exp_list[i].reg;
        }
    }
    call_stream << "(" + exp_list_stream.str() + ")";
    code_buffer.emit(call_stream.str());
    return return_res;
}

void FunctionManager::handle_declaration() {
    std::stringstream declaration_stream;
    std::stringstream formals_stream;
    declaration_stream << "define " + typeId_to_type[this->function.ret_type.type] + " @" + this->function.func_name;
    for (Formal formal: this->function.formals.formals) {
        formals_stream << typeId_to_type[formal.type.type] + ", " ;
    }
    string formals = formals_stream.str();
    formals = (formals.empty()) ? "" : formals.substr(0,formals.size()-2);
    declaration_stream << "(" + formals + ") {";
    code_buffer.emit(declaration_stream.str());
    code_buffer.emit("entry:");
}

void FunctionManager::handle_close(vector<pair<int,BranchLabelIndex>> next_list) {
    string closing_label = code_buffer.genLabel();
    code_buffer.bpatch(next_list,closing_label);
    if(this->function.ret_type.type != VOIDTYPE){
        code_buffer.emit("ret " + typeId_to_type[this->function.ret_type.type] + " 0");
    }
    else {
        code_buffer.emit("ret void");
    }
    code_buffer.emit("}");
}
