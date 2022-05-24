// FIXME: Сделать DLL и дёргать её exe выглядит более рационально в случае алгоритма
#include "TClope.hpp"
#include "TParamReader.hpp"

int main( int argc, char* argv[] )
{
   TParamReader paramReader;
   
   if ( paramReader( argc, argv ) == -1 )
      exit(0);

   TClope clope( "MR", paramReader.getParamStruct().getFileName(), paramReader.getParamStruct().getR() );

   clope.exec();
   
   return  0;
};