#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>

inline std::vector<double> read_file(const char* path) { // NOTE: this function is shared for both compile/run time

    // load file
    std::ifstream file(path);
    if(!file.is_open()) {
        // for a compile-time call, it throws a compile-time error if this file is not found at compile time
        // otherwise, it is just a runtime error
        throw std::runtime_error("could not open file " + std::string(path));
    }

    // read to `vec`
    std::vector<double> vec;
    double x;
    while(file >> x) {
        vec.push_back(x);
    }

    // return the `vec`
    return vec;
}

double my_function(double x) {
    // get the `coef`
    @meta std::vector<double> coef = read_file("series.txt"); // NOTE: this is a compile-time constant

    // compute the taylor expression
    double x2 = 1;
    double y = 0;
    @meta for(double c : coef) { // NOTE: this loop and `coef` has already been expanded at compile-time
        y += x2 * c; // accumulate the item
        x2 *= x; // make next item
    }

    // return the taylor value
    return y;
}

int main(int argc, char** argv) {
    // check whether input a value
    if(2 != argc) {
        fputs("expected 'x' argument to function\n", stderr);
        return 1;
    }

    // the input value
    double x = atof(argv[1]);

    // compute
    double y = my_function(x);

    // print
    printf("f(%f) = %f\n", x, y);

    // return
    return 0;
}