GCC=g++
FLAGS=--std=c++14 -I../../ -I../models

objdir=./obj

objects=${objdir}/defaultconverter.o ${objdir}/addregisterconverter.o

all: ${objdir} ${objects}

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

clean:
	rm -Rf ${objdir}

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@
