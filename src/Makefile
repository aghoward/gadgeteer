GCC=g++
AR=ar
FLAGS=--std=c++17 -fconcepts -I. -I./cdif -I./files -I./errorhandlers -I./headers -I./factories -I./results -I./parsing -I./parsing/models -I./parsing/converters -L./lib -L./errorhandlers/lib -L./headers/lib -L./factories/lib -L./results/lib -L./parsing/lib -L./files/lib -pthread
AR_FLAGS=rcs
objdir=./obj
libdir=./lib

objects=-lerrorhandler -lheaders -lgadgeteermodule -lfileparser -lgadgetfinder -lfactories -lbinaryfile -lparsing -lresultfactory -lresult -lfiles -lutils

all: ${objdir} ${libdir} ${libdir}/libutils.a ${libdir}/libbinaryfile.a ${libdir}/libfileparser.a ${libdir}/libgadgetfinder.a ${libdir}/libgadgeteermodule.a errorhandlerobjects headerobjects factoryobjects parsingobjects resultobjects tester

${objdir}:
	if [[ ! -d ${objdir} ]]; then mkdir ${objdir}; fi;

${libdir}:
	if [[ ! -d ${libdir} ]]; then mkdir ${libdir}; fi;

${objdir}/%.o: %.cc %.h
	$(GCC) ${FLAGS} -c $< -o $@

${libdir}/lib%.a: ${objdir}/%.o
	$(AR) ${AR_FLAGS} $@ $<

errorhandlerobjects:
	$(MAKE) -C errorhandlers

headerobjects:
	$(MAKE) -C headers

factoryobjects:
	$(MAKE) -C factories

resultobjects:
	$(MAKE) -C results

parsingobjects:
	$(MAKE) -C parsing

filesobjects:
	$(MAKE) -C files

clean:
	$(MAKE) clean -C headers
	$(MAKE) clean -C factories
	$(MAKE) clean -C results
	$(MAKE) clean -C errorhandlers
	$(MAKE) clean -C parsing
	$(MAKE) clean -C files
	rm -f tester

tester: tester.cc errorhandlerobjects headerobjects factoryobjects
	$(GCC) ${FLAGS} -rdynamic -o $@ $< ${objects}
