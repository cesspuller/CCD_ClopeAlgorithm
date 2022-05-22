#ifndef _T_HPP_CLOPE_
#define _T_HPP_CLOPE_

#include "vector"
#include <memory>
#include "TCluster.hpp"
#include "TFactory.hpp"

using namespace std;

//! Класс масштабируемого алгоритма кластеризации CLOPE ( Clustering with sLOPE ) 
//! https://loginom.ru/blog/clope - Описание принципа работы алгоритма
//! https://algowiki-project.org/ru/Участник:Артем_Карпухин/Алгоритм_CLOPE_кластеризации_категориальных_данных
class TClope
{
   public:

      //! Конструктор по умолчанию
      //! typeReader - Тип объекта чтения.
      //! fileName - Имя читаемого файла.
      //! r - коэффициент отталкивания.
      TClope( string typeReader, string fileName, double r );

      //! Функция выполнения кластеризации алгоритмом Clope
      void exec();

      //! Алиас для более короткой записи
      using UCluster = shared_ptr<TCluster>;

   private:

      //! Общая реализация формулы вычисления "profit"
      void firstStage( vector<int>& transaction, UCluster& bestCluster, double delCost );
        
      //! Нахождение максимального выигрыша для второй стадии(фазы) алгоритма
      //! transaction - Текущая транзакция.
      //! curentCluster - Текущий кластер
      //! return - ссылка на текущий выбранный кластер, для которого стоимость данной транзакции лучшая 
      UCluster& Profit2Stage( vector<int>& transaction, UCluster& curentCluster );

      //! Функция вычисления профита
      double profit();

      bool moved = true;                      //!< Логическая переменная необходима для уточняющих итераций
      double r = 0;                            //!< Коэффициент отталкивания  
      TFactory factory;                        //!< Объект фабрики создания классов чтения
      TBaseReader* fileReader;                 //!< Указатель на базовый класс объектов ( симуляция БД )
      vector<UCluster> clusters;               //!< Вектор кластеров
   
};

#endif // _T_HPP_CLOPE_