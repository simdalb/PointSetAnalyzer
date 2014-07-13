
#include "../COuterPerimeterFinder.hpp"

namespace pointSetAnalyzer {

COuterPerimeterFinder::COuterPerimeterFinder(const PointSet&     pointSet,
                                             const IPoint<int>*& pMaxPoint)
: mPointSet(pointSet)
, mpMaxPoint(pMaxPoint)
, mOuterPerimterPointSet()
{}

COuterPerimeterFinder::~COuterPerimeterFinder()
{}

COuterPerimeterFinder::EFindStatus COuterPerimeterFinder::findPoints()
{
   EFindStatus findStatus = POINTS_NOT_FOUND;

   CLargestxThenSmallesty largestxThenSmallesty;
   PointSet pointSet = mPointSet;

   {
   PointSet::const_iterator itPointSet = pointSet.begin();
   for(; itPointSet != pointSet.end(); itPointSet++)
   {
      std::cout << "xvalue: " << (*itPointSet)->getX() << ", yvalue: " << (*itPointSet)->getY() << std::endl;
   }
   }

   PointSet::iterator itLargestxPoint = std::max_element(pointSet.begin(), pointSet.end(), largestxThenSmallesty);

   if(itLargestxPoint != pointSet.end())
   {
      if(*itLargestxPoint)
      {
         std::cout << "lxvalue: " << (*itLargestxPoint)->getX() << ", lyvalue: " << (*itLargestxPoint)->getY() << std::endl;

         mOuterPerimterPointSet.push_back(*itLargestxPoint);

         CPointsBelowIny pointsBelowIny;

         std::partial_sort(pointSet.begin(), itLargestxPoint, pointSet.end(), pointsBelowIny);

         PointSet::const_iterator itPointSet = pointSet.begin();
         for(; itPointSet != itLargestxPoint; itPointSet++)
         {
            std::cout << "xvalue: " << (*itPointSet)->getX() << ", yvalue: " << (*itPointSet)->getY() << std::endl;
         }
      }
   }

   return findStatus;
}

IOuterPerimeterFinder::EFileHandlingStatus COuterPerimeterFinder::writeFoundPointsToFile(const std::string& filename)
{
   EFileHandlingStatus fileHandlingStatus = FILE_WRITE_NOT_OK;

   std::ofstream outputFile (filename.c_str(), std::ios_base::out);
   if(outputFile.is_open())
   {
      fileHandlingStatus = FILE_WRITE_OK;
      if(mpMaxPoint)
      {
         int maxX = mpMaxPoint->getX();
         int maxY = mpMaxPoint->getY();
         PointSet::const_iterator itOuterPerimterPointSet = mOuterPerimterPointSet.begin();
         PointSet::const_iterator itOuterPerimterPointSetEnd = mOuterPerimterPointSet.end();
         for(int i = 0; i < maxY; i++)
         {
            for(int j = 0; j < maxX; j++)
            {
               if(itOuterPerimterPointSet != itOuterPerimterPointSetEnd)
               {
                  if(*itOuterPerimterPointSet)
                  {
                     if((i == (*itOuterPerimterPointSet)->getY()) && (j == (*itOuterPerimterPointSet)->getX()))
                     {
                        outputFile.put('1');
                     }
                     else
                     {
                        outputFile.put('0');
                     }
                  }
                  else
                  {
                     fileHandlingStatus = INTERNAL_ERROR;
                     break;
                  }
               }
               else
               {
                  outputFile.put('0');
               }
            }
            outputFile.put('\n');
            if(INTERNAL_ERROR == fileHandlingStatus)
            {
               break;
            }
         }
      }
      else
      {
         fileHandlingStatus = INTERNAL_ERROR;
      }
      outputFile.close();
   }

   return fileHandlingStatus;
}

const bool COuterPerimeterFinder::CLargestxThenSmallesty::operator()(IPoint<int>* pPoint1, IPoint<int>* pPoint2)
{
   if(pPoint1 && pPoint2)
   {
      if(pPoint1->getX() == pPoint2->getX())
      {
         return pPoint1->getY() < pPoint2->getY();
      }
      return pPoint1->getX() < pPoint2->getX();
   }
   //DEBUG
   std::cout << "CLargestxThenSmallesty error" << std::endl;
   return false;
}

const bool COuterPerimeterFinder::CPointsBelowIny::operator()(IPoint<int>* pPoint1, IPoint<int>* pPoint2)
{
   if(pPoint1 && pPoint2)
   {
      return pPoint1->getY() >= pPoint2->getY();
   }
   //DEBUG
   std::cout << "CPointsBelowIny error" << std::endl;
   return false;
}

} // namespace pointSetAnalyzer
