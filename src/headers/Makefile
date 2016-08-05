GCC=g++
FLAGS=--std=c++11

objdir=./obj
objects=${objdir}/utils.o ${objdir}/elfheader.o ${objdir}/programheader.o

all: ${objdir} ${objects}

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

clean:
	rm -f ${objects}
	rm -Rf ${objdir}

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@
