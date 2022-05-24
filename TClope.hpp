#ifndef _T_CLOPE_HPP_
#define _T_CLOPE_HPP_

#include "vector"
#include <memory>
#include "TCluster.hpp"
#include "TFactory.hpp"
#include "TFileDispatcher.hpp"
#include "TLogInfo.hpp"

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
      //! logFlag - флаг вывода отладочной информации 
      TClope( string typeReader, string fileName, double r, bool logFlag );

      //! Функция выполнения кластеризации алгоритмом Clope
      [[noreturn]] void exec();

   private:

      //! Алиас для более короткой записи
      using UCluster = shared_ptr<TCluster>;

      //! Общая реализация формулы вычисления "profit"
      void firstStage( vector<int>& transaction, UCluster& bestCluster, double delCost );
        
      //! Нахождение максимального выигрыша для второй стадии(фазы) алгоритма
      //! transaction - Текущая транзакция.
      //! curentCluster - Текущий кластер
      //! return - ссылка на текущий выбранный кластер, для которого стоимость данной транзакции лучшая 
      [[nodiscard]] UCluster Profit2Stage( vector<int>& transaction, UCluster& curentCluster );

      //!< Функция проверяет наличие избыточных пустых кластеров и удаляет их 
      void deleteEmptyClusters();

      //! Функция вычисления профита
      double profit();

      TFactory factory;                        //!< Объект фабрики создания классов чтения
      TLogInfo logInfo;                        //!< Класс отвечающий за вывод отдадочной информации в консоль
      TBaseReader* fileReader;                 //!< Указатель на базовый класс объектов ( симуляция БД )
      vector<UCluster> clusters;               //!< Вектор кластеров
      TFileDispatcher dataBase;                //!< Объект класса необходимый для сохранения и считывания информации (симуляция БД)
      double r = 0;                            //!< Коэффициент отталкивания  
      bool logFlag = false;                    //!< Флаг вывода отладочной информации 
      bool moved = true;                       //!< Логическая переменная необходима для уточняющих итераций
};

#endif // _T_CLOPE_HPP_