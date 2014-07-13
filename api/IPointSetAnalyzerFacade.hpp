
#ifndef POINTSSETANALYZER_IPOINTSETANALYZERFACADE
#define POINTSSETANALYZER_IPOINTSETANALYZERFACADE

#include "./IPointSetFileInput.hpp"
#include "./IOuterPerimeterFinder.hpp"

namespace pointSetAnalyzer {

class IPointSetAnalyzerFacade
{
public:
   IPointSetAnalyzerFacade() {}

   virtual ~IPointSetAnalyzerFacade() {}

public:
   virtual IPointSetFileInput& getPointSetFileInput() = 0;

   virtual IOuterPerimeterFinder& getOuterPerimeterFinder() = 0;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_IPOINTSETANALYZERFACADE
