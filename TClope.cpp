#include "TClope.hpp"
//! Алиас для более короткой записи
using UCluster = shared_ptr<TCluster>;
void TClope::exec()
{
   double f = 0.0; // PROFIT!
   vector<int> transaction;            
   UCluster nextCluster = nullptr;
   UCluster curentCluster = nullptr;
   
   // Первая фаза алгоритма
   while ( fileReader->getTransaction( transaction ) )
   {
      firstStage( transaction, curentCluster, 0 );
      
      if ( curentCluster->getN() == 0 )
         clusters.push_back( TCluster::newCluster() );

      curentCluster->insertTransaction( transaction );
   }

   f = profit();
   cout << "Profit = " << f << endl;

   // Уточняющая фаза алгоритма -
   while( moved ) // Внешний цикл повторения проходов по хранилищу 
   {
      fileReader->returnStart();

      while ( fileReader->getTransaction( transaction ))       // Внутренний цикл, перерасчёт костов и перемещение транзакций
      {
         nextCluster = Profit2Stage( transaction, curentCluster );

         if( nextCluster == nullptr )        // >??????????
            continue;

         if( nextCluster->getId() != curentCluster->getId() )
         {
            if ( nextCluster->getN() == 0 )
            {
               if ( curentCluster->getN() > 1 )
               {
                  clusters.push_back( TCluster::newCluster() );
               }
            }           // проверить что в векторе останется по крайней мере 1 пустой кластер

            curentCluster->deleteTransaction( transaction );
            nextCluster->insertTransaction( transaction );

            moved = false;
               
         }

      }
      f = profit();
      moved = true;
   }


};

TClope::TClope( string readerType, string fileName, double r )
{
   clusters.push_back( TCluster::newCluster() );

   fileReader = factory.create( readerType );

   fileReader->setNameFile( fileName );

   this->r = r;
};

UCluster& TClope::Profit2Stage( vector<int>& transaction, UCluster& bestCluster )
{
   double delCost = 0.0;

   delCost = bestCluster->costDel( transaction, r );
   shared_ptr<TCluster> curCluster = nullptr;

   firstStage( transaction, curCluster, delCost );
   
   return curCluster;
};

void TClope::firstStage( vector<int>& transaction, UCluster& bestCluster, double delCost )
{
   double maxCost = 0.0;
   double addCost = 0.0;

   for ( auto iter = clusters.begin(); iter != clusters.end(); ++iter )
   {
      addCost = ( *iter )->costAdd( transaction, this->r );
      if ( addCost > maxCost )
      {
         maxCost = addCost + delCost;
         bestCluster = *iter;
      }
   }
};

double TClope::profit()
{
   double num = 0.0;
   double den = 0.0;
   
   for ( int a = 0; a < clusters.size(); ++a )
   {
      if ( clusters[a]->getN() )
      {
         den = den + clusters[a]->getN();
         num = num + clusters[a]->getS() / pow( clusters[a]->getW(), r ) * clusters[a]->getN();
      }
   }
   
   return ( abs( den ) > 1e-5 ) ? den / num : 0.0;
};

