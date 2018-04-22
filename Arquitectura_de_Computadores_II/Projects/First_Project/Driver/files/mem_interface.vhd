LIBRARY ieee;
USE ieee.std_logic_1164.all;
ENTITY mem_interface IS
PORT (clk, reset :IN STD_LOGIC;
	read, write : IN STD_LOGIC;
	readData: OUT STD_LOGIC_VECTOR(127 DOWNTO 0);
	writeData : IN STD_LOGIC_VECTOR(127 DOWNTO 0));
END mem_interface;

ARCHITECTURE Structure of mem_interface IS
SIGNAL to_processor : STD_LOGIC_VECTOR(31 DOWNTO 0);
SIGNAL from_processor : STD_LOGIC_VECTOR(31 DOWNTO 0);
COMPONENT memory IS
	PORT(clock :IN STD_LOGIC;
		rden, wren : IN STD_LOGIC;
		q: OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
		data, address : IN STD_LOGIC_VECTOR(31 DOWNTO 0));
	END COMPONENT;
BEGIN
		mem_instance: memory PORT MAP(clk, read, write, readData(31 DOWNTO 0), writeData(31 DOWNTO 0), writeData(63 DOWNTO 32));	
END Structure;