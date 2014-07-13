
#include "../CPointSetAnalyzerFacade.hpp"

namespace pointSetAnalyzer {

CPointSetAnalyzerFacade::CPointSetAnalyzerFacade()
: mPointSetFileInput(*this)
, mPointSet()
, mpMaxPoint(0)
, mOuterPerimeterFinder(mPointSet, mpMaxPoint)
{}

CPointSetAnalyzerFacade::~CPointSetAnalyzerFacade()
{
   PointSet::iterator itPointSet = mPointSet.begin();
   for(; itPointSet != mPointSet.end(); itPointSet++)
   {
      if(*itPointSet)
      {
         delete *itPointSet;
         itPointSet = mPointSet.erase(itPointSet);

         if(itPointSet == mPointSet.end())
         {
            break;
         }
      }
   }
}

void CPointSetAnalyzerFacade::setPointSet(const PointSet& pointSet, const Point* pMaxPoint)
{
   mPointSet = pointSet;
   mpMaxPoint = pMaxPoint;
}

} // namespace pointSetAnalyzer
