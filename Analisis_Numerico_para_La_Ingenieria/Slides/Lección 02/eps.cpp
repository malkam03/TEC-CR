#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <complex>


int main()
{
  // ABOUT EPSILON OF IEEE754 

  std::cout << "Show machine precisions:\n";
  
  // float
  std::cout << "\nepsilon<float>: "
	    << std::numeric_limits<float>::epsilon() << std::endl;

  std::cout << "log_2(epsilon<float>): "
	    << std::log(std::numeric_limits<float>::epsilon())/
               std::log(2.0f) << std::endl;

  // double
  std::cout << "\nepsilon<double>: "
	    << std::numeric_limits<double>::epsilon() << std::endl;

  std::cout << "log_2(epsilon<float>): "
	    << std::log(std::numeric_limits<double>::epsilon())/
               std::log(2.0) << std::endl;


  
  
  
}
