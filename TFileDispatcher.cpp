#include "TFileDispatcher.hpp"

TFileDispatcher::TFileDispatcher()
{
   fileDispatcher.open( "temporary_data_base.bin", ios::binary | ios::out | ios::in );

   if ( !fileDispatcher.is_open() )
   {
      cout << "TMP FILE DOESN'T NOT BE OPEN \n Please add file 'temporary_data_base.bin' in folder.";
      exit(1);
   }
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

   if ( fileDispatcher.eof() )
      return true;

   while ( tmpVal != 0 && !fileDispatcher.eof() )
   {
      fileDispatcher.read( reinterpret_cast< char* >( &tmpVal ), sizeof( int ) );

      if( tmpVal != 0 )
         transaction.push_back( tmpVal );
   };

   stopPos = fileDispatcher.tellg();
   
   if ( fileDispatcher.eof() )
      return true;

   return false;
};
   
void TFileDispatcher::overwriteClusterId( int clusterId )
{
   fileDispatcher.seekp( startPos );
   fileDispatcher.write( reinterpret_cast< const char* >( &clusterId ), sizeof( int ) );
   fileDispatcher.seekp( stopPos );
   fileDispatcher.seekg( stopPos );
};

void TFileDispatcher::return2Begin()
{
   fileDispatcher.clear();
   fileDispatcher.seekp( 0 );
   fileDispatcher.seekg( 0 );
};