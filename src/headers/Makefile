GCC=g++
AR=ar
FLAGS=--std=c++11
AR_FLAGS=rcs

objdir=./obj
libdir=./lib
objects=${objdir}/utils.o ${objdir}/elfheader.o ${objdir}/programheader.o
libs=${libdir}/libutils.a ${libdir}/libelfheader.a ${libdir}/libprogramheader.a

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