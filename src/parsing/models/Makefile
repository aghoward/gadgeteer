GCC=g++
FLAGS=--std=c++14 

objdir=./obj

objects=${objdir}/register.o ${objdir}/opcode.o

all: ${objdir} ${objects}

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

clean:
	rm -Rf ${objdir} ${libdir}

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@
