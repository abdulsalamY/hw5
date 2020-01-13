//
// Created by abdul on 21/12/2019.
//
#include "parser.hpp"


string getStringFromType(TypeID type_enum){
    switch (type_enum){
        case INTTYPE:
            return "INT";
        case BOOLTYPE:
            return "BOOL";
        case STRINGTYPE:
            return "STRING";
        case BYTETYPE:
            return "BYTE";
        case ENUMTYPE:
            return "enum";
        case VOIDTYPE:
            return "VOID";
        default:
            return "";
    }
}