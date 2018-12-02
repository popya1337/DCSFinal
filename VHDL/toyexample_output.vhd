library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;


entity datapath_toyexample is
port
(
	a : in std_logic_vector(3 downto 0);
	b : in std_logic_vector(3 downto 0);
	c : in std_logic_vector(3 downto 0);
	d : in std_logic_vector(3 downto 0);
	e : in std_logic_vector(3 downto 0);
	f : in std_logic_vector(3 downto 0);
	g : in std_logic_vector(3 downto 0);
	h : in std_logic_vector(3 downto 0);
	i : out std_logic_vector(3 downto 0);
	WR_INPUT : in std_logic;
	FU_0_MUX_A_SEL : in std_logic_vector(1 downto 0);
	FU_0_MUX_B_SEL : in std_logic_vector(1 downto 0);
	FU_1_MUX_A_SEL : in std_logic_vector(2 downto 0);
	FU_1_MUX_B_SEL : in std_logic_vector(2 downto 0);
	FU_2_MUX_A_SEL : in std_logic_vector(1 downto 0);
	FU_2_MUX_B_SEL : in std_logic_vector(1 downto 0);
	REG_0_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_1_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_2_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_3_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_4_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_5_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_6_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_7_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_8_MUX_SEL : in std_logic_vector(1 downto 0);
	REG_9_MUX_SEL : in std_logic_vector(1 downto 0);
	clear : in std_logic;
	clock : in std_logic);
end datapath_toyexample;

architecture toyexample_arch of datapath_toyexample is

--BEGINNING OF SIGNALS

	signal FU_0_A_IN : std_logic_vector(3 downto 0);
	signal FU_0_B_IN : std_logic_vector(3 downto 0);
	signal FU_0_OUT : std_logic_vector(3 downto 0);
	signal FU_1_A_IN : std_logic_vector(3 downto 0);
	signal FU_1_B_IN : std_logic_vector(3 downto 0);
	signal FU_1_OUT : std_logic_vector(3 downto 0);
	signal FU_2_A_IN : std_logic_vector(3 downto 0);
	signal FU_2_B_IN : std_logic_vector(3 downto 0);
	signal FU_2_OUT : std_logic_vector(3 downto 0);
	signal REG_0_IN : std_logic_vector(3 downto 0);
	signal REG_0_OUT : std_logic_vector(3 downto 0);
	signal REG_1_IN : std_logic_vector(3 downto 0);
	signal REG_1_OUT : std_logic_vector(3 downto 0);
	signal REG_2_IN : std_logic_vector(3 downto 0);
	signal REG_2_OUT : std_logic_vector(3 downto 0);
	signal REG_3_IN : std_logic_vector(3 downto 0);
	signal REG_3_OUT : std_logic_vector(3 downto 0);
	signal REG_4_IN : std_logic_vector(3 downto 0);
	signal REG_4_OUT : std_logic_vector(3 downto 0);
	signal REG_5_IN : std_logic_vector(3 downto 0);
	signal REG_5_OUT : std_logic_vector(3 downto 0);
	signal REG_6_IN : std_logic_vector(3 downto 0);
	signal REG_6_OUT : std_logic_vector(3 downto 0);
	signal REG_7_IN : std_logic_vector(3 downto 0);
	signal REG_7_OUT : std_logic_vector(3 downto 0);
	signal REG_8_IN : std_logic_vector(3 downto 0);
	signal REG_8_OUT : std_logic_vector(3 downto 0);
	signal REG_9_IN : std_logic_vector(3 downto 0);
	signal REG_9_OUT : std_logic_vector(3 downto 0);

begin


--BEGINNING OF FUNCTIONAL UNITS

	FU_0: entity work.c_subtractor
	generic map(width => 4)
	port map(input1 => FU_0_A_IN, input2 => FU_0_B_IN, output => FU_0_OUT);

	FU_1: entity work.c_multiplier
	generic map(width => 4)
	port map(input1 => FU_1_A_IN, input2 => FU_1_B_IN, output => FU_1_OUT);

	FU_2: entity work.c_multiplier
	generic map(width => 4)
	port map(input1 => FU_2_A_IN, input2 => FU_2_B_IN, output => FU_2_OUT);


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

	REG_3: entity work.c_register
	generic map(width => 4)
	port map(input => REG_3_IN, WR => WR_INPUT, output => REG_3_OUT, clear => clear, clock => clock);

	REG_4: entity work.c_register
	generic map(width => 4)
	port map(input => REG_4_IN, WR => WR_INPUT, output => REG_4_OUT, clear => clear, clock => clock);

	REG_5: entity work.c_register
	generic map(width => 4)
	port map(input => REG_5_IN, WR => WR_INPUT, output => REG_5_OUT, clear => clear, clock => clock);

	REG_6: entity work.c_register
	generic map(width => 4)
	port map(input => REG_6_IN, WR => WR_INPUT, output => REG_6_OUT, clear => clear, clock => clock);

	REG_7: entity work.c_register
	generic map(width => 4)
	port map(input => REG_7_IN, WR => WR_INPUT, output => REG_7_OUT, clear => clear, clock => clock);

	REG_8: entity work.c_register
	generic map(width => 4)
	port map(input => REG_8_IN, WR => WR_INPUT, output => REG_8_OUT, clear => clear, clock => clock);

	REG_9: entity work.c_register
	generic map(width => 4)
	port map(input => REG_9_IN, WR => WR_INPUT, output => REG_9_OUT, clear => clear, clock => clock);


--BEGINNING OF MUXES FOR FUNCTIONAL UNITS

	FU_0_MUX_A : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_0_OUT, input(7 downto 4) => FU_2_OUT, mux_select => FU_0_MUX_A_SEL, output => FU_0_A_IN);

	FU_0_MUX_B : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_1_OUT, input(7 downto 4) => h, mux_select => FU_0_MUX_B_SEL, output => FU_0_B_IN);

	FU_1_MUX_A : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 3, select_size => 2)
	port map (input(3 downto 0) => g, input(7 downto 4) => a, input(11 downto 8) => e, mux_select => FU_1_MUX_A_SEL, output => FU_1_A_IN);

	FU_1_MUX_B : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 3, select_size => 2)
	port map (input(3 downto 0) => FU_1_OUT, input(7 downto 4) => b, input(11 downto 8) => f, mux_select => FU_1_MUX_B_SEL, output => FU_1_B_IN);

	FU_2_MUX_A : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_1_OUT, input(7 downto 4) => c, mux_select => FU_2_MUX_A_SEL, output => FU_2_A_IN);

	FU_2_MUX_B : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_2_OUT, input(7 downto 4) => d, mux_select => FU_2_MUX_B_SEL, output => FU_2_B_IN);


--BEGINNING OF MUXES FOR REGISTERS

	REG_0_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_0_OUT, input(7 downto 4) => FU_1_OUT, mux_select => REG_0_MUX_SEL, output => REG_0_IN);

	REG_1_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_0_OUT, input(7 downto 4) => FU_2_OUT, mux_select => REG_1_MUX_SEL, output => REG_1_IN);

	REG_2_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_1_OUT, input(7 downto 4) => e, mux_select => REG_2_MUX_SEL, output => REG_2_IN);

	REG_3_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_2_OUT, input(7 downto 4) => a, mux_select => REG_3_MUX_SEL, output => REG_3_IN);

	REG_4_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 2, select_size => 1)
	port map (input(3 downto 0) => FU_1_OUT, input(7 downto 4) => b, mux_select => REG_4_MUX_SEL, output => REG_4_IN);

	REG_5_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => h, mux_select => REG_5_MUX_SEL, output => REG_5_IN);

	REG_6_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => g, mux_select => REG_6_MUX_SEL, output => REG_6_IN);

	REG_7_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => f, mux_select => REG_7_MUX_SEL, output => REG_7_IN);

	REG_8_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => d, mux_select => REG_8_MUX_SEL, output => REG_8_IN);

	REG_9_MUX : entity work.c_multiplexer
	generic map(width => 4, no_of_inputs => 1, select_size => 1)
	port map (input(3 downto 0) => c, mux_select => REG_9_MUX_SEL, output => REG_9_IN);

end toyexample_arch;