
#ifndef POINTSSETANALYZER_COUTERPERIMETERFINDER
#define POINTSSETANALYZER_COUTERPERIMETERFINDER

#include "../api/IOuterPerimeterFinder.hpp"
#include "../api/IPointSetReceiver.hpp"
#include "../api/IPoint.hpp"
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

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
   template<typename DirectionalComparator, typename AngularComparator>
   void calculateQuadrant(PointSet& pointSet, PointSet::iterator& itOuterPerimeterPoint);

private:
   class CSign
   {
   public:
      const int operator()(const int val);
   };

private:
   class CComparatorXLeft
   {
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   };

   class CComparatorYDown
   {
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   };

   class CComparatorYUp
   {
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   };

private:
   class CComparatorBottomRight
   {
   public:
      CComparatorBottomRight(const Point* pPoint);
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   private:
      const Point* mpPoint;
      CSign        mSign;
   };

private:
   class CComparatorTopLeft
   {
   public:
      CComparatorTopLeft(const Point* pPoint);
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   private:
      const Point* mpPoint;
      CSign        mSign;
   };

   class CComparatorBottomLeft
   {
   public:
      CComparatorBottomLeft(const Point* pPoint);
   public:
      const bool operator()(Point* pPoint1, Point* pPoint2);
   private:
      const Point* mpPoint;
      CSign        mSign;
   };

private:
   const PointSet& mPointSet;
   const Point*&   mpMaxPoint;
   PointSet        mOuterPerimterPointSet;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_COUTERPERIMETERFINDER
