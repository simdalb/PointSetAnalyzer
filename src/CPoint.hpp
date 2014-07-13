
#ifndef POINTSSETANALYZER_CPOINT
#define POINTSSETANALYZER_CPOINT

#include "../api/IPoint.hpp"

namespace pointSetAnalyzer {

template <typename T>
class CPoint
: public IPoint<T>
{
public:
   CPoint()
   : mX(0)
   , mY(0)
   {}

   CPoint(const T& x,
          const T& y)
   : mX(x)
   , mY(y)
   {}

   virtual ~CPoint()
   {}

// IPoint
public:
   const T& getX() const {return mX;}

   const T& getY() const {return mY;}

private:
   T mX;
   T mY;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_CPOINT
