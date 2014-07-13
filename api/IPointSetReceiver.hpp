
#ifndef POINTSSETANALYZER_IPOINTSETRECEIVER
#define POINTSSETANALYZER_IPOINTSETRECEIVER

#include "./IPoint.hpp"

namespace pointSetAnalyzer {

class IPointSetReceiver
{
public:
   IPointSetReceiver() {}

   virtual ~IPointSetReceiver() {}

public:
   virtual void setPointSet(const PointSet& pointSet, const IPoint<int>* maxPoint) = 0;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_IPOINTSETRECEIVER
