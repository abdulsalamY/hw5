//
// Created by abdul on 1/14/2020.
//

#include "BoolManager.hpp"
#include "abstract_class.hpp"


BoolManager &BoolManager::instance() {
    static BoolManager inst;//only instance
    return inst;
}

abstract_class* BoolManager::handleOr(const string& reg) {
    auto* abstract_class = new class abstract_class();
    string cond_reg = getReg();
    int header_address = code_buffer.emit("br label @");
    string header_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({header_address,FIRST}),header_label);
    code_buffer.emit(cond_reg + " = icmp eq i1 1, " + reg);
    int address = code_buffer.emit("br i1 " + cond_reg + ", label @, label @");
    string if_false_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({address,SECOND}),if_false_label);
    abstract_class->true_list.emplace_back(address,FIRST);
    return abstract_class;
}

string BoolManager::handleOrSecond(abstract_class * abstractClass, string reg) {
    string cond_reg = getReg();
    int header_address = code_buffer.emit("br label @");
    string header_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({header_address,FIRST}),header_label);
    code_buffer.emit(cond_reg + " = icmp eq i1 1, " + reg);
    int address = code_buffer.emit("br i1 " + cond_reg + ", label @, label @");
    abstractClass->true_list.emplace_back(address,FIRST);
    abstractClass->false_list.emplace_back(address,SECOND);

    //if the exp is false we will jump to here:
    string if_false_label = code_buffer.genLabel();
    code_buffer.bpatch(abstractClass->false_list,if_false_label);
    int from_false = code_buffer.emit("br label @");

    //if the exp is true we will jump to here:
    string if_true_label = code_buffer.genLabel();
    code_buffer.bpatch(abstractClass->true_list,if_true_label);
    int from_true = code_buffer.emit("br label @");

    //if the prev block was "if_true" the result should be true.
    string phi_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({from_false,FIRST}), phi_label);
    code_buffer.bpatch(makelist({from_true,FIRST}), phi_label);
    string result_reg = getReg();
    code_buffer.emit(result_reg + " = phi i1 [ 1, %" + if_true_label + " ], [ 0, %" + if_false_label + " ]");
    return result_reg;
}

abstract_class* BoolManager::handleAnd(const string& reg) {
    auto* abstract_class = new class abstract_class();
    string cond_reg = getReg();
    int header_address = code_buffer.emit("br label @");
    string header_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({header_address,FIRST}),header_label);
    code_buffer.emit(cond_reg + " = icmp eq i1 0, " + reg);
    int address = code_buffer.emit("br i1 " + cond_reg + ", label @, label @");
    string if_false_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({address,SECOND}),if_false_label);
    abstract_class->true_list.emplace_back(address,FIRST);
    return abstract_class;
}

string BoolManager::handleAndSecond(abstract_class * abstractClass, string reg) {
    string cond_reg = getReg();
    int header_address = code_buffer.emit("br label @");
    string header_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({header_address,FIRST}),header_label);
    code_buffer.emit(cond_reg + " = icmp eq i1 1, " + reg);
    int address = code_buffer.emit("br i1 " + cond_reg + ", label @, label @");
    abstractClass->true_list.emplace_back(address,FIRST);
    abstractClass->false_list.emplace_back(address,SECOND);

    //if the exp is false we will jump to here:
    string if_false_label = code_buffer.genLabel();
    code_buffer.bpatch(abstractClass->false_list,if_false_label);
    int from_false = code_buffer.emit("br label @");

    //if the exp is true we will jump to here:
    string if_true_label = code_buffer.genLabel();
    code_buffer.bpatch(abstractClass->true_list,if_true_label);
    int from_true = code_buffer.emit("br label @");

    //if the prev block was "if_true" the result should be true.
    string phi_label = code_buffer.genLabel();
    code_buffer.bpatch(makelist({from_false,FIRST}), phi_label);
    code_buffer.bpatch(makelist({from_true,FIRST}), phi_label);
    string result_reg = getReg();
    code_buffer.emit(result_reg + " = phi i1 [ 1, %" + if_true_label + " ], [ 0, %" + if_false_label + " ]");
    return result_reg;
}

string BoolManager::handleRelational(string token, string reg1, string reg2, TypeID reg1_type, TypeID reg2_type) {
    if(reg1_type == BYTETYPE){
        string new_reg = getReg();
        code_buffer.emit(new_reg + " = zext i8 " + reg1 + " to i32");
        reg1 = new_reg;
    }
    if(reg2_type == BYTETYPE){
        string new_reg = getReg();
        code_buffer.emit(new_reg + " = zext i8 " + reg2 + " to i32");
        reg2 = new_reg;
    }
    string result_reg = getReg();
    code_buffer.emit(result_reg + " = icmp " + op_translate[token] + " i32 "+ reg1 + ", " +reg2);
    return result_reg;
}
