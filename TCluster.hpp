#ifndef _T_CLUSTER_HPP_
#define _T_CLUSTER_HPP_

#include <map>
#include <memory>
#include <vector>

using namespace std;

//! Класс кластера категорийных данных
class TCluster
{
   public:

      //! Конструктор по умолчанию 
      TCluster();

      //! деструктор по умолчанию 
      ~TCluster() = default;

      //! Функция расчёта стоимости добавления транзакции в кластер
      //! return - цена добавления 
      [[nodiscard]] double costAdd( vector<int>& transaction, double r );

      //! Функция расчёта стоимости удаления транзакции из кластер
      //! return - цена удаления 
      [[nodiscard]] double costDel( vector<int>& transaction, double r );

      //! Функция добавления транзакции в кластер
      //! transaction - текущая транзакция 
      void insertTransaction( vector<int>& transaction );

      //! Функця удаления транзакции из кластера 
      //! transaction - текущая транзакция
      void deleteTransaction( vector<int>& transaction );

      //! Функция создание нового кластера
      //! return - Смарт линк на новый объект кластера
      static shared_ptr<TCluster> newCluster();

      //! геттер - Функция получения значения N
      //! return - текущее значение N 
      size_t getN();

      //! Функция получения общего количества объектов в кластере
      //! return - количество объектов в кластере S
      size_t getS();

      //! Функция получения ширины кластера
      //! return - ширина кластера W
      size_t getW();

      //! Функция, возвращающая номер кластера
      //! return - id - номер кластера
      int getId();

   private:
      
      map<int, int> Occ;         //!< количество вхождений (частота) объекта i в кластер CC;
                                 //!< Ключ - объект (символ)
                                 //!< пара? - частота вхождения объекта в кластер  
                                 
      size_t N = 0;              //!< Количество транзакций в кластере
      size_t S = 0;              //!< Количество объектов в кластере 
      size_t W = 0;              //!< Ширина кластера 

      
      inline static int g_id = 0; //!< Счётчик кол-ва Кластеров.
      int id = 0;                //!< Идентификатор текущей транзакции 
};

#endif // _T_CLUSTER_HPP_