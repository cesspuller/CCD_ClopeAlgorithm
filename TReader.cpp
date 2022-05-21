#include "TReader.hpp"
//TODO: надо в этом файле кодировку поправить и во всех остальных дл€ гита

void TReader::setNameFile( string fileName )
{
   fileManager.open( fileName );
   char c;

   fileManager >> c;          // стереть utf заголовок txt
   fileManager >> c;
   fileManager >> c;

   if ( !fileManager.is_open() )
   {
      cout << "File is not open. Check him" << endl;             //! TODO: написать сюда комент
      exit( 1 );
   }
}

bool TReader::getTransaction( vector<int>& transaction )
{
   //if ( fileManager.eof() )
   //   return true;
   //
   //getline( fileManager, fileLine );


   //transaction.clear();

   //fileLine.erase( remove_if( fileLine.begin(),       // ”даление не алфавитных символов с использованием предиката
   //                fileLine.end(),
   //                []( char c )
   //                {
   //                   if ( c == ',' )
   //                      return true;
   //                   else
   //                      return false;
   //                } ),
   //                fileLine.end() );

   //size_t sizeTrans = fileLine.size();
   //transaction.resize( sizeTrans );       // тут скорее всего ресайз надо 1 раз всего делать( Ќо это не точно )

   //int pos = 0;                           // позици€ значени€ в транзакции t

   //for ( int a = 0; a < sizeTrans; ++a )
   //{
   //   transaction[a] = static_cast< int >( fileLine[a] ) + 26 * pos - start_char + 1;
   //   ++pos;
   //}

   //return false;
   string line;
   char c;
   int pos = 0;
   getline( fileManager, line );
   istringstream iss( line );          // скорее всего с обычной стрингой будет работать так же 
   transaction.clear();                // ќчень опасное место - если каждый божий раз происходит реолокаци€ вектора то надо переделывать
   while ( true )
   {
      iss >> c;

      if ( iss.eof() ) 
         break;

      if ( c == ',' )
      {
         ++pos;
      }
      else
      {
         if ( c != '?' )
         {
            unsigned int data = static_cast<int>( c ) - start_char + 1;
            data = data + 26 * pos;
            transaction.push_back( data );
         }
      }

   };

   if ( transaction.size() == 0 )
      return false;

   return true;

};

TReader::~TReader()
{
   fileManager.close();
};

void TReader::returnStart()
{
   fileManager.seekg( 0 );

};

