LIBRARY ieee;
  use ieee.std_logic_1164.ALL;

entity c_and is
  generic (width : integer := 1);
  port (input1 : std_logic_vector((width -1)  downto 0);
        input2 : std_logic_vector((width -1)  downto 0);
        output : out std_logic_vector((width -1) downto 0));
end  c_and;

architecture behavior of c_and is
begin
	 P0 : process(input1,input2)
          variable  result : std_logic_vector(width-1 downto 0);
        begin
          outer :
           for n in width-1 downto 0 loop
             result(n) := input1(n) and input2(n);
          end loop outer;
          output <= result;
   end process P0;

end behavior;
