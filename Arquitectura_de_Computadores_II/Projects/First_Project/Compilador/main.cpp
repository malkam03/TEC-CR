#include "compilador.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc,char** argv)
{
	// Para ejecutar ./<<nombreEjectuable>> <<nombreArchivo.txt>>
	std::string nombreArchivo = argv[1];
	compilador comp;
	comp.compilarArchivo(nombreArchivo);
	return 0;
}