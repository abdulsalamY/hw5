//
// Created by abdul on 1/16/2020.
//

#include "StatementManager.hpp"
#include <unordered_map>
std::unordered_map<TypeID, std::string> typeId_to_type({
                                                     { INTTYPE, "i32" },
                                                     {ENUMTYPE, "i32" },
                                                     { BYTETYPE, "i8" },
                                                     { BOOLTYPE, "i1" },
                                                     { STRINGTYPE, "i8*" },
                                                     { VOIDTYPE, "void" },
                                                            });

StatementManager &StatementManager::instance() {
    static StatementManager inst;//only instance
    return inst;
}

vector<pair<int, BranchLabelIndex>>
StatementManager::handle_statements(string header_label, vector<pair<int, BranchLabelIndex>> statements_next_list) {
    code_buffer.bpatch(statements_next_list,header_label);
    int address = code_buffer.emit("br label @");
    return makelist({address,FIRST});
}

vector<pair<int, BranchLabelIndex>>
StatementManager::handle_statement() {
    int address = code_buffer.emit("br label @");
    return makelist({address,FIRST});
}

void StatementManager::handle_return(string reg, TypeID type) {
    if(reg == ""){
        code_buffer.emit("ret " + typeId_to_type[type]);
    }else {
        code_buffer.emit("ret " + typeId_to_type[type] + " " + reg);
    }
}

vector<pair<int, BranchLabelIndex>> StatementManager::handle_bool_exp() {
    return this->handle_statement();
}

