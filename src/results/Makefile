GCC=g++
AR=ar
FLAGS=--std=c++17 -fconcepts -I. -L./lib
AR_FLAGS=rcs
objdir=./obj
libdir=./lib

objects=-lresult -lresultfactory

all: ${objdir} ${libdir} ${libdir}/libresult.a ${libdir}/libresultfactory.a

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@

${libdir}/lib%.a: ${objdir}/%.o
	$(AR) ${AR_FLAGS} $@ $<

clean:
	rm -Rf ${objdir} ${libdir}

