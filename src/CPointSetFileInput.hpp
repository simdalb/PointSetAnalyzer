
#ifndef POINTSSETANALYZER_CPOINTSETFILEINPUT
#define POINTSSETANALYZER_CPOINTSETFILEINPUT

#include "../api/IPointSetFileInput.hpp"
#include "../api/IPointSetReceiver.hpp"
#include "./CPoint.hpp"
#include <string>
#include <fstream>
#include <cstdio>
#include <iostream>

namespace pointSetAnalyzer {

class CPointSetFileInput
: public IPointSetFileInput
{
public:
   CPointSetFileInput(IPointSetReceiver& pointSetReceiver);

   virtual ~CPointSetFileInput();

public:
   virtual EFileInputStatus setPointSetFromFile(const std::string& filename);

private:
   IPointSetReceiver& mPointSetReceiver;
};

} // namespace pointSetAnalyzer

#endif // POINTSSETANALYZER_CPOINTSETFILEINPUT
