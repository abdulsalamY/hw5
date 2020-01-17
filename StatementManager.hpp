//
// Created by abdul on 1/16/2020.
//

#ifndef HW5_STATEMENTMANAGER_HPP
#define HW5_STATEMENTMANAGER_HPP

#include "bp.hpp"
#include "parser.hpp"
#define getReg() RegisterManager::getReg()
#define code_buffer CodeBuffer::instance()
#define makelist CodeBuffer::makelist

class StatementManager {
public:
    static StatementManager &instance();
    vector<pair<int,BranchLabelIndex>> handle_statements(string header_label,vector<pair<int,BranchLabelIndex>> statements_next_list);
    vector<pair<int,BranchLabelIndex>> handle_statement();
    void handle_return(string reg,TypeID type);
    vector<pair<int,BranchLabelIndex>> handle_bool_exp();
};


#endif //HW5_STATEMENTMANAGER_HPP
