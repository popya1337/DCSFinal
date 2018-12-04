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
	signal FU_0_MUX_A_SEL : std_logic_vector(0 downto 0);
	signal FU_0_MUX_B_SEL : std_logic_vector(0 downto 0);
	signal REG_0_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_1_MUX_SEL : std_logic_vector(0 downto 0);
	signal REG_2_MUX_SEL : std_logic_vector(0 downto 0);
	signal WR_INPUT : std_logic := '1';
	signal clear :  std_logic := '0';
	signal clock :  std_logic := '0';


begin


toyexample_dp : entity work.datapath_toyexample(toyexample_arch)
	port map(
		a => a,
		b => b,
		c => c,
		WR_INPUT => WR_INPUT,
		FU_0_MUX_A_SEL => FU_0_MUX_A_SEL,
		FU_0_MUX_B_SEL => FU_0_MUX_B_SEL,
		REG_0_MUX_SEL => REG_0_MUX_SEL,
		REG_1_MUX_SEL => REG_1_MUX_SEL,
		REG_2_MUX_SEL => REG_2_MUX_SEL,
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
		wait for 20 ns;
		FU_0_MUX_A_SEL <= "0";
		FU_0_MUX_B_SEL <= "0";
		REG_0_MUX_SEL <= "0"; REG_1_MUX_SEL <= "0"; REG_2_MUX_SEL <= "0";
		a <= "0010"; b <= "0001";
		wait for 20 ns;
		FU_0_MUX_A_SEL <= "0";
		FU_0_MUX_B_SEL <= "0";
		REG_0_MUX_SEL <= "0"; REG_1_MUX_SEL <= "0"; REG_2_MUX_SEL <= "0";
		a <= "0011"; b <= "0101";
		wait for 20 ns;
		FU_0_MUX_A_SEL <= "0";
		FU_0_MUX_B_SEL <= "0";
		REG_0_MUX_SEL <= "0"; REG_1_MUX_SEL <= "0"; REG_2_MUX_SEL <= "0";
		a <= "0101"; b <= "0101";
		wait for 20 ns;
		FU_0_MUX_A_SEL <= "0";
		FU_0_MUX_B_SEL <= "0";
		REG_0_MUX_SEL <= "0"; REG_1_MUX_SEL <= "0"; REG_2_MUX_SEL <= "0";
		a <= "0010"; b <= "0001";

		wait;
	end process;



end Test;
