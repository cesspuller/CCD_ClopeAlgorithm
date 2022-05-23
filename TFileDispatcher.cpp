#include "TFileDispatcher.hpp"

TFileDispatcher::TFileDispatcher()
{
   fileDispatcher.open( "temporary_data_base.bin", ios::binary | ios::out | ios::in );

   if ( !fileDispatcher.is_open() )
      throw logic_error( string( "TMP FILE DOESN'T NOT BE OPEN " ) );

};

TFileDispatcher::~TFileDispatcher()
{
   fileDispatcher.close();
};

void TFileDispatcher::writeTransactionInfo( vector<int>& transaction, int clusterId )
{
   fileDispatcher.write( reinterpret_cast<const char*>( &clusterId ), sizeof( int ) );

   for ( auto& elem : transaction )
       fileDispatcher.write( reinterpret_cast<const char*>( &elem ), sizeof( int ) );
   
   fileDispatcher.write( reinterpret_cast<const char*>( &sep ), sizeof( int ) );
};

bool TFileDispatcher::readTransactionInfo( vector<int>& transaction, int& clusterId )
{
   if ( fileDispatcher.eof() )
      return true;

   startPos = fileDispatcher.tellg();

   int tmpVal = 1;       // Временная переменная для записи транзакции. Равна единице чтобы зайти в первой итерации в вайл 
   transaction.clear();  

   fileDispatcher.read( reinterpret_cast< char* >( &clusterId ), sizeof( int ) );

   while ( tmpVal != 0 && !fileDispatcher.eof() )
   {
      fileDispatcher.read( reinterpret_cast< char* >( &tmpVal ), sizeof( int ) );

      if( tmpVal != 0 )
         transaction.push_back( tmpVal );
   };

   stopPos = fileDispatcher.tellp();

   return false;
};
   
void TFileDispatcher::overwriteClusterId( int clusterId )
{
   fileDispatcher.seekp( startPos );
   fileDispatcher.write( reinterpret_cast< const char* >( &clusterId ), sizeof( int ) );
   fileDispatcher.seekp( stopPos );
};

void TFileDispatcher::return2Begin()
{
   fileDispatcher.seekp( 0 );
   fileDispatcher.seekg( 0 );
};