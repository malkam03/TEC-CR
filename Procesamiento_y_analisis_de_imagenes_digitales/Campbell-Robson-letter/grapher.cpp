//#include "grapher.h"
#include <map>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include "gnuplot-iostream.h"
#include <stdlib.h> 

#pragma once
template<typename T>
class grapher
{
private:
	Gnuplot gPlot;
	std::pair<int, int> * xRange;
	std::pair<int, int> * yRange;
	std::pair<int, int> * center;

public:
	grapher(int = 50, int = 20, int = 50, int = 50);
	inline void operator ()( std::vector<std::vector<T> >* pPreImages, std::vector<std::vector<T> >* pImages, std::vector<std::string>* pTitles);
	~grapher();
	std::string toString(int * pInt);
};


/**
*Constructor of the class to graph the functions with c
*/
template<typename T>
grapher<T>::grapher(int pXMax, int pYMax, int pCenterX, int pCenterY)
{
	xRange = new std::pair<int, int>;
	yRange = new std::pair<int, int>;
	center = new std::pair<int, int>;
	*xRange =  std::make_pair(pCenterX-pXMax, pCenterX+pXMax);
	*yRange = std::make_pair(pCenterY-pYMax, pCenterY+pYMax);
	*center = std::make_pair(pCenterX, pCenterY);
}

/**
* Destructor of the class to graph the functions with c
*/
template<typename T>
grapher<T>::~grapher()
{
	delete xRange;
	delete yRange;
	delete center;
}

/**
* () operator overloaded to graph n function
*/
template<typename T>
inline void grapher<T>::operator () ( std::vector<std::vector<T> >* pPreImages,  std::vector<std::vector<T> >* pImages,  std::vector<std::string> * pTitles)
{

	gPlot << "set xrange ["<< toString(&xRange->first)<< ":"<< toString(&xRange->second) << "]\nset yrange ["<< toString(&yRange->first)<<":"<< toString(&yRange->second) <<"]\n";
	std::string command =  "plot";
	std::vector<std::pair<T, T> > xy_pts_A;
	for(int i=0; i<pPreImages->size(); i++){
		for(int j=0; j<pPreImages->at(i).size(); j++) {
			xy_pts_A.push_back(std::make_pair(pPreImages->at(i).at(j), pImages->at(i).at(j)));
		//	std::cout << i << " -> " << xy_pts_A[j].first << " : " << xy_pts_A[j].second << std::endl;
		}
		if(i!=pPreImages->size()-1){
			command += gPlot.file1d(xy_pts_A) + "with lines title '" + pTitles->at(i)+ "',";
		}else{
			command += gPlot.file1d(xy_pts_A) + "with lines title '" + pTitles->at(i) +"'";
		}
	}
	gPlot << command <<std::endl;
}


template<typename T>
std::string grapher<T>::toString(int * pData)
{
	std::ostringstream stream;
	stream << *pData;
	return stream.str();
}

/**
* Main para probar el funcionamiento nada mas hay que borrarlo
*/
/*
int main() {
	int funciones = 6;
	int entradas = 10000;
	int inicio = 0;
	std::vector<std::vector <double> > metodos(funciones, std::vector<double>(entradas));
	std::vector<std::vector <double> > resultados(funciones, std::vector<double>(entradas)) ;
	std::vector<std::string > hola(funciones);
	anpi::grapher<double> graph(2, 2, 0);
	double x=-2;
	int f=3;
	for(int i=0; i<funciones; i++){
		for(double j=0; j<inicio+entradas; j++){
			metodos[i][j] = x;
			resultados[i][j] = sin(x*2*3.14+f);
			x+=0.001;
			//				std::cout << i << ", " << j << " : " << resultados[i][j] << " : " << metodos[i][j] << std::endl;
		}
		hola[i]="Funcion " ;
		hola[i]+= graph.toString(&i);
		x=-2;	 
		f=rand()%(2*3);
	}
	graph(&metodos, &resultados, &hola);
	
}*/
