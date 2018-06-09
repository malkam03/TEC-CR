/* Quartus Prime Version 17.1.0 Build 590 10/25/2017 SJ Lite Edition */
JedecChain;
	FileRevision(JESD32A);
	DefaultMfr(6E);

	P ActionCode(Ign)
		Device PartName(SOCVHPS) MfrSpec(OpMask(0));
	P ActionCode(Cfg)
		Device PartName(5CSEMA5) Path("/home/malkam03/Documents/TEC-CR/Arquitectura_de_Computadores_II/Projects/First_Project/Driver/") File("output_file.jic") MfrSpec(OpMask(1) SEC_Device(EPCQ128A) Child_OpMask(1 1));

ChainEnd;

AlteraBegin;
	ChainType(JTAG);
AlteraEnd;
