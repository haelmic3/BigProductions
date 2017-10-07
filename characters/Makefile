C=g++ -g -Wall -Werror --std=c++11 -O3
E=.cpp
O=main.opp
P=program.elf
SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
.PHONY : clean all
all:$P
$P:$O
	$C -o $P $O $(SFML)
%.opp:%$E
	$C -c $< -o $@ $(SFML)
clean:
	rm $O $P
