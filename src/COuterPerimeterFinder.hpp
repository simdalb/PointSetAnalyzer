
#ifndef POINTSSETANALYZER_COUTERPERIMETERFINDER
#define POINTSSETANALYZER_COUTERPERIMETERFINDER

#include "../api/IOuterPerimeterFinder.hpp"
#include "../api/IPointSetReceiver.hpp"
#include "../api/IPoint.hpp"
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

namespace pointSetAnalyzer {

class COuterPerimeterFinder
: public IOuterPerimeterFinder
{
public:
   COuterPerimeterFinder(const PointSet&     pointSet,
                         const IPoint<int>*& pMaxPoint);

   virtual ~COuterPerimeterFinder();

// IPointSetAnalyzerFacade
public:
   virtual EFindStatus findPoints();

   virtual EFileHandlingStatus writeFoundPointsToFile(const std::string& filename);

private:
   class CLargestxThenSmallesty
   {
   public:
      const bool operator()(IPoint<int>* pPoint1, IPoint<int>* pPoint2);
   };

   class CPointsBelowIny
   {
   public:
      const bool operator()(IPoint<int>* pPoint1, IPoint<int>* pPoint2);
   };

private:
   const PointSet&     mPointSet;
   const IPoint<int>*& mpMaxPoint;
   PointSet            mOuterPerimterPointSet;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_COUTERPERIMETERFINDER
