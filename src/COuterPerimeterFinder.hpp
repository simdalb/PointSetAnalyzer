
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
   COuterPerimeterFinder(const PointSet& pointSet,
                         const Point*&   pMaxPoint);

   virtual ~COuterPerimeterFinder();

// IPointSetAnalyzerFacade
public:
   virtual EFindStatus findPoints();

   virtual EFileHandlingStatus writeFoundPointsToFile(const std::string& filename);

private:
   class CLargestxThenSmallesty
   {
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   };

   class CPointsBelowIny
   {
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   };

   class CLeastdYOverdX
   {
   public:
      CLeastdYOverdX(const Point* pPoint);
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   private:
      const int sgn(const int val);
   private:
      const Point* mpPoint;
   };

   class CLargestyThenLargestx
   {
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   };

private:
   const PointSet& mPointSet;
   const Point*&   mpMaxPoint;
   PointSet            mOuterPerimterPointSet;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_COUTERPERIMETERFINDER
