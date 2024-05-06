# pragma once

#include <iostream>
#include <string>


namespace args {
    
    struct Validation {
        bool is_default = false;
        bool is_valid = false;
        std::string reason = "";
    };

    struct Args {
        Validation valid;

        int max = -1;
        int level = -1;
        bool table = false;
    };

    Args getArguments(int argc, char** argv);
}
