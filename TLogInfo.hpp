#ifndef _T_LOG_INFO_HPP_
#define _T_LOG_INFO_HPP_

#include <string>
#include <iostream>
#include "TCluster.hpp"

using namespace std;
using ULogCluster = vector<shared_ptr<TCluster>>;

class TLogInfo
{
   public:
      
      //! Конструктор по умолчанию
      TLogInfo() = default;

      //! Деструктор по умолчанию
      ~TLogInfo() = default;

      //! Функция вывода информации о состоянии кластеров
      //! log - текущее состояние кластеров 
      void displayClusterInfo( ULogCluster& log );

      //! Функция отображения профита
      //! prof - профит
      void displayProfit( double prof );

   private:

      string headlineLittle = "=====================";                           //!< Разделители 
      string headlineBig = "===============================================";
      int counter = 0;                                                           //!< Счётчик вывода 
};

#endif // !_T_LOG_INFO_HPP_
