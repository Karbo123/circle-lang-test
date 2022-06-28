#include "json.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

// NOTE: `@meta` can also be used in a global space
// load a json file at compile time
@meta std::ifstream inject_file("inject.json");
@meta nlohmann::json inject_json;
@meta inject_file >> inject_json;

// loop over each item in the file and inject a function.
@meta for(auto& item : inject_json.items()) {
    @meta std::string key = item.key();
    @meta std::string value = item.value();

    // print out what we have injected
    @meta std::cout << "Injecting " << key << " = " << value << std::endl;

    // define a function with the key name into the global namespace
    double @(key)(double x) {
        // convert the value text into an expression
        // NOTE: the definition actually comes from an external json file
        return @expression(value);
    }
}

int main(int argc, char** argv) {
    // check whether input a value
    double x = 0.5;
    if(2 == argc) {
        x = atof(argv[1]);
    } else {
        std::cout << "using a default input value `x = " << x << "`" << std::endl;
    }

    // evaluate
    std::cout << "sq(.3) = " << sq(x) << std::endl;

    // return
    return 0;
}