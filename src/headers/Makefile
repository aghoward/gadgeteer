GCC=g++
AR=ar
FLAGS=--std=c++17 -fconcepts -I../ -L../lib
AR_FLAGS=rcs

objdir=./obj
libdir=./lib
objects=${objdir}/elfheader.o ${objdir}/programheader.o ${objdir}/sectionheader.o
libs=${libdir}/libheaders.a

all: ${objdir} ${libdir} ${objects} ${libs}

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

clean:
	rm -f ${objects}
	rm -Rf ${objdir} ${libdir}

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@

${libdir}/lib%.a: ${objects}
	$(AR) ${AR_FLAGS} $@ $?
