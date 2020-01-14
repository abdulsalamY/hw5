//
// Created by abdul on 1/13/2020.
//

#ifndef HW5_ABSTRACT_CLASS_HPP
#define HW5_ABSTRACT_CLASS_HPP
#include <iostream>
#include <vector>
#include <string>
#include "bp.hpp"
extern int yylineno;
using namespace std;

class abstract_class{
public:
    int lineno;
    string header_label;
    string inner_label;
    string token;
    string reg;
    vector<pair<int,BranchLabelIndex>> true_list;
    vector<pair<int,BranchLabelIndex>> false_list;
    abstract_class():lineno(yylineno){}

};

#endif //HW5_ABSTRACT_CLASS_HPP
