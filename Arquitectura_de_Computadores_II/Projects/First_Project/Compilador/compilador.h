#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector>
#include <string>
#include <array>
#include <stdexcept>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <utility>
#include <iterator>
#include <tuple>
#include <cstdlib>

#ifndef COMPILADOR_H
	#define COMPILADOR_H
#endif



class compilador
{

public:

	/**
	 * Constructor de la clase compilador
	 * @param void
	 * @return void
	 */
	compilador();

	int compilarArchivo(std::string nombreArchivo);

	void separarLineas(std::string nombreArchivo);

	void parsear();

	void guardarEtiqueta(std::string cadena, int numeroLinea);

	void guardarEtiquetaSalto(std::string cadena, int numeroLinea);

	int buscarEtiqueta(std::string nombreEtiqueta);

	void guardarRegistro(std::string cadena, int numeroLinea);

	void guardarInstruccion(std::string cadena);

	void limpiarArreglo();

	void copiarEnVector();

	void imprimirInstrucciones();

	void imprimirRegistros();

	void imprimirVector();	

	void verificarInstrucciones();

	void verificarOperando1(std::string operando1);

	void verificarOperando2(std::string operando2);

	void verificarOperando3(std::string operando3);

	std::string convertirDecBin(int numero);

	std::string convertirDecBinEtiq(int numero);	

	void convertirBinHex(std::string cadena);

	void crearArchivo(std::string instrucciones);


private:

	std::vector<std::string> instrucciones;

	std::vector<std::tuple<std::string, int > > etiquetas;

	std::vector<std::tuple<std::string, int > > etiquetasSalto;

	std::vector<std::tuple<std::string, std::string, std::string, std::string> > instruc;

	std::string instruccion;

	std::string instruccionActual;

	int operando;

	int numeroEtiqueta;

	int numeroInstrucciones = 0;

	int cantidadInstrucciones = 0;

	int numeroLineaArchivo = 0;

	std::string operando1;

	std::string operando2;

	std::string operando3;

	std::string opcode;

	std::string op1;

	std::string op2;

	std::string op3;

	std::string line;

	std::string errores;
};