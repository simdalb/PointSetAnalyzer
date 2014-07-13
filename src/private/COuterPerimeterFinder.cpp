
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
         std::cout << "xvalue: " << (*itPointSet)->getX() << ", yvalue: " << (*itPointSet)->getY() << std::endl;
      }

      // The first outer perimeter point is the point with the largest x.
      // For multiple largest x points with the same x, get the one with largest y.
      CLargestxThenSmallesty largestxThenSmallesty;
      PointSet::iterator itOuterPerimeterPoint = std::max_element(pointSet.begin(), pointSet.end(), largestxThenSmallesty);

      mOuterPerimterPointSet.push_back(*itOuterPerimeterPoint);

      // get point set underneath (i.e. below or at the y-level of) the first outer perimeter point,
      // sorted as increasing y (equal y points sorted as decreasing x)
      CPointsBelowIny pointsBelowIny;
      std::partial_sort(pointSet.begin(), itOuterPerimeterPoint, pointSet.end(), pointsBelowIny);

      // get back the iterator for the current outer perimeter point (iterator to it was invalidated by partial_sort)
      itOuterPerimeterPoint = std::find(pointSet.begin(), pointSet.end(), mOuterPerimterPointSet.back());

      while(true)
      {
         // get next outer perimeter point. Search only the point set underneath
         CLeastdYOverdX leastdYOverdX(*itOuterPerimeterPoint);
         itOuterPerimeterPoint = std::max_element(pointSet.begin(), itOuterPerimeterPoint, leastdYOverdX);

         mOuterPerimterPointSet.push_back(*itOuterPerimeterPoint);

         if(itOuterPerimeterPoint == pointSet.begin())
         {
            // no more points to be found, break
            break;
         }
      }

      itPointSet = mOuterPerimterPointSet.begin();
      for(; itPointSet != mOuterPerimterPointSet.end(); itPointSet++)
      {
         std::cout << "1xvalue: " << (*itPointSet)->getX() << ", yvalue: " << (*itPointSet)->getY() << std::endl;
      }

      findStatus = POINTS_FOUND;
   }

   return findStatus;
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
         CLargestyThenLargestx largestyThenLargestx;
         std::sort(mOuterPerimterPointSet.begin(), mOuterPerimterPointSet.end(), largestyThenLargestx);
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

const bool COuterPerimeterFinder::CLargestxThenSmallesty::operator()(Point* pPoint1, Point* pPoint2)
{
   if(pPoint1 && pPoint2)
   {
      if(pPoint1->getX() == pPoint2->getX())
      {
         return pPoint1->getY() < pPoint2->getY();
      }
      return pPoint1->getX() < pPoint2->getX();
   }
   return false;
}

const bool COuterPerimeterFinder::CPointsBelowIny::operator()(Point* pPoint1, Point* pPoint2)
{
   if(pPoint1 && pPoint2)
   {
      if(pPoint1->getY() == pPoint2->getY())
      {
         return pPoint1->getX() < pPoint2->getX();
      }
      return pPoint1->getY() > pPoint2->getY();
   }
   return false;
}

COuterPerimeterFinder::CLeastdYOverdX::CLeastdYOverdX(const Point* pPoint)
: mpPoint(pPoint)
{}

const bool COuterPerimeterFinder::CLeastdYOverdX::operator()(Point* pPoint1, Point* pPoint2)
{
   if(mpPoint && pPoint1 && pPoint2)
   {
      int dx1 = pPoint1->getX() - mpPoint->getX();
      int dx2 = pPoint2->getX() - mpPoint->getX();
      int dy1 = pPoint1->getY() - mpPoint->getY();
      int dy2 = pPoint2->getY() - mpPoint->getY();

      int lhs = sgn(dx1) * dy1 * abs(dx2);
      int rhs = sgn(dx2) * dy2 * abs(dx1);

      if(lhs == rhs)
      {
         return pPoint1->getY() > pPoint2->getY();
      }
      return lhs > rhs;
   }
   return false;
}

const int COuterPerimeterFinder::CLeastdYOverdX::sgn(const int val)
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

const bool COuterPerimeterFinder::CLargestyThenLargestx::operator()(Point* pPoint1, Point* pPoint2)
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
