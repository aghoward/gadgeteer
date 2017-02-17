GCC=g++
AR=ar
FLAGS=--std=c++17 -fconcepts -I../ -L../lib -I./models -I./converters
AR_FLAGS=rcs

objdir=./obj
libdir=./lib

objects=${objdir}/registerparser.o ${objdir}/opcodeparser.o ${objdir}/assemblyparser.o ${objdir}/assemblyparserfactory.o
modelobjects=./models/${objdir}/register.o ./models/${objdir}/opcode.o
converters=./converters/${objdir}/defaultconverter.o ./converters/${objdir}/addregisterconverter.o
libs=${libdir}/libparsing.a

all: ${modelobjects} ${converters} ${objdir} ${libdir} ${objects} ${libs}

./models/%.o:
	$(MAKE) -C ./models

./converters/%.o:
	$(MAKE) -C ./converters

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

clean:
	$(MAKE) clean -C ./models
	$(MAKE) clean -C ./converters
	rm -f ${objects}
	rm -Rf ${objdir} ${libdir}

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@

${libdir}/lib%.a: ${objects} ${modelobjects} ${converters}
	$(AR) ${AR_FLAGS} $@ $^
