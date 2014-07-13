
#ifndef POINTSSETANALYZER_IOUTERPERIMETERFINDER
#define POINTSSETANALYZER_IOUTERPERIMETERFINDER

#include "./IOuterPerimeterFinder.hpp"
#include <string>

namespace pointSetAnalyzer {

class IOuterPerimeterFinder
{
public:
   IOuterPerimeterFinder() {}

   virtual ~IOuterPerimeterFinder() {}

public:
   enum EFindStatus
   {
      POINTS_FOUND = 1,
      POINTS_NOT_FOUND
   };

   enum EFileHandlingStatus
   {
      FILE_WRITE_OK = 1,
      FILE_WRITE_NOT_OK,
      INTERNAL_ERROR
   };

public:
   virtual EFindStatus findPoints() = 0;

   virtual EFileHandlingStatus writeFoundPointsToFile(const std::string& filename) = 0;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_IOUTERPERIMETERFINDER
