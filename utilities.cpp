//
// Created by abdul on 1/14/2020.
//

#include "utilities.hpp"

void Utilities::initProgram() {
    std::stringstream code_stream;
    code_stream << "declare i32 @printf(i8*, ...)\n"
                   "declare void @exit(i32)\n";
    code_stream << "@.int_specifier = constant [4 x i8] c\"%d\\0A\\00\"\n"
                   "@.str_specifier = constant [4 x i8] c\"%s\\0A\\00\"\n"
                   "@.str_error = constant [24 x i8] c\"Error division by zero\\0A\\00\"\n";

    code_stream << "define void @printi(i32) {\n"
                   "    call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0), i32 %0)\n"
                   "    ret void\n"
                   "}\n";
    code_stream << "define void @print(i8*) {\n"
                   "    call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0), i8* %0)\n"
                   "    ret void\n"
                   "}\n";
    code_stream << "define void @error_division_by_zero() {\n"
                   "    call void (i8*) @print(i8* getelementptr ([24 x i8], [24 x i8]* @.str_error, i32 0, i32 0))\n"
                   "    call void (i32) @exit(i32 0)\n"
                   "    ret void\n"
                   "}";
    code_buffer.emitGlobal(code_stream.str());
}
