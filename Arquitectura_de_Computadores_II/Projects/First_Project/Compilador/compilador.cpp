#include "compilador.h"

compilador::compilador(){
}

int compilador::compilarArchivo(std::string nombreArchivo){
	try{
		separarLineas(nombreArchivo);
	}
	catch(std::invalid_argument& e){
		std::cerr << e.what() << std::endl;
	}
	return 1;
}

// Toma cada línea del archivo de texto y la inserta en un vector
void compilador::separarLineas(std::string nombreArchivo){
	std::ifstream archivo; 
   	archivo.open(nombreArchivo); 
   	std::string linea;
   	if (archivo.is_open()){
   		while (getline(archivo,linea)){
   			instrucciones.push_back(linea);			
   		}
   		archivo.close();
    	parsear();  
   	}
   	else{
   		throw std::invalid_argument("El archivo no existe o no puede ser abierto");
   	}
}

// Obtiene los diferentes tokens
void compilador::parsear(){
	// Ciclo que va recorriendo cada línea del vector
	for(unsigned int i=0; i<instrucciones.size(); i++){
		std::string linea = instrucciones[i];
		std::string cadena = "";
		bool flagInstrucccion = false;
		operando=0;
		numeroLineaArchivo++;
		// Ciclo para obtener caracter por caracter de la línea
		for (unsigned int j=0; j<instrucciones[i].length(); j++){
			// Ignorar el comentario
			if (instrucciones[i][j]=='#'){
				break;
			}
			// Si es inmediato o un salto al final de la línea
			else if (cadena!="" && j==instrucciones[i].length()-1)
			{
				cadena = cadena + instrucciones[i][j];
				guardarRegistro(cadena, i);			
			}
			// Definición de la etiqueta
			else if(instrucciones[i][j]==':'){
				guardarEtiqueta(cadena, i+1);
				cadena="";
			}
			// 			
			else if (iswspace(instrucciones[i][j]) && cadena!=""){
				// Si es una instrucción
				if (!flagInstrucccion){				
					guardarInstruccion(cadena);
					flagInstrucccion=true;
				}
				// Si es un inmediato un salto
				else{
					guardarRegistro(cadena, i);
				}
				cadena="";
			}
			// Va construyendo el string
			else if (isalpha(instrucciones[i][j])  || isdigit(instrucciones[i][j])){
				cadena.append(linea.substr(j,1));	
			}
			// Si es un registro
			else if (instrucciones[i][j]=',' && cadena!=""){
				guardarRegistro(cadena, i);
				cadena="";	
			}
			else{

			}
		}
		copiarEnVector();
	}
	verificarInstrucciones();
}

// Guarda el nombre y número de línea de la definición de la etiquetaen un vector de etiquetas
void compilador::guardarEtiqueta(std::string cadena, int numeroLinea){
	std::cout << "La etiqueta es: " << cadena << " en la línea " << numeroLinea << std::endl;
	etiquetas.push_back(std::make_tuple(cadena, numeroLinea));
}

// Guarda el nombre y número de línea de la etiqueta a la que se quiere hacer el salto
void compilador::guardarEtiquetaSalto(std::string cadena, int numeroLinea){
	std::cout << "La etiqueta salto es: " << cadena << std::endl;
	etiquetasSalto.push_back(std::make_tuple(cadena, numeroLinea));
}

// Guarda los registros, según sea el primer, segundo, o tercer operando 
void compilador::guardarRegistro(std::string cadena, int numeroLinea){
	if (operando==0){
		if (instruccion=="J"){
			operando1 = cadena.substr(0,cadena.length());
		}
		else{
			operando1 = cadena.substr(1,cadena.length());
		}
	}
	else if(operando==1){
		operando2 = cadena.substr(1,cadena.length());		
	}
	else{
		if (instruccion=="BNE" || instruccion =="BEQ"){
			operando3 = cadena.substr(0, cadena.length());
		}
		else if (instruccion=="LV") {
			operando3 = "nada";
		}
		else{
			operando3 = cadena.substr(1, cadena.length());
		}		
	}
	operando++;	
}

// Compara la etiqueta de salto de instrucción para ver si se encuentra definida en el archivo
int compilador::buscarEtiqueta(std::string nombreEtiqueta){
	bool flag = false; 
	for(std::vector<std::tuple<std::string, int > >::iterator iterador=etiquetas.begin(); iterador<etiquetas.end(); iterador++){
		std::string x;
		x=std::get<0>(*iterador);
		if (!x.compare(nombreEtiqueta)){
			int y = std::get<1>(*iterador);
			flag = true;
			return y;
			break;
		}	
	}
	// Si la etiqueta no está
	if (flag==false){
		errores = errores + "\nError: La etiqueta " + "<<" + nombreEtiqueta + ">>" + " en la línea " + std::to_string(cantidadInstrucciones) + " no existe!";	
	}
}

// Guarda la instrucción
void compilador::guardarInstruccion(std::string cadena){
	instruccion = cadena;
	numeroInstrucciones++;
	// Primer operando en la instrucción SV es 00000
	if (instruccion=="SV"){
		operando++;
	}
}

// Copia los valores obtenidos de instrucción y operandos en el vector
void compilador::copiarEnVector(){
	if (instruccion!=""){
		instruc.push_back(std::make_tuple(instruccion, operando1, operando2, operando3));
		std::cout << "Instrucción->" << instruccion << std::endl;
		std::cout << "Operando1->" << operando1 << std::endl;
		std::cout << "Operando2->" << operando2 << std::endl;
		std::cout << "Operando3->" << operando3 << std::endl;		
	}
	if (instruccion=="BEQ" || instruccion=="BNE"){
		guardarEtiquetaSalto(operando3, numeroInstrucciones);
	}
	if (instruccion=="J"){
		guardarEtiquetaSalto(operando1, numeroInstrucciones);		
	}
	operando1="";
	operando2="";
	operando3="";
	instruccion="";
}

// Imprimir todas las instrucciones
void compilador::imprimirInstrucciones(){
	for(std::vector<std::tuple<std::string, std::string, std::string, std::string> >::iterator iterador=instruc.begin(); iterador<instruc.end();iterador++){
		std::string x;
		x=std::get<0>(*iterador);
		std::cout << "La instrucción->" << x << std::endl;
	}
}

// Imprime todos los registros de operandos
void compilador::imprimirRegistros(){
	for(std::vector<std::tuple<std::string, std::string, std::string, std::string> >::iterator iterador=instruc.begin(); iterador<instruc.end();iterador++){
		std::string op1, op2, op3;
		op1 = std::get<1>(*iterador);
		std::cout << "El operando1->" << op1 << std::endl;
		op2 = std::get<2>(*iterador);
		std::cout << "El operando2->" << op2 << std::endl;
		op3 = std::get<3>(*iterador);
		std::cout << "El operando3->" << op3 << std::endl;					
	}	
}

// Imprime el vector compuesto por instrucciones y operandos
void compilador::imprimirVector(){
	for(std::vector<std::tuple<std::string, std::string, std::string, std::string> >::iterator iterador=instruc.begin(); iterador<instruc.end();iterador++){
		std::string instruccion;
		std::string op1, op2, op3;
		instruccion = std::get<0>(*iterador);
		std::cout << "La instrucción->" << instruccion << std::endl;		
		op1 = std::get<1>(*iterador);
		std::cout << "El operando1->" << op1 << std::endl;
		op2 = std::get<2>(*iterador);
		std::cout << "El operando2->" << op2 << std::endl;
		op3 = std::get<3>(*iterador);
		std::cout << "El operando3->" << op3 << std::endl;			
	}	
}

// Verifica la validez de las instrucciones y los registros de operandos
void compilador::verificarInstrucciones(){
	for(std::vector<std::tuple<std::string, std::string, std::string, std::string> >::iterator iterador=instruc.begin(); iterador<instruc.end();iterador++){
		std::string instruccion;
		instruccion = std::get<0>(*iterador);
		instruccionActual = instruccion;
		cantidadInstrucciones++;

		if (!instruccion.compare("XOR")){
			opcode = "010000";
		}
		else if (!instruccion.compare("SRL")){
			opcode = "010001";
		}
		else if (!instruccion.compare("SLL")){
			opcode = "010010";	
		}
		else if (!instruccion.compare("SRC")){
			opcode = "010011";
		}
		else if (!instruccion.compare("SLC")){
			opcode = "010100";
		}
		else if (!instruccion.compare("ADDV")){
			opcode = "010101";
		}
		else if (!instruccion.compare("SUBV")){
			opcode = "010110";
		}
		else if (!instruccion.compare("ADDS")){
			opcode = "001011";
		}
		// Hay que revisar etiquetas de salto
		else if (!instruccion.compare("J")){
			opcode = "100000";
		}
		else if (!instruccion.compare("BNE")){
			opcode = "100010";
		}
		else if (!instruccion.compare("BEQ")){
			opcode = "100011";
		}
		else if (!instruccion.compare("LV")){
			opcode = "100100";
		}	
		else if (!instruccion.compare("SV")){
			opcode = "100101";
		}
		else{
			errores = errores + "La instrucción << " + instruccion + " >> no coincide!";
		}
		
		line.append(opcode);

		std::string operando1;	
		operando1 = std::get<1>(*iterador);
		if (instruccion=="J"){
			numeroEtiqueta = (buscarEtiqueta(operando1)*3)-4;
			line.append("00000");
		}
		else{
			verificarOperando1(operando1);
		}		

		std::string operando2;	
		operando2 = std::get<2>(*iterador);
		verificarOperando2(operando2);

		std::string operando3;	
		operando3 = std::get<3>(*iterador);
		if (instruccion=="BEQ" || instruccion=="BNE"){
			numeroEtiqueta = (buscarEtiqueta(operando3)*3)-4;
			line.append("00000");			
		}	
		verificarOperando3(operando3);
	}
	convertirBinHex(line);	
}

	
std::string compilador::convertirDecBin(int numero){
	std::string result;
    while(numero!=0) {
    	result = (numero%2==0 ?"0":"1")+result;
    	numero/=2;
    }
    int largo = result.length();
    if (largo==5){
    	return result;
    }
    else{
    	while (largo<5){
    		result = "0" + result;
    		largo++;
    	}
    }
}

std::string compilador::convertirDecBinEtiq(int numero){
	std::string result;
    while(numero!=0) {
    	result = (numero%2==0 ?"0":"1")+result;
    	numero/=2;
    }
    int largo = result.length();
    if (largo==27){
    	return result;
    }
    else{
    	while (largo<27){
    		result = "0" + result;
    		largo++;
    	}
    }
}

void compilador::verificarOperando1(std::string operando1){
	int num = 0;
	std::stringstream ss(operando1);
	ss >> num;
	op1 = convertirDecBin(num);
	line.append(op1);
}

void compilador::verificarOperando2(std::string operando2){
	int num = 0;
	std::stringstream ss(operando2);
	ss >> num;
	op2 = convertirDecBin(num);
	line.append(op2);
}

void compilador::verificarOperando3(std::string operando3){
	int num = 0;
	std::stringstream ss(operando3);
	ss >> num;
	op3 = convertirDecBin(num);
	if (instruccionActual!="BNE" && instruccionActual!="BEQ"){
		line.append(op3);
	}

	if (instruccionActual=="J" || instruccionActual=="BNE" || instruccionActual=="BEQ"){	
		std::string hola = convertirDecBinEtiq(numeroEtiqueta);
		line.append(hola);
	}
	else{
		line.append("000000000000000000000000000");
	}
}

// Convierte las filas de 4 caracteres de binario a hexadecimal
void compilador::convertirBinHex(std::string cadena){
	int ocho, cuatro, dos, uno, result;
	int acum = 0;
	std::string resultado, total, letra;
	for (int x=0; x<=cadena.length()-1; x=x+4){
		acum++;
		ocho = (cadena[x]-48)*8;
		cuatro = (cadena[x+1]-48)*4;
		dos = (cadena[x+2]-48)*2;
		uno = (cadena[x+3]-48)*1;
		result = ocho + cuatro + dos + uno;
		if (result>9){
			if (result==10){
				letra = "A";
			}
			else if (result==11){
				letra = "B";
			}
			else if (result==12){
				letra = "C";
			}
			else if (result==13){
				letra = "D";
			}
			else if (result==14){
				letra = "E";
			}
			else{
				letra = "F";
			}
			resultado = resultado + letra;
		}
		else{
			std::ostringstream convert;
			convert << result;
			resultado = resultado + convert.str();
		}
		result = 0;
		// Instrucción completa
	}
	std::cout << resultado << std::endl;
	// Si no hay errores se crea el archivo
	if (errores==""){
		crearArchivo(resultado);
	}
	else{
		std::cout << errores << std::endl;
		std::cout << "No se pudo crear el archivo .mif!" << std::endl;
	}
}

void compilador::crearArchivo(std::string codigo){
	std::ofstream dataFile;
	dataFile.open("output.mif");
	if(dataFile.is_open()){
		dataFile << "WIDTH=48;\n";
		dataFile << "DEPTH=1024;\n";
		dataFile << "\n";
		dataFile << "ADDRESS_RADIX=UNS;\n";
		dataFile << "DATA_RADIX=HEX;\n\n";
		dataFile << "CONTENT BEGIN\n";
		int limite = 48;
		int x = 0;
		for (int i=0; i<codigo.length(); i++){
			if (i%12 == 0){
				if (i!=0){
					dataFile << ";";
				}
				dataFile << "\n";
				dataFile << x << " : " << "000000000000;\n";
				x++;
				dataFile << x << " : " << "000000000000;\n";
				x++;
				dataFile << x << " : ";
				x++;
			}
			dataFile << codigo[i];
		}
		dataFile << ";";
		dataFile << "\n\n";
		dataFile << "END;\n";
    	dataFile.close();
	}
	else throw std::invalid_argument("No se pudo abrir");
}

