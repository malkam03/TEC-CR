LIBRARY ieee;
USE ieee.std_logic_1164.all;
ENTITY vectorial_processor_interface IS
PORT (clock, reset :IN STD_LOGIC;
	read, write : IN STD_LOGIC;
	readData: OUT STD_LOGIC_VECTOR(127 DOWNTO 0);
	writeData : IN STD_LOGIC_VECTOR(127 DOWNTO 0);
	address : OUT STD_LOGIC_VECTOR(7 DOWNTO 0));
END vectorial_processor_interface;

ARCHITECTURE Structure of vectorial_processor_interface IS
SIGNAL to_processor : STD_LOGIC_VECTOR(31 DOWNTO 0);
SIGNAL from_processor : STD_LOGIC_VECTOR(31 DOWNTO 0);
COMPONENT procesador IS
	PORT(clk, clk_f, rst :IN STD_LOGIC;
		readEn, writeEn : OUT STD_LOGIC;
		prueba, memAddress, memDataInput: OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
		dataMem : IN STD_LOGIC_VECTOR(31 DOWNTO 0));
	END COMPONENT;
BEGIN
	processor_instance: procesador PORT MAP(clock, clock, reset, readData(96), readData(97), readData(95 DOWNTO 64), readData(63 DOWNTO 32), readData(31 DOWNTO 0), writeData(31 DOWNTO 0));
END Structure;