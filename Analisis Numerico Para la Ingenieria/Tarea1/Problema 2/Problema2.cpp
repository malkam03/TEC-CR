/* 
 * File:   main.cpp
 * Author: Malcolm Davis
 * Author: Juan Navarro
 *
 * Created on February 13, 2017, 4:37 PM
 */

#include <cstdlib>
#include <iostream>

template <typename type1, typename type2>
inline type1 const& Problema2(type1 const& n, type2 const& x, bool simple){
    if(simple){
        float result = 0;
        for(int i = 0; i < n; i++){
            result +=x;
        }
        std::cout << "Result: " << result << std::endl; 
        std::cout << "Presition: " << (simple ? "simple" : "double") <<std::endl;
        std::cout << "Error: " << (((n*x - result)/(n*x))*100) << std::endl;  
    }else{
        double result = 0;
        for(int i = 0; i < n; i++){
            result +=x;
        }
        std::cout << "Result: " << result << std::endl; 
        std::cout << "Presition: " << (simple ? "simple" : "double") <<std::endl;
        std::cout << "Error: " << (((n*x - result)/(n*x))*100) << std::endl;
    }
}
/*
 * 
 */
int main(int argc, char** argv) {
    Problema2(100000, 0.00001, true);
    Problema2(100000, 0.00001, false);
    return 0;
}

