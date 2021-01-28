LIB = firewall
EXEC = firewall.exe
OTHER_LIB = input

LIB_OBJS = string.cpp field.cpp ip.cpp port.cpp 
APP_OBJS = main.cpp 

CXX = g++  # C compiler
CXXFLAGS = -Wall -Wextra -L. -g 
LDFLAGS = -fPIC -shared 
RM = rm -f   


all:${EXEC}

$(LIB):
	$(CXX) ${CXXFLAGS} ${LDFLAGS} ${LIB_OBJS} -o lib${LIB}.so


${EXEC}: ${LIB} 
	$(CXX) ${CXXFLAGS} ${APP_OBJS} -o ${EXEC} -l$(LIB) -l$(OTHER_LIB)

# We usually have a "clean" rule to delete any automatically generated files
clean:
	-${RM} ${LIB} ${EXEC} 