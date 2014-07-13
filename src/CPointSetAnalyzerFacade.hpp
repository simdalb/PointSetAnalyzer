
#ifndef POINTSSETANALYZER_CPOINTSETANALYZERFACADE
#define POINTSSETANALYZER_CPOINTSETANALYZERFACADE

#include "./CPointSetFileInput.hpp"
#include "./COuterPerimeterFinder.hpp"
#include "../api/IPointSetAnalyzerFacade.hpp"
#include "../api/IPointSetReceiver.hpp"
#include <iostream>

namespace pointSetAnalyzer {

class CPointSetAnalyzerFacade
: public IPointSetAnalyzerFacade
, public IPointSetReceiver
{
public:
   CPointSetAnalyzerFacade();

   virtual ~CPointSetAnalyzerFacade();

// IPointSetAnalyzerFacade
public:
   virtual IPointSetFileInput& getPointSetFileInput() {return mPointSetFileInput;}

   virtual IOuterPerimeterFinder& getOuterPerimeterFinder() {return mOuterPerimeterFinder;}

// IPointSetReceiver
public:
   virtual void setPointSet(const PointSet& pointSet, const IPoint<int>* pMaxPoint);

private:
   CPointSetFileInput    mPointSetFileInput;
   PointSet              mPointSet;
   const IPoint<int>*    mpMaxPoint;
   COuterPerimeterFinder mOuterPerimeterFinder;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_CPOINTSETANALYZERFACADE
