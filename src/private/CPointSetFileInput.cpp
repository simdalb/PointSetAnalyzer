
#include "../CPointSetFileInput.hpp"

namespace pointSetAnalyzer {

CPointSetFileInput::CPointSetFileInput(IPointSetReceiver& pointSetReceiver)
: mPointSetReceiver(pointSetReceiver)
{}

CPointSetFileInput::~CPointSetFileInput()
{}

IPointSetFileInput::EFileInputStatus CPointSetFileInput::setPointSetFromFile(const std::string& filename)
{
   EFileInputStatus fileInputStatus = FILE_READ_NOT_OK;

   std::ifstream inputFile (filename.c_str(), std::ios_base::in);
   if(inputFile.is_open())
   {
      fileInputStatus = FILE_READ_OK;
      PointSet pointSet;
      char ch;
      int xMax = 0;
      int yMax = 0;
      int ix = 0;
      int iy = 1;
      bool isNewlineFound = false;
      bool isPreviousCharNewLine = true;
      while (!inputFile.eof())
      {
         inputFile.get(ch);
         if(ch != '\n')
         {
            isPreviousCharNewLine = false;
            isNewlineFound = false;
            ix++;
            if(ch == '1')
            {
               pointSet.push_back(new CPoint<int>(ix, iy));
            }
            else if(ch != '0')
            {
               fileInputStatus = BAD_FORMAT;
               break;
            }
         }
         else
         {
            if(!isPreviousCharNewLine)
            {
               isPreviousCharNewLine = true;
               isNewlineFound = true;
               if(0 == xMax)
               {
                  xMax = ix;
               }
               else if(ix != xMax)
               {
                  fileInputStatus = BAD_FORMAT;
                  break;
               }
               ix = 0;
               iy++;
            }
         }
      }
      yMax = iy;
      if(isNewlineFound)
      {
         yMax--;
      }
      mPointSetReceiver.setPointSet(pointSet, new CPoint<int>(xMax, yMax));
      inputFile.close();
   }
   return fileInputStatus;
}

} // namespace pointSetAnalyzer
