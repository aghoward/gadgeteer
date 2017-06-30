GCC ?= g++
AR ?= ar

CXX_FLAGS ?= --std=c++17 -I../
AR_FLAGS ?= rcs

OBJDIR = ./obj
LIBDIR = ./lib

OBJECTS = ${OBJDIR}/filereader.o ${OBJDIR}/filesmodule.o
LIBS = ${LIBDIR}/libfiles.a

all: ${LIBDIR} ${LIBS}

clean:
	rm -Rf ${OBJDIR} ${LIBDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

${LIBDIR}:
	mkdir -p ${LIBDIR}

${OBJDIR}/%.o: %.cc %.h ${OBJDIR}
	$(GCC) ${CXX_FLAGS} -o $@ -c $<

${LIBDIR}/%.a: ${OBJECTS}
	$(AR) ${AR_FLAGS} $@ $?
