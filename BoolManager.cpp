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
    abstract_class->header_label = header_label;
    abstract_class->inner_label = if_false_label;
    return abstract_class;
}

string BoolManager::handleOrSecond(abstract_class * abstractClass, string reg) {
    int true_address = code_buffer.emit("br label @");
    string if_true_label = code_buffer.genLabel();
    vector<pair<int,BranchLabelIndex>> true_list =code_buffer.merge(makelist({true_address, FIRST}),abstractClass->true_list);
    code_buffer.bpatch(true_list, if_true_label);
    string result_reg = getReg();
    code_buffer.emit(result_reg + " = phi i1 [ 1, %" + abstractClass->header_label + " ], [ " + reg + ", %" + abstractClass->inner_label + " ]");
    return result_reg;
}