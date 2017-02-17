GCC=g++
AR=ar
FLAGS=--std=c++17 -fconcepts
AR_FLAGS=rcs
OBJDIR=./obj
LIBDIR=./lib

objects=${OBJDIR}/errorhandler.o ${OBJDIR}/handlers.o
libraries=${LIBDIR}/liberrorhandler.a

all: ${OBJDIR} ${LIBDIR} ${objects} ${libraries}

clean:
	rm -rf ${OBJDIR} ${LIBDIR}

${OBJDIR}:
	if [[ ! -d ${OBJDIR} ]]; then mkdir ${OBJDIR}; fi;

${LIBDIR}:
	if [[ ! -d ${LIBDIR} ]]; then mkdir ${LIBDIR}; fi;

${OBJDIR}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -o $@ -c $<

${LIBDIR}/lib%.a: ${objects}
	$(AR) ${ARFLAGS} $@ ${objects}
