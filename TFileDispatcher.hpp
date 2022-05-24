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

      //! Функция считывающая транзакцию и номер кластера из временного хранилища 
      //! transaction - транзакция считанная из файла и ассоциированная с - clusterId
      bool readTransactionInfo( vector<int>& transaction, int& clusterId );

      //! Функция, которая перезаписывает id кластера у последней считанной транзакции 
      void overwriteClusterId( int clusterId );

      //! Фукнция возврата кареток в начало файла 
      void return2Begin();

   private:

      fstream fileDispatcher;                      //!< поток вывода иформации о кластерах
      fpos<_Mbstatet> startPos;                    //!< Позиция указателя в момент начала чтения 
      fpos<_Mbstatet> stopPos;                     //!< Позиция указателя в момент конца чтения 
      const int sep = 0;                           //!< разделитель между транзакциями
};

#endif //_T_FILE_DISPATCHER_HPP_
