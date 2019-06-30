/**
 * Includes
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <complex>
#include <typeinfo>
#include <boost/math/tools/polynomial.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/lexical_cast.hpp>
#include "string.h"
/**
 * Compiler const
 */
#define deflationMethod 1
#define deflationMethod2 2
#define mullerMethod 3
#define laguerreMethod 4
#define debug

namespace po = boost::program_options;
namespace anpi {
	/**
	 * Deflation class
	 */
	template<typename T> class deflation {
		public :
			/**
			 * Deflation class operator () overload
			 * @param poly: the polynomial array it can be almost any numerical type.
			 * @param root: a known root of the polynomial, has to be the same type as poly.
			 * @param order: the size of the polynomial -1, has to be a int.
			 * @return
			 */
			inline std::vector<T> operator () ( std::vector<T>& poly, T& root, T& res, int order) {
				res =poly[order];
				poly[order]=0;
				#ifdef debug
					std::cout << "Deflation method started." << std::endl;
				#endif
				for (int i=order-1;i>=0;i--){
					T s = poly[i];
					poly[i]=res;
					res=s+res*root;
					std::cout << poly[i] << "x^" << i;
					if(i!=0) std::cout << " + ";
				}
				std::cout << "\n";
				#ifdef debug
					std::cout << "Deflation method ended." << std::endl;
				#endif
				return poly;
			}
	};
	/**
	 * Deflation2 class, for the case that both complex conjugate roots have to be deleted 
	 */
	template<typename T> class deflation2 {
		public :
			/**
			 * Deflation2 class operator () overload
			 * @param poly: the polynomial array, has to be a complex<T> type.
			 * @param root: a known root of the polynomial, has to be  the same type as poly.
			 * @param order: the size of the polynomial -1, has to be a int.
			 * @return
			 */
			inline std::vector<T> operator () (std::vector<T>& poly, T& root, T& res, int order) {
				res =poly[order];
				poly[order]=0;
				#ifdef debug
					std::cout << "Deflation method 2 started." << std::endl;
				#endif
				for (int i=order-1;i>=0;i--){
					T s = poly[i];
					poly[i]=res;
					res=s+res*root;
				}
				res =poly[--order];
				root=std::conj(root);
				poly[order]=0;
				for (int i=order-1;i>=0;i--){
					T s = poly[i];
					poly[i]=res;
					res=s+res*root;
					std::cout << poly[i] << "x^" << i;
					if(i!=0) std::cout << " + ";
				}
				std::cout << "\n";
				#ifdef debug
					std::cout << "Deflation method 2 ended." << std::endl;
				#endif
				return poly;
			}
	};
	/**
	 * Muller class
	 */
	template <typename T>
	class muller{
		public:
			/**
			 * Muller class operator () overload
			 * @param x0: 
			 * @param x1: 
			 * @param x2: 
			 * @param coefs:
			 * @param max:
			 * @param pTolerance:
			 * @return
			 */
			std::vector<std::complex<T> > operator()(T x0, T x1, T x2,const std::vector< std::complex<T> >& coefs,unsigned int max, double pTolerance) {
			std::vector<std::complex<T> > res;
			std::vector<std::complex<T> > q = coefs;
			std::complex<T> z;
			while (q.size() > 2) {
			    z = polinom_zero(x0, x1, x2, q, max, pTolerance);
			    //z = polinom_zero(p, z);
			    q = horner(q, z);
			    res.push_back(z);
			  }
			  res.push_back(-q[0] / q[1]);
			  return res;
			} 

			std::complex<T> evaluatePol(std::vector<std::complex<T> >& coef, std::complex<T> * x){
				std::complex<T> result = 0;
				for (int ite = 0; ite<coef.size(); ite++){
					result+= coef[ite]*std::pow(*x, ite);
				}
				return result;
			}

			std::vector<std::complex<T> > horner(const std::vector<std::complex<T> > &a, std::complex<T> x0) {
			  int n = a.size();
			  std::vector<std::complex<T> >  b(std::max(1, n - 1),0);

			  for(int i = n - 1; i > 0; i--)
			    b[i - 1] = a[i] + (i < n - 1 ? b[i] * x0 : 0);
			  return b;
			}

			std::complex<T>  polinom_zero (T x0, T x1, T x2,std::vector< std::complex<T> >& coefs,unsigned int max, double pTolerance){
				std::complex<T> xi0, xi1, xi2,xi3, h0,h1,q0,q1,A, B, C,result, tmp1, tmp2;
				long double err;
				xi0=x0;
				xi1=x1;
				xi2=x2;
				err=2;
				tmp1=0;
				tmp2=0;
				int ite =0;
				while(ite<max && (long double)err >= pTolerance){


					h0=xi1-xi0;
					h1=xi2-xi1;
					q0=(evaluatePol(coefs, &xi1)-evaluatePol(coefs, &xi0))/h0;
					q1=(evaluatePol(coefs, &xi2)-evaluatePol(coefs, &xi1))/h1;
					
					A=(q1-q0)/(h1+h0);
					B=A*h1+q1;
					C=(evaluatePol(coefs, &xi2));
				
					tmp1=xi2+((std::complex<T> )-2*C)/(B+std::sqrt(B*B-(std::complex<T> )4*A*C));
					tmp2=xi2+((std::complex<T> )-2*C)/(B-std::sqrt(B*B-(std::complex<T> )4*A*C));
					
					if(B.real()>=0)
						xi3=tmp1;
					else
						xi3=tmp2;
					err=std::abs((((xi3-xi2)/xi3)).real())*100;

					xi0=xi1;
					xi1=xi2;
					xi2=xi3;
					ite++;
					
				}
				return xi3;
			};
		
	};
	typedef std::complex<double> cdouble;
	typedef std::vector<cdouble> polyn;
	/**
	 * Laguerre class
	 */
	std::pair<polyn, cdouble> horner(const polyn &a, cdouble x0) {
	  int n = a.size();
	  polyn b = polyn(std::max(1, n - 1));

	  for(int i = n - 1; i > 0; i--)
	    b[i - 1] = a[i] + (i < n - 1 ? b[i] * x0 : 0);
	  return make_pair(b, a[0] + b[0] * x0);
	}

	cdouble eval(const polyn &p, cdouble x) {
	  return horner(p, x).second;
	}

	polyn derivative(const polyn &p) {
	  int n = p.size();
	  polyn r = polyn(std::max(1, n - 1));
	  for(int i = 1; i < n; i++)
	    r[i - 1] = p[i] * cdouble(i);
	  return r;
	}

	const double EPS = 1e-9;

	int cmp(cdouble x, cdouble y) {
	  double diff = abs(x) - abs(y);
	  return diff < -EPS ? -1 : (diff > EPS ? 1 : 0);
	}

	cdouble find_one_root(const polyn &p0, cdouble x) {
	  int n = p0.size() - 1;
	  polyn p1 = derivative(p0);
	  polyn p2 = derivative(p1);
	  for (int step = 0; step < 10000; step++) {
	    cdouble y0 = eval(p0, x);
	    if (cmp(y0, 0) == 0) break;
	    cdouble G = eval(p1, x) / y0;
	    cdouble H = G * G - eval(p2, x) - y0;
	    cdouble R = sqrt(cdouble(n - 1) * (H * cdouble(n) - G * G));
	    cdouble D1 = G + R;
	    cdouble D2 = G - R;
	    cdouble a = cdouble(n) / (cmp(D1, D2) > 0 ? D1 : D2);
	    x -= a;
	    if (cmp(a, 0) == 0) break;
	  }
	  return x;
	}

	std::vector<cdouble> find_all_roots(const polyn &p) {
	  std::vector<cdouble> res;
	  polyn q = p;
	  while (q.size() > 2) {
	    cdouble z(rand() / double(RAND_MAX), rand() / double(RAND_MAX));
	    z = find_one_root(q, z);
	    z = find_one_root(p, z);
	    q = horner(q, z).first;
	    res.push_back(z);
	  }
	  res.push_back(-q[0] / q[1]);
	  return res;
	}
}

/**
 * Auxiliar method for the main
 * @param method          Which method will be run (number from 1 to 4 or none for default).
 * @param poly            The polynomial that the method will be run in.
 * @param order           The orther of the polynomial.
 * @param root            The root of the polinomial (use for deflation).
 * @param X               The positions where the method will be started.
 * @param maxIt           The max times the method will be run(muller).
 * @param tolerance       The tolerance the method will have(muller).
 * @param singlePrecision Single precision flag.
 * @param polish          Polish flag.
 */
void mainAux(unsigned short method, std::vector<double>& poly, short order, double root, std::vector<double> X, int maxIt=50, double tolerance=0.00001, bool singlePrecision=0,bool polish=0){
	if(poly.size()==0 and method!=0){
		std::cout << "To use a method you need to enter a polynomial with the option --polynomial and the coeficients."<< std::endl;
		return;
	}
	switch(method){
		case deflationMethod: //Deflation
		{
			if(singlePrecision){
				std::complex<float> res =*(new std::complex<float>(0,0));
				std::complex<float> roots=*(new std::complex<float>(root,0));
				std::vector<std::complex<float> > polys;
				anpi::deflation<std::complex<float> > defla;
				for(int i=0; i<poly.size(); i++){
					std::complex<float> tmp=*(new std::complex<float>(poly[i],0));
					polys.push_back(tmp);
				}
				defla(polys,roots, res, (int)order);
			}else{
				std::complex<double> res =*(new std::complex<double>(0,0));
				std::complex<double> rootd=*(new std::complex<double>(root,0));
				std::vector<std::complex<double> > polyd;
				anpi::deflation<std::complex<double> > defla;
				for(int i=0; i<poly.size(); i++){
					std::complex<float> tmp=*(new std::complex<float>(poly[i],0));
					polyd.push_back(tmp);
				}
				defla(polyd,rootd, res, (int)order);
			}
			break;
		}
		case deflationMethod2: //Deflation2
		{
			if(singlePrecision){
				std::complex<float> res =*(new std::complex<float>(0,0));
				std::complex<float> roots=*(new std::complex<float>(root,0));
				std::vector<std::complex<float> > polys;
				anpi::deflation2<std::complex<float> > defla;
				for(int i=0; i<poly.size(); i++){
					std::complex<float> tmp=*(new std::complex<float>(poly[i],0));
					polys.push_back(tmp);
				}
				defla(polys,roots, res, (int)order);
			}else{
				std::complex<double> res =*(new std::complex<double>(0,0));
				std::complex<double> rootd=*(new std::complex<double>(root,0));
				std::vector<std::complex<double> > polyd;
				anpi::deflation2<std::complex<double> > defla;
				for(int i=0; i<poly.size(); i++){
					std::complex<float> tmp=*(new std::complex<float>(poly[i],0));
					polyd.push_back(tmp);
				}
				defla(polyd,rootd, res, (int)order);
			}
			break;
		}
		case mullerMethod: //Muller
		{

			if(X.size()!=3){
				std::cout << "Three positions has to be set to use this method. Use the option: --position and the positions space separated." << std::endl;
				return ;
			}
			if(singlePrecision){
				anpi::muller<float> mull;
				std::vector<std::complex<float> > polyd;
				for(int i=0; i<poly.size(); i++){
					std::complex<float> tmp=*(new std::complex<float>(poly[i],0));
					polyd.push_back(tmp);
				}
				std::vector<std::complex<float> > res;
				res = mull((float)X[0], 
								(float)X[1], 
								(float)X[2], 
								polyd, 
								(unsigned int)maxIt,
								(float)tolerance);
				for(int i = 0; i < res.size(); i++){
					std::cout<< "x" << i <<": " << res[i] << std::endl; 
				}
				break;
			}else{
				anpi::muller<double> mull;
				std::vector<std::complex<double> > polyd;
				for(int i=0; i<poly.size(); i++){
					std::complex<double> tmp=*(new std::complex<double>(poly[i],0));
					polyd.push_back(tmp);
				}
				std::vector<std::complex<double> > res;
				res = mull((double)X[0], 
								(double)X[1], 
								(double)X[2], 
								polyd, 
								(unsigned int)maxIt,
								(double)tolerance);
				for(int i = 0; i < res.size(); i++){
					std::cout<< "x" << i <<": " << res[i] << std::endl; 
				}
				break;
			}
		}
		case laguerreMethod:
		{
			anpi::polyn p;
			// x^3 - 8x^2 - 13x + 140 = (x+4)(x-5)(x-7)
			//X**3 + 2x**2 -109x -110 = (x+11)(x+8)(x-4)
			for(int i=0; i<poly.size(); i++){
				p.push_back(poly[i]);
			}
			std::vector<anpi::cdouble> roots = anpi::find_all_roots(p);

			for(size_t i = 0; i < roots.size(); i++) {
				if (abs(roots[i].real()) < anpi::EPS) roots[i] -= anpi::cdouble(roots[i].real(), 0);
					if (abs(roots[i].imag()) < anpi::EPS) roots[i] -= anpi::cdouble(0, roots[i].imag());
						std::cout << std::setprecision(3) << roots[i] << std::endl;
			}
			break;
		}
		default:
		{
			//Deflation method
			std::cout << "Deflation of 1x^3+3x^2+4x+12, with 2i as root." <<std::endl;
			std::vector<std::complex<double> >  polyd;
			std::complex<double> tmp= *(new std::complex<double>(12,0));
			polyd.push_back(tmp);
			tmp= *(new std::complex<double>(4,0));
			polyd.push_back(tmp);
			tmp= *(new std::complex<double>(3,0));
			polyd.push_back(tmp);
			tmp= *(new std::complex<double>(1,0));
			polyd.push_back(tmp);
			std::complex<double> rootd =*(new std::complex<double>(0,2));
			std::complex<double> res =*(new std::complex<double>(0,0)); 
			anpi::deflation<std::complex<double> > defla;
			defla(polyd,rootd, res, (int)order);
			//Deflation method 2
			std::cout << "Deflation method 2 of 1x^3+3x^2+4x+12, with 2i as root." <<std::endl;
			rootd =*(new std::complex<double>(0,2));
			res =*(new std::complex<double>(0,0)); 
			anpi::deflation2<std::complex<double> > defla2;
			defla2(polyd,rootd, res, (int)order);
			//Muller method
			std::cout << "Muller method roots of 1x^3+2x^2+-5x+-6." <<std::endl;
			anpi::muller<double> mull;
			std::vector<std::complex<double> >coefs;
			tmp=-6;
			coefs.push_back(tmp);
			tmp=-5;
			coefs.push_back(tmp);
			tmp=2;
			coefs.push_back(tmp);
			tmp=1;
			coefs.push_back(tmp);
			std::vector<std::complex<double> > result;
			result = mull((double)-4, 
							(double)-2, 
							(double)0, 
							coefs, 
							(unsigned int)50,
							(long double)0.000001);
			for(int i = 0; i < result.size(); i++){
				std::cout<< "x" << i <<": " << result[i] << std::endl; 
			}
			
			//Laguerre method
			std::cout << "Laguerre roots of 1x^3-2x^2+-109x+-110." <<std::endl;
			anpi::polyn p;
			// x^3 - 8x^2 - 13x + 140 = (x+4)(x-5)(x-7)
			//X**3 + 2x**2 -109x -110 = (x+11)(x+8)(x-4)
			p.push_back(-110);
			p.push_back(-109);
			p.push_back(-2);
			p.push_back(1);

			std::vector<anpi::cdouble> roots = anpi::find_all_roots(p);

			for(size_t i = 0; i < roots.size(); i++) {
				if (abs(roots[i].real()) < anpi::EPS) roots[i] -= anpi::cdouble(roots[i].real(), 0);
					if (abs(roots[i].imag()) < anpi::EPS) roots[i] -= anpi::cdouble(0, roots[i].imag());
						std::cout << std::setprecision(3) << roots[i] << std::endl;
			}
		}
		
	}
}

/**
 * Main method, runs all the methods with a default or you can enter options
 * @param Uses program options, call the program plus --help to see detailed description
 * @return the return is depending which method is called
 */
int main(int argc, char** argv){
	using boost::lexical_cast;
	using boost::bad_lexical_cast;
	//Default values for the methods:
	short order=3;
	unsigned short method=0;
	double tolerance=0.000001;
	int maxIt=50;
	std::vector<double> poly;
	double root;
	std::vector<double> position;
	bool polish=0;
	bool singlePrecision=0;
	//Program options definitions
	po::options_description description("Project1 Usage");
	description.add_options()
	("help", "Display this help message")
	("polynomial", po::value<std::vector<double> >(&poly)->multitoken(), "The polynomial that the program will use, just add the coeficients space separated.")
	("position", po::value<std::vector<double> >(&position)->multitoken(), "The positions to start the method space separated.")
	("root", po::value<double>(&root), "The root to find.")
	("order", po::value<short>(&order), "The order of the polynomial.")
	("muller", "Use this option to use the muller method.")
	("deflation", "Use this option to use deflation method.")
	("deflation2", "Use this option to use deflation2 method.")
	("laguerre", "Use this option to use laguerre method.")
	("polish", "Use this option to polish the roots.")
	("tolerance", po::value<double>(&tolerance), "The order of the polynomial.")
	("maxIterations", po::value<int>(&maxIt), "The order of the polynomial.")
	("singlePrecision", "Use this to set the methods to double singlePrecision, otherwise double precision will be used.");
	po::positional_options_description p;
	p.add("file", -1);
	po::variables_map vm;
	//Try to use the entered options
	try {
		po::store(po::parse_command_line(argc, argv, description, po::command_line_style::unix_style ^ po::command_line_style::allow_short), vm);		po::notify(vm);
		if(vm.count("help")){
			std::cout << description;
			return 0;
		}
		if(vm.count("order")){
			#ifdef debug
				std::cout << "Polynomial order changed to: " << order << std::endl;
			#endif
			if(order<0){
				std::cout << "The order has to be a positive number." << std::endl;
				return -1;
			}
		}
		if(vm.count("tolerance")){
			#ifdef debug
				std::cout << "The tolerance for the method will be: " << tolerance << std::endl;
			#endif
			if(tolerance<0){
				std::cout << "The tolerance has to be a positive number." << std::endl;
				return -1;
			}

		}
		if(vm.count("maxIterations")){
			#ifdef debug
				std::cout << "Max iterations will be changed to: " << maxIt << std::endl;
			#endif
			if(maxIt<0){
				std::cout << "The iterations has to be a positive number." << std::endl;
				return -1;
			}

		}
		if(vm.count("singlePrecision")){
			#ifdef debug
				std::cout << "Polynomial order changed to: " << singlePrecision << std::endl;
			#endif
			singlePrecision = 1;
		}
		if(vm.count("deflation")){
			#ifdef debug
				std::cout << "Deflation method will be used." << std::endl;
			#endif
			method = deflationMethod;
		}
		if(vm.count("deflation2")){
			#ifdef debug
				std::cout << "Deflation method 2 will be used." << std::endl;
			#endif
			method = deflationMethod2;
		}
		if(vm.count("muller")){
			#ifdef debug
				std::cout << "Muller method will be used." << std::endl;
			#endif
			method = mullerMethod;
		}
		if(vm.count("laguerre")){
			#ifdef debug
				std::cout << "Laguerre method will be used." << std::endl;
			#endif
			method = laguerreMethod;
		}
		if(vm.count("poly")){
			#ifdef debug
				std::cout << "A custom polynomial will be used. With size: " <<poly.size() << std::endl;
			#endif
			if(poly.size()<=0){
				std::cout << "The polynomial coeficients must be more than 0." << std::endl;
				return -1;
			}
		}
		if(vm.count("root")){
			#ifdef debug
				std::cout << "A custom root will be used: " << root << std::endl;
			#endif
		}
		if(vm.count("position")){
			#ifdef debug
				std::cout << "Custom positions will be used." << std::endl;
			#endif
			if(poly.size()<=0){
				std::cout << "The positions must be more than 0." << std::endl;
				return -1;
			}
		}
		mainAux(method, poly, order, root, position,maxIt, tolerance, singlePrecision,polish);
		return 0;
	}
	catch(const po::error &ex){
		std::cerr << ex.what() << '\n';
	}
	
}


