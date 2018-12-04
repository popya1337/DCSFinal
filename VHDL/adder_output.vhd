library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;


entity datapath_adder is
	port
	(
	a : in std_logic_vector(3 downto 0);
	b : in std_logic_vector(3 downto 0);
	c : out std_logic_vector(3 downto 0);
	WR_INPUT : in std_logic;
	FU_0_MUX_A_SEL : in std_logic_vector(0 downto 0);
	FU_0_MUX_B_SEL : in std_logic_vector(0 downto 0);
	REG_0_MUX_SEL : in std_logic_vector(0 downto 0);
	REG_1_MUX_SEL : in std_logic_vector(0 downto 0);
	REG_2_MUX_SEL : in std_logic_vector(0 downto 0);
	clear : in std_logic;
	clock : in std_logic);
end datapath_adder;

architecture adder_arch of datapath_adder is

--BEGINNING OF SIGNALS

	signal FU_0_A_IN : std_logic_vector(3 downto 0);
	signal FU_0_B_IN : std_logic_vector(3 downto 0);
	signal FU_0_OUT : std_logic_vector(3 downto 0);
	signal REG_0_IN : std_logic_vector(3 downto 0);
	signal REG_0_OUT : std_logic_vector(3 downto 0);
	signal REG_1_IN : std_logic_vector(3 downto 0);
	signal REG_1_OUT : std_logic_vector(3 downto 0);
	signal REG_2_IN : std_logic_vector(8307327 downto 0);
	signal REG_2_OUT : std_logic_vector(8307327 downto 0);

begin

--OUTPUTS

	c <= REG_0_OUT;

--BEGINNING OF FUNCTIONAL UNITS

	FU_0: entity work.c_adder
	generic map(width => 4)
	port map(input1 => FU_0_A_IN, input2 => FU_0_B_IN, output => FU_0_OUT);


--BEGINNING OF REGS

	REG_0: entity work.c_register
	generic map(width => 4)
	port map(input => REG_0_IN, WR => WR_INPUT, output => REG_0_OUT, clear => clear, clock => clock);

	REG_1: entity work.c_register
	generic map(width => 4)
	port map(input => REG_1_IN, WR => WR_INPUT, output => REG_1_OUT, clear => clear, clock => clock);

	REG_2: entity work.c_register
	generic map(width => 4)
	port map(input => REG_2_IN, WR => WR_INPUT, output => REG_2_OUT, clear => clear, clock => clock);


--BEGINNING OF MUXES FOR FUNCTIONAL UNITS

	FU_0_MUX_A : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => a, mux_select => FU_0_MUX_A_SEL, output => FU_0_A_IN);

	FU_0_MUX_B : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => b, mux_select => FU_0_MUX_B_SEL, output => FU_0_B_IN);


--BEGINNING OF MUXES FOR REGISTERS

	REG_0_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => FU_0_OUT, mux_select => REG_0_MUX_SEL, output => REG_0_IN);

	REG_1_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => b, mux_select => REG_1_MUX_SEL, output => REG_1_IN);

	REG_2_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => a, mux_select => REG_2_MUX_SEL, output => REG_2_IN);

end adder_arch;