GCC=g++
AR=ar
FLAGS=--std=c++14 -I../ -L../lib
AR_FLAGS=rcs

objdir=./obj
libdir=./lib
objects=${objdir}/elfheader.o ${objdir}/programheader.o ${objdir}/sectionheader.o
libs=${libdir}/libelfheader.a ${libdir}/libprogramheader.a ${libdir}/libsectionheader.a

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

${libdir}/lib%.a: ${objdir}/%.o
	$(AR) ${AR_FLAGS} $@ $<
