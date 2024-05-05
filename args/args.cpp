#include <string>
#include <iostream>

#include "args.h"


namespace {

    void setDefaults(args::Args& args) {
            args.max = 100;
            args.level = -1;
            args.table = false;
    }

    void validate(args::Args& args) {
        args.valid.is_valid = true;
        args.valid.is_default = false;
        args.valid.reason = "Arguments passed are valid";
    }

    void validateDefault(args::Args& args) {
        args.valid.is_valid = true;
        args.valid.is_default = true;
        args.valid.reason = "No arguments passed";
    }

    void invalidateNoMaxValueProvided(args::Args& args) {
        args.valid.is_valid = false;
        args.valid.is_default = false;
        args.valid.reason = "No value provided for -max argument";
    }

    void invalidateNoLevelValueProvided(args::Args& args) {
        args.valid.is_valid = false;
        args.valid.is_default = false;
        args.valid.reason = "No value provided for -level argument";
    }

    void invalidateUnknownArgumentProvided(args::Args& args, 
                                           const std::string& arg) {
        args.valid.is_valid = false;
        args.valid.is_default = false;
        args.valid.reason = "Unknown argument provided: " + arg;
    }

    void invalidateWrongMaxValue(args::Args& args) {
        args.valid.is_valid = false;
        args.valid.is_default = false;
        args.valid.reason = "Incorrect value provided for -max argument: "
                            + std::to_string(args.max);
    }

    void invalidateWrongLevelValue(args::Args& args) {
        args.valid.is_valid = false;
        args.valid.is_default = false;
        args.valid.reason = "Incorrect value provided for -level argument: "
                            + std::to_string(args.level);
    }

    void invalidateBothLevelAndMaxSpecified(args::Args& args) {
        args.valid.is_valid = false;
        args.valid.is_default = false;
        args.valid.reason = "-max and -level arguments are mutually exclusive";
    }

    void invalidateTableIsNotOnlyArgument(args::Args& args) {
        args.valid.is_valid = false;
        args.valid.is_default = false;
        args.valid.reason = "-table must be the only argument provided";
    }

    void checkArgsCoherence(args::Args& args) {
        bool table_set = args.table;
        
        bool max_set = args.max != -1;
        bool max_valid = args.max >= 2;

        bool level_set = args.level != -1;
        bool level_valid = args.level >=1 && args.level <= 3;

        if (table_set) {
            if (max_set || level_set) {
                invalidateTableIsNotOnlyArgument(args);
            }
        }
        else { // !table_set
            if (max_set && level_set) {
                invalidateBothLevelAndMaxSpecified(args);
            }
            else if (!level_set && !max_valid) {
                invalidateWrongMaxValue(args);
            }
            else if (!max_set && !level_valid) {
                invalidateWrongLevelValue(args);
            }
        }
    }

} // namespace <unnamed>


namespace args {

    Args getArguments(int argc, char** argv) {
        Args ret;
        
        if (argc < 2) {
            validateDefault(ret);
            setDefaults(ret);

            return ret;
        }

        int pos = 1;
        while (pos < argc) {
            std::string arg_value{ argv[pos] };

            if (arg_value == "-table") {
                validate(ret);
                ret.table = true;
                pos += 1;
            }
            else if (arg_value == "-max") {
                if (pos+1 >= argc) 
                    invalidateNoMaxValueProvided(ret);
                else {
                    validate(ret);
                    ret.max = std::stoi(argv[pos+1]);
                }
                pos += 2;
            }
            else if (arg_value == "-level") {
                if (pos+1 >= argc) {
                    invalidateNoLevelValueProvided(ret);
                }
                else {
                    validate(ret);
                    ret.level = std::stoi(argv[pos+1]);
                }
                pos += 2;
            }
            else {
                invalidateUnknownArgumentProvided(ret, argv[pos]);
                return ret;
            }
        }

        checkArgsCoherence(ret);
        
        return ret;
    }

} // namespace args
