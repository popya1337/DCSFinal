--Test Bench of toyexample.
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;


entity  toyTB is
end  toyTB;

architecture  Test of  toyTB is

	signal a : std_logic_vector(3 downto 0);
	signal b : std_logic_vector(3 downto 0);
	signal c : std_logic_vector(3 downto 0);
	signal d : std_logic_vector(3 downto 0);
	signal e : std_logic_vector(3 downto 0);
	signal f : std_logic_vector(3 downto 0);
	signal g : std_logic_vector(3 downto 0);
	signal h : std_logic_vector(3 downto 0);
	signal i : std_logic_vector(3 downto 0);
	signal FU_0_MUX_A_SEL : std_logic_vector(0 downto 0);
	signal FU_0_MUX_B_SEL : std_logic_vector(0 downto 0);
	signal FU_1_MUX_A_SEL : std_logic_vector(1 downto 0);
	signal FU_1_MUX_B_SEL : std_logic_vector(1 downto 0);
	signal FU_2_MUX_A_SEL : std_logic_vector(0 downto 0);
	signal FU_2_MUX_B_SEL : std_logic_vector(0 downto 0);
	signal REG_0_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_1_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_2_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_3_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_4_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_5_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_6_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_7_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_8_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_9_MUX_SEL : std_logic_vector(0 downto 0);
	signal WR_INPUT : std_logic := '1';
	signal clear :  std_logic := '0';
	signal clock :  std_logic := '0';


begin


toyexample_dp : entity work.datapath_toyexample(toyexample_arch)
	port map(
		a => a,
		b => b,
		c => c,
		d => d,
		e => e,
		f => f,
		g => g,
		h => h,
		i => i,
		WR_INPUT => WR_INPUT,
		FU_0_MUX_A_SEL => FU_0_MUX_A_SEL,
		FU_0_MUX_B_SEL => FU_0_MUX_B_SEL,
		FU_1_MUX_A_SEL => FU_1_MUX_A_SEL,
		FU_1_MUX_B_SEL => FU_1_MUX_B_SEL,
		FU_2_MUX_A_SEL => FU_2_MUX_A_SEL,
		FU_2_MUX_B_SEL => FU_2_MUX_B_SEL,
		REG_0_MUX_SEL => REG_0_MUX_SEL,
		REG_1_MUX_SEL => REG_1_MUX_SEL,
		REG_2_MUX_SEL => REG_2_MUX_SEL,
		REG_3_MUX_SEL => REG_3_MUX_SEL,
		REG_4_MUX_SEL => REG_4_MUX_SEL,
		REG_5_MUX_SEL => REG_5_MUX_SEL,
		REG_6_MUX_SEL => REG_6_MUX_SEL,
		REG_7_MUX_SEL => REG_7_MUX_SEL,
		REG_8_MUX_SEL => REG_8_MUX_SEL,
		REG_9_MUX_SEL => REG_9_MUX_SEL,
		clear => clear,
		clock => clock
	);

	CLK : process
	begin
		clock <= '0';
		wait for 10 ns;
		clock <= '1';
		wait for 10 ns;
	end process;

	puts : process
	begin
		wait for 65 ns;
		FU_0_MUX_A_SEL <= "1"; FU_1_MUX_A_SEL <= "01"; FU_2_MUX_A_SEL <= "1";
		FU_0_MUX_B_SEL <= "1"; FU_1_MUX_B_SEL <= "01"; FU_2_MUX_B_SEL <= "1";
		REG_0_MUX_SEL <= "1"; REG_1_MUX_SEL <= "1"; REG_2_MUX_SEL <= "1"; REG_3_MUX_SEL <= "1"; REG_4_MUX_SEL <= "1";
		REG_5_MUX_SEL <= "0"; REG_6_MUX_SEL <= "0"; REG_7_MUX_SEL <= "0"; REG_8_MUX_SEL <= "0"; REG_9_MUX_SEL <= "0";
		a <= "0010"; b <= "0001"; c <= "0001"; d <= "0001"; e <= "0001"; f <= "0001"; g <= "0001"; h <= "0001"; 
		wait for 20 ns;
		FU_0_MUX_A_SEL <= "1"; FU_1_MUX_A_SEL <= "10"; FU_2_MUX_A_SEL <= "0";
		FU_0_MUX_B_SEL <= "1"; FU_1_MUX_B_SEL <= "10"; FU_2_MUX_B_SEL <= "0";
		REG_0_MUX_SEL <= "1"; REG_1_MUX_SEL <= "1"; REG_2_MUX_SEL <= "1"; REG_3_MUX_SEL <= "0"; REG_4_MUX_SEL <= "0";
		wait for 20 ns;
		FU_0_MUX_A_SEL <= "1"; FU_1_MUX_A_SEL <= "00"; FU_2_MUX_A_SEL <= "1";
		FU_0_MUX_B_SEL <= "1"; FU_1_MUX_B_SEL <= "00"; FU_2_MUX_B_SEL <= "1";
		REG_0_MUX_SEL <= "1"; REG_1_MUX_SEL <= "0"; REG_2_MUX_SEL <= "0"; REG_3_MUX_SEL <= "0"; REG_4_MUX_SEL <= "0";
		wait for 20 ns;
		FU_0_MUX_A_SEL <= "0"; FU_1_MUX_A_SEL <= "00"; FU_2_MUX_A_SEL <= "1";
		FU_0_MUX_B_SEL <= "0"; FU_1_MUX_B_SEL <= "00"; FU_2_MUX_B_SEL <= "1";
		REG_0_MUX_SEL <= "0"; REG_1_MUX_SEL <= "0"; REG_2_MUX_SEL <= "0"; REG_3_MUX_SEL <= "0"; REG_4_MUX_SEL <= "0";
		
		wait;
	end process;
	
	
	
end Test;
