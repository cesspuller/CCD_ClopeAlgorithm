#include "TLogInfo.hpp"

void TLogInfo::displayClusterInfo( ULogCluster& log)
{
   ++counter;
   cout << headlineBig << endl;
   cout << "cluster contetns at iteration number: " << counter << endl;
   cout << headlineBig << endl;

   for ( auto& elem : log )
   {
      cout << "Cluster ID: " << elem.get()->getId() << endl;
      cout << "Cluster N: " << elem.get()->getN() << endl;
      cout << "Cluster W: " << elem.get()->getW() << endl;
      cout << "Cluster S: " << elem.get()->getS() << endl;
      cout << headlineLittle << endl;
   }

   cout << headlineBig << endl;
};

void TLogInfo::displayProfit( double prof )
{
   cout << "Profit = " << prof << endl;
}