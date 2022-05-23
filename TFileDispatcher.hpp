#ifndef _T_FILE_DISPATCHER_HPP_
#define _T_FILE_DISPATCHER_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//! Класс необходимый для сохранения информации о транзакциях и их принадлежноти к i - ому кластеру.
class TFileDispatcher
{
   public:

      //! Конструктор по умолчанию.
      TFileDispatcher();

      //! Деструктор по умолчанию.
      ~TFileDispatcher();

      //! Функция записывающая информацию о кластере во временный файл.
      //! transaction - текущая считанная транзакция. 
      //! clusterId - индентификационный номер кластера, к которому будет отнесена данная транзакция.
      void writeTransactionInfo( vector<int>& transaction, int clusterId );

      //! Коммент
      void writeClusterId( int clusterId );
      
      //! Функция возвращающая указатели чтения/записи потока ввода/вывода в начало
      void setSeekToBegin();

   private:

      streamoff startPos;                          //!< Позиция указателя в момент начала чтения 
      streamoff stopPos;                           //!< Позиция указателя в момент конца чтения 
      ofstream fileDispatcher;                     //!< поток вывода иформации о кластерах
      const int sep = 0;                           //!< разделитель между транзакциями
};

#endif //_T_FILE_DISPATCHER_HPP_
