CXX = clang++ 			
CXXFLAGS = -g -Wall -MMD
OBJECTS = Card.o Command.o Game.o ComputerPlayer.o HumanPlayer.o Player.o straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
