/* 
 * File:   problema3.cpp
 * Author: Malcolm Davis
 *
 * Created on February 14, 2017, 5:37 PM
 */

#include <stdlib.h>
#include <iostream>
#include <math.h>

template <typename type>
inline type const& problema3(type & a, type & b, type & c){
  type discriminant = b*b - 4*a*c;
  float tmp;
  if (discriminant < 0){
    std::cout << "Not a real result." << std::endl;
  }
  else{
    type x1;
    type x2;
    x1 = (-b + sqrt(discriminant))/(2*a);
    x2 = (-b - sqrt(discriminant))/(2*a);
    std::cout << "------------------Start------------------" << std::endl;
    std::cout << a <<"x^2+" << b << "x+" << c << "=0\n";
    std::cout << (sizeof(tmp)==sizeof(a) ? "Simple" : "Double") <<" precision roots:\n";
    std::cout <<"X1: " << x1 << "\n";
    std::cout <<"X2: " << x2 << "\n";
    std::cout << "------------------End------------------" << std::endl; 
  }
}

/*
 * Main method for the third problem.
 * Usage: run a b c or run to deafault 
 */
int main(int argc, char** argv) {
    float simple[3] = {1, 10000, -1};
    double doublePres[3] = {1, 10000, -1}; 
    if(argc==1){
        //Keep the default values.
    }else if (argc==4){
        try{
            for(int i = 0; i < 3; i++){
              simple[i] = atof(argv[i+1]);
              doublePres[i] = strtod(argv[i+1], NULL);
            }
        }
        catch (const std::exception& e) { 
            std::cout << "A standard exception was caught, with message '"
                  << e.what() << "'\n";
            return -1;
        }
    }else {
        std::cout << "Usage: "<< argv[0] <<" a b c or "<< argv[0] <<" to deafault.\n";
        return -1;
    }
    problema3(simple[0],simple[1],simple[2]);
    problema3(doublePres[0],doublePres[1],doublePres[2]);
    return 0;
}
