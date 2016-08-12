GCC=g++
AR=ar
FLAGS=--std=c++11
AR_FLAGS=rcs

objdir=./obj
libdir=./lib
objects=${objdir}/programheaderfactory.o
libs=${libdir}/libprogramheaderfactory.a

all: ${objdir} ${objects} ${libdir} ${libs}

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

clean:
	rm -f ${objects}
	rm -Rf ${objdir} ${libdir}

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@

${libdir}/lib%.a: ${objdir}/%.o %.cc %.h
	$(AR) ${AR_FLAGS} $@ $<
