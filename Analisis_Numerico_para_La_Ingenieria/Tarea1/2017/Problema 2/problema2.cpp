/* 
 * File:   problema2.cpp
 * Author: Malcolm Davis
 *
 * Created on July 30, 2017, 3:12 PM
 */

#include <stdlib.h>
#include <iostream>
#include <cmath>

template <typename type>
inline type const& problema2(int & n, type & x){
    type result = 0;
    float tmp;
    for(int i = 0; i < n; i++){
        result +=x;
    }
    std::cout << "------------------Start------------------" << std::endl;
    std::cout << "Result: " << result << std::endl; 
    std::cout << "Precision: " << (sizeof(tmp)==sizeof(result) ? "simple" : "double") <<std::endl;
    std::cout << "Error: " << ((std::abs(n*x - result)/(n*x))*100) << std::endl; 
    std::cout << "------------------End------------------" << std::endl; 
}
/*
 * Main method for the second problem.
 * Usage: run n  x 
 */
int main(int argc, char** argv) {
    int n=100000;
    float simple= 0.00001;
    double doublePres= 0.00001;
    if(argc==1){
        //Keep the default values.
    }else if (argc==3){
        try{
            n = atoi(argv[1]);
            simple = atof(argv[2]);
            doublePres = strtod(argv[2], NULL);
        }
        catch (const std::exception& e) { 
            std::cout << "A standard exception was caught, with message '"
                  << e.what() << "'\n";
            return -1;
        }
    }else {
        std::cout << "Usage: "<< argv[0] <<" n x or "<< argv[0] <<" to deafault.\n";
        return -1;
    }
    problema2(n, simple);
    problema2(n, doublePres);
    return 0;
}

