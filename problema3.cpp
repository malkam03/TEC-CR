/* 
 * File:   main.cpp
 * Author: Malcolm Davis
 * Author: Juan Navarro
 *
 * Created on February 14, 2017, 5:37 PM
 */

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <limits>   

template <typename type1, typename type2, typename type3>
inline type1 const& Problema3(type1 const& a, type2 const& b, type3 const& c,bool pressision ){
  /* Value of discriminant */
  double dis = (b*b) - (4*a*c);
  /* if the result is complex */
  if (dis < 0){
    std::cout << "Not a real result" << std::endl;
  }
  /*the result is not complex*/
  else{
    /*Varaibles with double presicion*/
    double x1 = 0;
    double x2 = 0;
    x1 = (-b + sqrt (dis))/2*a;
    x2 = (-b - sqrt (dis))/2*a;
    /*if true the result will be given using the double presicion*/
    if (pressision) {
      /*Set the digits given to print*/
      std::cout.precision(100);
      std::cout << "double pression" << std::endl;
      std::cout << x1 << std::endl;
      std::cout << x2 << std::endl;                 
    }
    else {
      std::cout << "single pression" << std::endl;
      float x11 = float(x1);
      float x12 = float(x2);
      std::cout << x11 << std::endl;
      std::cout << x12 << std::endl;      
    }
  }     
}
/*
 * 
 */
int main(int argc, char** argv) {
    std::cout << " --------- a = 1 -------- b = 2 ------ c = - 7 ----" << std::endl;
    Problema3(1, 2,-7,true);
    Problema3(1, 2,-7,false);
    std::cout << " --------- a = 1 -------- b = 20 ------ c = - 7 ----" << std::endl;
    Problema3(1, 20,-7,true);
    Problema3(1, 20,-7,false);
    std::cout << " --------- a = 1 -------- b = 200 ------ c = - 7 ----" << std::endl;
    Problema3(1, 200,-7,true);
    Problema3(1, 200,-7,false);
    std::cout << " --------- a = 1 -------- b = 2000 ------ c = - 7 ----" << std::endl;
    Problema3(1, 2000,-7,true);
    Problema3(1, 2000,-7,false);
    std::cout << " --------- a = 1 -------- b = 20000 ------ c = - 7 ----" << std::endl;
    Problema3(1, 20000,-7,true);
    Problema3(1, 20000,-7,false);
    return 0;
}
