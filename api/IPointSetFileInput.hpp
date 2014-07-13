
#ifndef POINTSSETANALYZER_IPOINTSETFILEINPUT
#define POINTSSETANALYZER_IPOINTSETFILEINPUT

#include <string>

namespace pointSetAnalyzer {

class IPointSetFileInput
{
public:
   IPointSetFileInput() {}

   virtual ~IPointSetFileInput() {}

public:
   enum EFileInputStatus
   {
      FILE_READ_OK = 1,
      FILE_READ_NOT_OK,
      BAD_FORMAT
   };

public:
   virtual EFileInputStatus setPointSetFromFile(const std::string& filename) = 0;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_IPOINTSETFILEINPUT
