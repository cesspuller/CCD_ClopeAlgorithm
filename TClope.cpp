#include "TClope.hpp"

//! Алиас для более короткой записи
using UCluster = shared_ptr<TCluster>;

void TClope::exec()
{
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
      dataBase.writeTransactionInfo( transaction, curentCluster->getId() );
   }

   logInfo.displayProfit( profit() );

   if ( logFlag )
      logInfo.displayClusterInfo( clusters );

   int clusterId = 0;

   // Уточняющая фаза алгоритма -
   while( moved ) // Внешний цикл повторения проходов по хранилищу 
   {
      moved = false;
      dataBase.return2Begin();


      while ( !dataBase.readTransactionInfo( transaction, clusterId ) )       // Внутренний цикл, перерасчёт костов и перемещение транзакций
      {
         curentCluster = clusters[clusterId];

         nextCluster = Profit2Stage( transaction, curentCluster );

         if ( nextCluster == nullptr )        // Если выгоднее положить транзакцию в пустой кластер, не нужно её перемещать в пустой кластер
            continue;

         if ( nextCluster->getId() != curentCluster->getId() )
         {
            if ( nextCluster->getN() == 0 )       // проверить что в векторе останется по крайней мере 1 пустой кластер
               if ( curentCluster->getN() > 1 )
                  clusters.push_back( TCluster::newCluster() );

            curentCluster->deleteTransaction( transaction );
            nextCluster->insertTransaction( transaction );
            dataBase.overwriteClusterId( nextCluster->getId() );

            moved = true;
         }
      }

      logInfo.displayProfit( profit() );

      if ( logFlag )
         logInfo.displayClusterInfo( clusters );
   }
};

TClope::TClope( string readerType, string fileName, double r, bool logFlag )
{
   clusters.push_back( TCluster::newCluster() );

   fileReader = factory.create( readerType );

   fileReader->setNameFile( fileName );

   this->logFlag = logFlag;

   this->r = r;
};

UCluster TClope::Profit2Stage( vector<int>& transaction, UCluster& curentCluster )
{
   double delCost = 0.0;

   delCost = curentCluster->costDel( transaction, r );
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

      if ( addCost + delCost > maxCost )
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

