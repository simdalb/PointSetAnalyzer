
include ../../makefile.inc

OBJECTS := COuterPerimeterFinder.o CPointSetAnalyzerFacade.o CPointSetFileInput.o
SOURCES := $(OBJECTS:%.o=%.cpp)
LIBRARY := libpointSetAnalyzer.a

all: $(LIBRARY)

$(OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(LIBRARY): $(OBJECTS)
	ar rvs libpointSetAnalyzer.a $(OBJECTS)

clean:
	@for obj in $(OBJECTS); do \
		echo "Removing $$obj"; \
		rm -f $$obj; \
	done
	rm -f $(LIBRARY)

depend:
	makedepend $(SOURCES)

COuterPerimeterFinder.o: ../COuterPerimeterFinder.hpp
COuterPerimeterFinder.o: ../../api/IOuterPerimeterFinder.hpp
COuterPerimeterFinder.o: ../../api/./IOuterPerimeterFinder.hpp
COuterPerimeterFinder.o: ../../api/IPointSetReceiver.hpp
COuterPerimeterFinder.o: ../../api/./IPoint.hpp ../../api/IPoint.hpp
CPointSetAnalyzerFacade.o: ../CPointSetAnalyzerFacade.hpp
CPointSetAnalyzerFacade.o: .././CPointSetFileInput.hpp
CPointSetAnalyzerFacade.o: .././../api/IPointSetFileInput.hpp
CPointSetAnalyzerFacade.o: ../../api/IPointSetReceiver.hpp
CPointSetAnalyzerFacade.o: ../../api/./IPoint.hpp ../././CPoint.hpp
CPointSetAnalyzerFacade.o: ../../api/IPoint.hpp
CPointSetAnalyzerFacade.o: .././COuterPerimeterFinder.hpp
CPointSetAnalyzerFacade.o: ../../api/IOuterPerimeterFinder.hpp
CPointSetAnalyzerFacade.o: ../../api/./IOuterPerimeterFinder.hpp
CPointSetAnalyzerFacade.o: ../../api/IPointSetAnalyzerFacade.hpp
CPointSetAnalyzerFacade.o: ../../api/./IPointSetFileInput.hpp
CPointSetFileInput.o: ../CPointSetFileInput.hpp
CPointSetFileInput.o: .././../api/IPointSetFileInput.hpp
CPointSetFileInput.o: ../../api/IPointSetReceiver.hpp ../../api/./IPoint.hpp
CPointSetFileInput.o: ../././CPoint.hpp ../../api/IPoint.hpp
