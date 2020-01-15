#ifndef EXAMPLE1
#define EXAMPLE1
#include <iostream>
#include <vector>
#include <stack>
#include "hw3_output.hpp"
#include "abstract_class.hpp"

extern int yylineno;
using namespace std;
enum TypeID {VOIDTYPE, INTTYPE, BOOLTYPE, BYTETYPE, ENUMTYPE, STRINGTYPE, NONETYPE, ERRORUNDEFINED};

string getStringFromType(TypeID type_enum);


class Identifier : public abstract_class{
public:
    string value;
    explicit Identifier(string name=""){
        value=name;
    }
};

class Type : public abstract_class {
public:
    TypeID type;
        Identifier enum_id;
    Type(TypeID type, string enum_id = ""): type(type), enum_id(enum_id){}
};

class RetType : public Type {
public:
    RetType(TypeID type) : Type(type){}
};

class EnumType : public Type {
public:
    EnumType(string enum_id): Type(ENUMTYPE,enum_id){}
};

class Enumerator : public Identifier {
public:
    Enumerator()=default;
    Enumerator(string name):Identifier(name){   }
};

class EnumeratorList : public abstract_class {
public:
    vector<Enumerator> enum_values_options;
    EnumeratorList() = default;
    void insert (Enumerator curr_enum){
        enum_values_options.emplace_back(curr_enum);
    }

    bool contains(Enumerator enumerator){

        for (Enumerator curr_var : enum_values_options){
            if(curr_var.value == enumerator.value)
                return true;
        }
        return false;
    }
};

class Formal : public abstract_class {
public:
    int offset;
    Type type;
    Identifier id;
    Identifier enum_id;
    bool is_new_Enum_Type;
    EnumeratorList possible_EnumeratorList;
    /// enum_id is the name of the ENUM TYPE for example moths or DAYS
    Formal (TypeID type,string name,string enum_id = "") : enum_id(enum_id),id(name),type(type, enum_id) {
        type = type ;
        is_new_Enum_Type= false;
        offset=-1;
    }
    Formal (TypeID type,string name,EnumeratorList enums_vals,string enum_id = "") : enum_id(enum_id),id(name),type(type, enum_id) {
        type = type ;
        possible_EnumeratorList=enums_vals;
        is_new_Enum_Type = true;
        offset=-1;
    }
	Formal() = default;
};

class Formals : public abstract_class {
public:
    vector<Formal> formals;
    Formals() = default;
    Formals(vector<Formal> formals){
        this->formals=formals;
    }

    void insert(Formal formal){
        formals.insert(formals.begin(),formal);
    }
};



class Exp : public abstract_class{
public:
    Type type;
    Identifier id;
    Exp(TypeID type, string id = "", string enum_id="") : type(type,enum_id), id(id) {}

};

class ExpList: public abstract_class {
public:
    vector<Exp> exp_list;
    ExpList() = default;
    void insert(Exp exp){
        exp_list.insert(exp_list.begin(),exp);
    }
};

class FuncID : public abstract_class {
public:
    string func_name;
    Formals formals;
    RetType ret_type;
    FuncID(string func_name,TypeID ret_type) : ret_type(ret_type), func_name(func_name){}

    FuncID(string func_id, RetType ret_type, Formals formal):ret_type(ret_type){
        formals=formal;
        func_name=func_id;
    }
    string getId(){
        return func_name;
    }
    bool compareArgs(ExpList exp_list){
        if(formals.formals.size()!=exp_list.exp_list.size())
            return false;
        for (int i = 0; i < formals.formals.size(); ++i) {
            if(formals.formals[i].type.type != exp_list.exp_list[i].type.type && !(formals.formals[i].type.type == INTTYPE && exp_list.exp_list[i].type.type == BYTETYPE)){
                return false;
            }
            if(formals.formals[i].type.type == ENUMTYPE){
              if(formals.formals[i].enum_id.value != exp_list.exp_list[i].type.enum_id.value){
                return false;
              }
            }
          }
        return true;
    }

    vector<string> getArgs(){

        vector<string> to_ret = vector<string>();
        for(Formal curr_formal : formals.formals){
            if(curr_formal.type.type == ENUMTYPE){
                to_ret.emplace_back("enum " + curr_formal.enum_id.value);
            }
            if(curr_formal.type.type == INTTYPE){
                to_ret.emplace_back("INT");
            }
            if(curr_formal.type.type == BOOLTYPE){
                to_ret.emplace_back("BOOL");
            }
            if(curr_formal.type.type == BYTETYPE){
                to_ret.emplace_back("BYTE");
            }
            if(curr_formal.type.type == STRINGTYPE){
                to_ret.emplace_back("STRING");
            }
            //PROBABLY SHOULDN'T BE A VOID PARAM TO FUNCTION...
            if(curr_formal.type.type == VOIDTYPE){
                to_ret.emplace_back("VOID");
            }
        }
        return to_ret;
    }
};

class Table : public abstract_class {
public:
    int curr_offset;
    vector<Formal> vars_in_scope_list;      //can be enum moth curr_month = "january"; for example
    vector<Formal> enums_in_scope_list;     //new enum types in current scope
    Table() = default;
    //new Table(stack.top.curr_offset)
    //or first scope (global only) new Table(0);
    Table(int starting_offset){
        curr_offset=starting_offset;
    }

    void insertIdentifier(Formal formal){
        formal.offset=curr_offset;
        vars_in_scope_list.emplace_back(formal);
        curr_offset++;
    }
    void insertFormals(Formals& formals){
        int curr_off_set=-1;
        for(Formal param : formals.formals){
            param.offset=curr_off_set;
            vars_in_scope_list.emplace_back(param);
            curr_off_set--;
        }
    }

    /// checks if exists an Enum Type with the id sent( only checks for Enum Types not vars)
    bool containsEnum(Identifier id){

        for(Formal curr_enum : enums_in_scope_list){
            //for enum TYPE!! we save as a normal new formal and insert to enums list
            //for enum var we add also a formal with enum_id and not normal, and there we have its value and so...
            if(curr_enum.id.value == id.value)
                return true;
        }
        return false;
    }
    bool contains(Identifier id){
        //here we check for normal var
        for(Formal var : vars_in_scope_list){
            if (var.id.value==id.value)
                return true;
        }
        for (Formal new_enum_type : enums_in_scope_list){
            if(new_enum_type.id.value==id.value)
                return true;
            for(Enumerator item : new_enum_type.possible_EnumeratorList.enum_values_options){
                if (item.value == id.value)
                    return true;
            }
        }
        return false;
    }
    void insertEnum(Identifier id,EnumeratorList& enumerator_list){
        enums_in_scope_list.emplace_back(Formal(ENUMTYPE,id.value,enumerator_list));
    }

    Type getIdentifierType(Identifier id){
        for(Formal var : vars_in_scope_list){
            if (var.id.value==id.value)
                return var.type;
        }
        for (Formal new_enum_type : enums_in_scope_list){
            if(new_enum_type.id.value==id.value)
                return Type(NONETYPE);
            for(Enumerator item : new_enum_type.possible_EnumeratorList.enum_values_options){
                if (item.value == id.value)
                    return Type(ENUMTYPE,new_enum_type.id.value);
            }
        }
        return Type(NONETYPE);
    }

    bool EnumTypeHasEnumVal(Identifier EnumType, Identifier EnumVal){
        for(Formal currEnumType : enums_in_scope_list){
            if(currEnumType.id.value==EnumType.value){
                for(Enumerator currEnumVal : currEnumType.possible_EnumeratorList.enum_values_options){
                    if(currEnumVal.value == EnumVal.value)
                        return true;
                }
            }
        }
        return false;
    }

    EnumType getIdentifierEnumType(Identifier id){
        for (Formal new_enum_type : enums_in_scope_list){
            for(Enumerator item : new_enum_type.possible_EnumeratorList.enum_values_options){
                if (item.value == id.value)
                    return EnumType(new_enum_type.enum_id.value);
            }
        }
        for (Formal curr_var : vars_in_scope_list) {
            if(curr_var.id.value == id.value){
                return EnumType(curr_var.enum_id.value);
            }
        }
        return EnumType("no@@");
    }

    int getEnumOffset(const Identifier& id){
        for (Formal new_enum_type : enums_in_scope_list){
            int cnt = 0;
            for(Enumerator item : new_enum_type.possible_EnumeratorList.enum_values_options){
                if (item.value == id.value)
                    return cnt;
                cnt++;
            }
        }
        return -1;
    }

    void printEnums(){

        for (Formal curr_enum_type : enums_in_scope_list){
            vector<string> to_print = vector<string>();
            for( Enumerator curr_enum_val : curr_enum_type.possible_EnumeratorList.enum_values_options){
                to_print.push_back(curr_enum_val.value);
            }
            output::printEnumType(curr_enum_type.id.value, to_print);
        }
    }

    void printVariables(){
        for(Formal curr_var : vars_in_scope_list){
            if(curr_var.type.type == ENUMTYPE){
                output::printID(curr_var.id.value, curr_var.offset, "enum " + curr_var.enum_id.value);
            }else{
                ///here we print for other regular vars like INT , BOOL ...
                output::printID(curr_var.id.value, curr_var.offset, getStringFromType(curr_var.type.type));
            }
        }
    }
};

class Num : public abstract_class{
public:
    int num;
    explicit Num(int num) : num(num) {}
    Num() = default;
};

class Call: public abstract_class{
public:
    Type type;
    explicit Call(TypeID type) : type(type){    }
};

class Additive: public abstract_class{
public:
    explicit Additive(string op) : abstract_class(){
        this->token = op;
    }
};

class Multiplicative: public abstract_class{
public:
    explicit Multiplicative(string op) : abstract_class(){
        this->token = op;
    }
};

class Relational: public abstract_class{
public:
    explicit Relational(string op) : abstract_class(){
        this->token = op;
    }
};

class Equality: public Relational{
public:
    explicit Equality(string op) : Relational(op){
    }
};

class StringToken: public abstract_class{
public:
    explicit StringToken(char* str) : abstract_class(){
        this->token = string(str);
    }
};
#define YYSTYPE abstract_class*
#endif
