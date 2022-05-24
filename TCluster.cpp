#include "TCluster.hpp"

TCluster::TCluster()
{
   id = g_id++;      
}

shared_ptr<TCluster> TCluster::newCluster()
{
   return make_shared<TCluster>();
};

double TCluster::costAdd( vector<int>& transaction, double r )
{
   double result = 0.0;

   const map<int, int>::iterator end_Occ = Occ.end();

   int curentS = S + transaction.size();
   int curentW = W;
   map<int, int>::iterator elem;

   for ( int a = 0; a < transaction.size(); ++a )
   {
      elem = Occ.find( transaction[a] );

      if ( elem == end_Occ )
         ++curentW;
   }

   if ( W == 0 )
      result = curentS * ( N + 1 ) / pow( curentW, r );
   else
      result = curentS * ( N + 1 ) / pow( curentW, r ) - S * N / pow( W , r ); // Без условия скинет nan

   return result;
}

double TCluster::costDel( vector<int>& transaction, double r )
{
   double result = 0.0;

   const map<int, int>::iterator end_Occ = Occ.end();

   int curentS = S - transaction.size();
   int curentW = W;
   map<int, int>::iterator elem;

   for ( int a = 0; a < transaction.size(); ++a )
   {
      elem = Occ.find( transaction[a] );

      if ( elem == end_Occ )
         --curentW;
   }

   if ( W == 0 )
      result = -curentS * N / pow( curentW, r );
   else
      result = curentS * ( N - 1 ) / pow( curentW, r ) - S * N / pow( W, r ); // Без условия скинет nan

   return result;
};

void TCluster::insertTransaction( vector<int>& transaction )
{

   const map<int, int>::iterator occIterEnd = Occ.end();
   map<int, int>::iterator occIter;
   ++N;

   S += transaction.size();

   for ( int a = 0; a < transaction.size(); ++a )
   {
      occIter = Occ.find( transaction[a] );
      if ( occIter == occIterEnd )
      {
         Occ[transaction[a]] = 1;
         ++W;
      }
      else
         ++Occ[transaction[a]];

   }
};

void TCluster::deleteTransaction(vector<int>& transaction)
{
   --N;                                           // уменьшить кол во транзакций внутри кластера
   S -= transaction.size();   // уменьшить количество объктов внутри кластера

   const map<int, int>::iterator OccEnd = Occ.end();

   for( auto a = 0; a < transaction.size(); ++a )
   {
      auto occTmp = Occ.find( transaction[a] );

      Occ[transaction[a]] = Occ[transaction[a]] - 1;

      if ( !Occ[transaction[a]] )
         --W;

      int val = Occ[transaction[a]];

   }

}


size_t TCluster::getN()
{
   return N;
};

size_t TCluster::getS()
{
   return S;
};

size_t TCluster::getW()
{
   return W;
};

int TCluster::getId()
{
   return id;
};
