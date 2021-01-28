CXX	:=	clang++
CXX_FLAGS	:=	-std=c++17 -stdlib=libc++ 

BIN			:=	bin
SRC			:=	src
INCLUDE	:=	include

LIBRARIES		:=
EXECUTABLE	:=	main

all: ${BIN}/${EXECUTABLE}

${BIN}/${EXECUTABLE}: ${SRC}/*.cpp
	${CXX} ${CXX_FLAGS} -I${INCLUDE} $^ -o $@ ${LIBRARIES}
