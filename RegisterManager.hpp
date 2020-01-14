//
// Created by abdul on 1/14/2020.
//

#ifndef HW5_REGISTERMANAGER_HPP
#define HW5_REGISTERMANAGER_HPP

#include <string>

using namespace std;
class RegisterManager {
    static int count;
public:
    RegisterManager() = default;
    /**
     *
     * @return new register name.
     */
    static string getReg();
};

#endif //HW5_REGISTERMANAGER_HPP
