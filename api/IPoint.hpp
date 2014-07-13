
#ifndef POINTSSETANALYZER_IPOINT
#define POINTSSETANALYZER_IPOINT

#include <vector>

namespace pointSetAnalyzer {

template <typename T>
class IPoint
{
public:
   IPoint() {}

   virtual ~IPoint() {}

public:
   virtual const T& getX() const = 0;

   virtual const T& getY() const = 0;
};

typedef IPoint<int> Point;

typedef std::vector<IPoint<int>*> PointSet;

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_IPOINT
