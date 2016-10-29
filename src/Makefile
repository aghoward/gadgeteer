GCC=g++
AR=ar
FLAGS=--std=c++14 -I. -I./errorhandlers -I./headers -I./factories -I./results -I./parsing -L./lib -L./errorhandlers/lib -L./headers/lib -L./factories/lib -L./results/lib -L./parsing/lib
AR_FLAGS=rcs
objdir=./obj
libdir=./lib

objects=-lerrorhandler -lelfheader -lfileparser -lgadgetfinder -lelfheaderfactory -lprogramheaderfactory -lsectionheaderfactory -lprogramheader -lsectionheader -lbinaryfile -lparsing -lresultfactory -lresult -lutils

all: ${objdir} ${libdir} ${libdir}/libutils.a ${libdir}/libbinaryfile.a ${libdir}/libfileparser.a ${libdir}/libgadgetfinder.a errorhandlerobjects headerobjects factoryobjects parsingobjects resultobjects tester

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

clean:
	$(MAKE) clean -C headers
	$(MAKE) clean -C factories
	$(MAKE) clean -C results
	$(MAKE) clean -C errorhandlers
	$(MAKE) clean -C parsing
	rm -f tester

tester: tester.cc errorhandlerobjects headerobjects factoryobjects
	$(GCC) ${FLAGS} -rdynamic -o $@ $< ${objects}
