#include "TFileDispatcher.hpp"

TFileDispatcher::TFileDispatcher()
{
   fileDispatcher.open( "temporary_data_base.bin", ios::binary | ios::out );
};

TFileDispatcher::~TFileDispatcher()
{
   fileDispatcher.close();
};

void TFileDispatcher::writeTransactionInfo( vector<int>& transaction, int clusterId )
{
   sep;
   fileDispatcher.write( reinterpret_cast<const char*>( &clusterId ), sizeof( int ) );

   for ( auto& elem : transaction )
       fileDispatcher.write( reinterpret_cast<const char*>( &elem ), sizeof( int ) );
   
   fileDispatcher.write( reinterpret_cast<const char*>( sep ), sizeof( int ) );
};
   
void TFileDispatcher::writeClusterId( int clusterId )
{
   fileDispatcher.seekp( startPos );
   fileDispatcher.write( reinterpret_cast< const char* >( &clusterId ), sizeof( int ) );
   fileDispatcher.seekp( stopPos );
   setSeekToBegin();
};

void TFileDispatcher::setSeekToBegin()
{
   fileDispatcher.seekp( 0 );
};