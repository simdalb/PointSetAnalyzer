
#include "../COuterPerimeterFinder.hpp"

namespace pointSetAnalyzer {

COuterPerimeterFinder::COuterPerimeterFinder(const PointSet& pointSet,
                                             const Point*&   pMaxPoint)
: mPointSet(pointSet)
, mpMaxPoint(pMaxPoint)
, mOuterPerimterPointSet()
{}

COuterPerimeterFinder::~COuterPerimeterFinder()
{}

bool myfunction (int i,int j) { return (i<j); }

COuterPerimeterFinder::EFindStatus COuterPerimeterFinder::findPoints()
{
   EFindStatus findStatus = POINTS_NOT_FOUND;

   if(mPointSet.empty())
   {
      findStatus = POINTS_FOUND;
   }
   else
   {
      PointSet pointSet = mPointSet;


      PointSet::const_iterator itPointSet = pointSet.begin();
      for(; itPointSet != pointSet.end(); itPointSet++)
      {
         std::cout << "a(" << (*itPointSet)->getX() << ", " << (*itPointSet)->getY() << ")" << std::endl;
      }

      // The first outer perimeter point is the point with the largest x.
      // For multiple largest x points with the same x, get the one with largest y.
      PointSet::iterator itOuterPerimeterPoint = std::max_element(pointSet.begin(), pointSet.end(), CComparatorXLeft());

      calculateQuadrant<CComparatorYDown, CComparatorBottomRight>(pointSet, itOuterPerimeterPoint);
      calculateQuadrant<CComparatorXLeft, CComparatorBottomLeft>(pointSet, itOuterPerimeterPoint);
      //calculateQuadrant<CComparatorYUp, CComparatorTopLeft>(pointSet, itOuterPerimeterPoint);

      findStatus = POINTS_FOUND;
   }

   return findStatus;
}

template<typename DirectionalComparator, typename AngularComparator>
void COuterPerimeterFinder::calculateQuadrant(PointSet& pointSet, PointSet::iterator& itOuterPerimeterPoint)
{
   // get point set underneath (i.e. below or at the y-level of) the first outer perimeter point,
   // sorted as increasing y (equal y points sorted as decreasing x)
   Point* pOuterPerimeterPoint = *itOuterPerimeterPoint;

   std::cout << "Sorting around point: (" << (*itOuterPerimeterPoint)->getX() << ", " << (*itOuterPerimeterPoint)->getY() << ")" << std::endl;
   std::sort(pointSet.begin(), pointSet.end(), DirectionalComparator());

   // get back the iterator for the current outer perimeter point (iterator to it was invalidated by partial_sort)
   itOuterPerimeterPoint = std::find(pointSet.begin(), pointSet.end(), pOuterPerimeterPoint);

   PointSet::const_iterator itPointSet = pointSet.begin();
   for(; itPointSet != itOuterPerimeterPoint; itPointSet++)
   {
      std::cout << "a(" << (*itPointSet)->getX() << ", " << (*itPointSet)->getY() << ")" << std::endl;
   }
   for(; itPointSet != pointSet.end(); itPointSet++)
   {
      std::cout << "b(" << (*itPointSet)->getX() << ", " << (*itPointSet)->getY() << ")" << std::endl;
   }

   std::cout << "Starting point: (" << (*itOuterPerimeterPoint)->getX() << ", " << (*itOuterPerimeterPoint)->getY() << ")" << std::endl;

   while(true)
   {
      // get next outer perimeter point. Search only the point set underneath
      itOuterPerimeterPoint = std::max_element(pointSet.begin(), itOuterPerimeterPoint, AngularComparator(*itOuterPerimeterPoint));

      std::cout << "Next point: (" << (*itOuterPerimeterPoint)->getX() << ", " << (*itOuterPerimeterPoint)->getY() << ")" << std::endl;

      mOuterPerimterPointSet.push_back(*itOuterPerimeterPoint);

      if(itOuterPerimeterPoint == pointSet.begin())
      {
         // no more points to be found, break
         break;
      }
   }
}

IOuterPerimeterFinder::EFileHandlingStatus COuterPerimeterFinder::writeFoundPointsToFile(const std::string& filename)
{
   EFileHandlingStatus fileHandlingStatus = FILE_WRITE_NOT_OK;

   std::ofstream outputFile (filename.c_str(), std::ios_base::out);
   if(outputFile.is_open())
   {
      if(mpMaxPoint)
      {
         int maxX = mpMaxPoint->getX();
         int maxY = mpMaxPoint->getY();
         CComparatorYUp comparatorYUp;
         std::sort(mOuterPerimterPointSet.begin(), mOuterPerimterPointSet.end(), comparatorYUp);
         PointSet::const_iterator itOuterPerimterPointSet = mOuterPerimterPointSet.begin();
         for(int i = 1; i <= maxY; i++)
         {
            for(int j = 1; j <= maxX; j++)
            {
               if(itOuterPerimterPointSet != mOuterPerimterPointSet.end())
               {
                  if((i == (*itOuterPerimterPointSet)->getY()) && (j == (*itOuterPerimterPointSet)->getX()))
                  {
                     outputFile.put('1');
                     itOuterPerimterPointSet++;
                  }
                  else
                  {
                     outputFile.put('0');
                  }
               }
               else
               {
                  outputFile.put('0');
               }
            }
            outputFile.put('\n');
         }
      }
      else
      {
         fileHandlingStatus = INTERNAL_ERROR_WRITING;
      }
      outputFile.close();

      fileHandlingStatus = FILE_WRITE_OK;
   }

   return fileHandlingStatus;
}

const bool COuterPerimeterFinder::CComparatorXLeft::operator()(Point* pPoint1, Point* pPoint2)
{
   if(pPoint1 && pPoint2)
   {
      if(pPoint1 == pPoint2)
      {
         return false;
      }
      if(pPoint1->getX() == pPoint2->getX())
      {
         return pPoint1->getY() < pPoint2->getY();
      }
      return pPoint1->getX() < pPoint2->getX();
   }
   return false;
}

const bool COuterPerimeterFinder::CComparatorYDown::operator()(Point* pPoint1, Point* pPoint2)
{
   if(pPoint1 && pPoint2)
   {
      if(pPoint1 == pPoint2)
      {
         return true;
      }
      if(pPoint1->getY() == pPoint2->getY())
      {
         return pPoint1->getX() < pPoint2->getX();
      }
      return pPoint1->getY() > pPoint2->getY();
   }
   return false;
}

COuterPerimeterFinder::CComparatorBottomRight::CComparatorBottomRight(const Point* pPoint)
: mpPoint(pPoint)
, mSign()
{}

const bool COuterPerimeterFinder::CComparatorBottomRight::operator()(Point* pPoint1, Point* pPoint2)
{
   if(mpPoint && pPoint1 && pPoint2)
   {
      int dx1 = pPoint1->getX() - mpPoint->getX();
      int dx2 = pPoint2->getX() - mpPoint->getX();
      int dy1 = pPoint1->getY() - mpPoint->getY();
      int dy2 = pPoint2->getY() - mpPoint->getY();

      int lhs = mSign(dx1) * dy1 * abs(dx2);
      int rhs = mSign(dx2) * dy2 * abs(dx1);

      if(lhs == rhs)
      {
         return pPoint1->getY() >= pPoint2->getY();
      }
      return lhs > rhs;
   }
   return false;
}

COuterPerimeterFinder::CComparatorTopLeft::CComparatorTopLeft(const Point* pPoint)
: mpPoint(pPoint)
, mSign()
{}

const bool COuterPerimeterFinder::CComparatorTopLeft::operator()(Point* pPoint1, Point* pPoint2)
{
   if(mpPoint && pPoint1 && pPoint2)
   {
      int dx1 = pPoint1->getX() - mpPoint->getX();
      int dx2 = pPoint2->getX() - mpPoint->getX();
      int dy1 = pPoint1->getY() - mpPoint->getY();
      int dy2 = pPoint2->getY() - mpPoint->getY();

      int lhs = mSign(dx1) * dy1 * abs(dx2);
      int rhs = mSign(dx2) * dy2 * abs(dx1);

      if(lhs == rhs)
      {
         return pPoint1->getY() <= pPoint2->getY();
      }
      return lhs >= rhs;
   }
   return false;
}

COuterPerimeterFinder::CComparatorBottomLeft::CComparatorBottomLeft(const Point* pPoint)
: mpPoint(pPoint)
, mSign()
{}

const bool COuterPerimeterFinder::CComparatorBottomLeft::operator()(Point* pPoint1, Point* pPoint2)
{
   if(mpPoint && pPoint1 && pPoint2)
   {
      int dx1 = pPoint1->getX() - mpPoint->getX();
      int dx2 = pPoint2->getX() - mpPoint->getX();
      int dy1 = pPoint1->getY() - mpPoint->getY();
      int dy2 = pPoint2->getY() - mpPoint->getY();

      int lhs = mSign(dy1) * dx1 * abs(dy2);
      int rhs = mSign(dy2) * dx2 * abs(dy1);

      if(lhs == rhs)
      {
         return pPoint1->getX() <= pPoint2->getX();
      }
      return lhs < rhs;
   }
   return false;
}

const int COuterPerimeterFinder::CSign::operator()(const int val)
{
   if(val > 0)
   {
      return 1;
   }
   else if(val < 0)
   {
      return -1;
   }
   return 0;
}

const bool COuterPerimeterFinder::CComparatorYUp::operator()(Point* pPoint1, Point* pPoint2)
{
   if(pPoint1 && pPoint2)
   {
      if(pPoint1->getY() == pPoint2->getY())
      {
         return pPoint1->getX() < pPoint2->getX();
      }
      return pPoint1->getY() < pPoint2->getY();
   }
   return false;
}

} // namespace pointSetAnalyzer
