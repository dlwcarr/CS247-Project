CXX = g++ 			
CXXFLAGS = -g -Wall -O `pkg-config gtkmm-2.4 --cflags --libs`
OBJECTS = Card.o Command.o Game.o ComputerPlayer.o HumanPlayer.o Player.o GUI.o straights.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
