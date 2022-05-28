#include "Base.h"
#include <iostream>

class Derived : public Base{
    public:
        std::string foo();
        std::string bar();
        virtual ~Derived();
};