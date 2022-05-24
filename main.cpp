// FIXME: Сделать DLL и дёргать её exe выглядит более рационально в случае алгоритма
#include "TClope.hpp"
#include "TParamReader.hpp"

int main( int argc, char* argv[] )
{
   //TParamReader paramReader;
   //
   //int resultCheck = paramReader( argc, argv );
   //
   //if ( resultCheck == -1 )
   //   exit(0);

   TClope clope("MR", "Mashroom.txt", 2.6 );

   clope.exec();
   
   return  0;

};