#ifndef _T_HPP_READER_
#define _T_HPP_READER_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "TBaseReader.hpp"

using namespace std;

//! Класс отвечающий за считывание данных из файла, который необходимо подвергнуть алгоритму кластеризации
//! Этот класс симулирует работу базы данных.
//! Совместим с форматом файла txt, в котором 1 транзакция записана в строчку
//! и содержит буквенные символы разделённые запятой
//! Используется для чтения данных типовой задачи про грибы
class TReader : public TBaseReader
{
   public:

      TReader() = default;

      ~TReader();

      //! Функция устанавливает имя считываемого файла(сим. БД)
      void setNameFile ( string fileName ) override;

      //! Функция получения одной транзакции из файла(БД).
      //! transaction - Вектор целочисленных значений считаной транзакции.
      //! return - достигнут ли конец файла 
      //! false - конец файла не достигнут
      //! true - конец файла достигнут
      bool getTransaction( vector<int>& transaction ) override;

      //! Функция возврата коретки потока ввода в начало файла
      void returnStart() override;

   private:

      const unsigned int startPos = 97;    //!< Стартовая позиция буквенного (не заглавного) символа в ASCI таблице
      const int eAlphaVol = 26;           //!< (english alphabet volume) Количество букв в аглийском алфавите. 
      string fileName;                       //!< Имя считываемого файла.
      string fileLine;                       //!< Считанная из файла(БД) строка
      ifstream fileManager;                  //!< Объект класса для работы с потоком ввода.
};

#endif // _T_HPP_READER_