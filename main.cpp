
#include "./src/CPointSetAnalyzerFacade.hpp"
#include "./api/IPointSetFileInput.hpp"
#include "./api/IOuterPerimeterFinder.hpp"
#include <iostream>

int main()
{
   pointSetAnalyzer::CPointSetAnalyzerFacade pointSetAnalyzerFacade;

   pointSetAnalyzer::IPointSetFileInput& pointSetFileInput = pointSetAnalyzerFacade.getPointSetFileInput();
   pointSetAnalyzer::IPointSetFileInput::EFileInputStatus fileInputStatus = pointSetFileInput.setPointSetFromFile("myPoints.txt");
   if(pointSetAnalyzer::IPointSetFileInput::FILE_READ_OK != fileInputStatus)
   {
      std::cerr << "Error: Status: " <<  fileInputStatus << " while reading file." << std::endl;
   }
   else
   {
      std::cout << "Input file read." << std::endl;
      pointSetAnalyzer::IOuterPerimeterFinder& outerPerimeterFinder = pointSetAnalyzerFacade.getOuterPerimeterFinder();
      pointSetAnalyzer::IOuterPerimeterFinder::EFindStatus findStatus = outerPerimeterFinder.findPoints();
      if(pointSetAnalyzer::IOuterPerimeterFinder::POINTS_FOUND != findStatus)
      {
         std::cerr << "Error: Status: " <<  findStatus << " while finding outer perimeter points." << std::endl;
      }
      else
      {
         std::cout << "Outer perimeter points found." << std::endl;
         pointSetAnalyzer::IOuterPerimeterFinder::EFileHandlingStatus fileHandlingStatus = outerPerimeterFinder.writeFoundPointsToFile("myOuterPerimeterPoints.txt");
         if(pointSetAnalyzer::IOuterPerimeterFinder::FILE_WRITE_OK != fileHandlingStatus)
         {
            std::cerr << "Error: Status: " <<  fileHandlingStatus << " while handling file." << std::endl;
         }
         else
         {
            std::cout << "Outer perimeter points written to file." << std::endl;
         }
      }
   }
}

