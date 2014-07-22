
include ./makefile.inc

SUBDIRS := src/private
LIBRARY := pointSetAnalyzer
SOURCES := main.cpp
OBJECTS := main.o

$(OBJECTS): $(SOURCES)
	$(CC) -c $(SOURCES) $(CFLAGS)

all: $(OBJECTS)
	@for subdir in $(SUBDIRS); do \
		cd $$subdir && $(MAKE) all; \
	done
	$(CC) -o points.exe $(OBJECTS) -L$(SUBDIRS) -l$(LIBRARY) $(CFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f *.bak
	rm -f *.stackdump
	rm -f main.o
	@for subdir in $(SUBDIRS); do \
		cd $$subdir && $(MAKE) clean; \
	done

depend:
	makedepend $(SOURCES)
	@for subdir in $(SUBDIRS); do \
		cd $$subdir && $(MAKE) depend; \
	done

main.o: ./src/CPointSetAnalyzerFacade.hpp ./src/./CPointSetFileInput.hpp
main.o: ./src/./../api/IPointSetFileInput.hpp
main.o: ./src/./../api/IPointSetReceiver.hpp ./src/./../api/./IPoint.hpp
main.o: ./src/././CPoint.hpp ./src/././../api/IPoint.hpp
main.o: ./src/./COuterPerimeterFinder.hpp
main.o: ./src/./../api/IOuterPerimeterFinder.hpp
main.o: ./src/./../api/./IOuterPerimeterFinder.hpp
main.o: ./api/IPointSetAnalyzerFacade.hpp ./api/./IPointSetFileInput.hpp
main.o: ./api/IPointSetFileInput.hpp ./api/IOuterPerimeterFinder.hpp
