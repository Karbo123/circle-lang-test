#include "json.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

@mvoid inject_function(std::string name, std::string text) {
    @meta std::cout << "Injecting " << name << " = "<< text << "\n";

    // expand this function definition into the scope (i.e. namespace or class scope) from which the macro is called
    double @(name)(double x) {
        return @@expression(text);
    }
}

@mvoid inject_from_json(const char* filename) {
    // load a json file at compile time
    // these objects have automatic storage duration at compile time
    // they'll destruct when the end of the macro is hit
    @meta std::ifstream inject_file(filename);
    @meta nlohmann::json inject_json;
    @meta inject_file >> inject_json;

    // loop over each item in the file and inject a function
    @meta for(auto& item : inject_json.items()) {
        @meta std::string key = item.key();
        @meta std::string value = item.value();

        // expand the inject_function 
        @macro inject_function(key, value);
    }  
}

int main() {
    // expand this macro into the injected namespace
    // this creates the namespace if it isn't already created.
    @macro namespace(injected) inject_from_json("inject.json");

    std::cout << "unity(.3) = "<< injected::unity(.3) << std::endl;

    return 0;
}