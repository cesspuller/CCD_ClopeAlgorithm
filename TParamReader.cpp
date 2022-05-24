#include <iostream>
#include "TParamReader.hpp"

int TParamReader::operator()( int argc, char* argv[] )
{
   store( command_line_parser( argc, argv ).options( allOption ).allow_unregistered().run(), variableMaps );
   notify( variableMaps );

   if ( variableMaps.count( keyHelp ) )
   {
      cout << allOption << endl;

      return -1;
   }

   if ( !variableMaps.count( keyInputFile ) )
   {
      cout << allOption << endl;

      cout << "Enter input file!"<< endl;

      return -1;
   }

   if ( !variableMaps.count( keyLogFlag ) )
   {
      logFlag = 0;
   }

   if ( !variableMaps.count( keyRepulsion ) )
   {
      cout << allOption << endl;

      cout << "Enter repulsion key !" << endl;

      return -1;
   }

   if ( !checkParam( variableMaps ) )
      return -1;

   return 0;
};

bool TParamReader::checkParam( const variables_map& variableMap )
{
   fileName = variableMap[keyInputFile].as<string>();                //! TODO: В целом можно добавить проверку на файл 
   r = variableMap[keyRepulsion].as<double>();
   logFlag = variableMap[keyLogFlag].as<int>();

   bool fl1 = false;
   bool fl2 = false;

   if ( logFlag == 1 )
      fl1 = true;

   if ( logFlag == 0 )
      fl1 = true;

   if ( !fl1 && !fl2 )
   {
      cout << "The output flag must take values 1 or 0" << endl;

      return false;
   }

   if ( r < 1 )                // Отталкивание должно быть положительным значением больше единицы 
   {
      cout << "The repuslion must be a positive value rheater than one" << endl;
      return false;
   }

   prStr.setFileName( fileName );
   prStr.setLogFlag( logFlag );
   prStr.setR( r );

   return true;
};

TParamReader::TParamReader() : genericOption( "All Optional" )
{
   genericOption.add_options()
      ( optionHelp.c_str(), "Show help \n" )
      ( optionInputFile.c_str(), value<string>( &fileName ), " Input file whith data" )
      ( optionRepulsionCoeff.c_str(), value<double>( &r ), " Coeff repulsion " )
      ( optionLogFlag.c_str(), value<int>( &logFlag ), " Output log information \n Takes the values 0 or 1" );
      
   allOption.add( genericOption );
};

TParamReader::~TParamReader()
{

};

TParamStruct& TParamReader::getParamStruct()
{
   return prStr;
};


string TParamStruct::getFileName()
{
   return fileName;
};

double TParamStruct::getR()
{
   return r;
};

int TParamStruct::getLogFlag()
{
   return logFlag;
};

void TParamStruct::setFileName( string fileName )
{
   this->fileName = fileName;
};

void TParamStruct::setLogFlag( int logFlag )
{
   this->logFlag = logFlag;
};

void TParamStruct::setR( double r )
{
   this->r = r;
};