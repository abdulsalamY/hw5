//
// Created by abdul on 1/14/2020.
//

#ifndef HW5_REGISTERMANAGER_HPP
#define HW5_REGISTERMANAGER_HPP

#include <string>

using namespace std;
class RegisterManager {
    static int count;
    static int global_count;
public:
    RegisterManager() = default;
    /**
     *
     * @return new register name.
     */
    static string getReg();
    static string getGlobal();
};

#endif //HW5_REGISTERMANAGER_HPP
