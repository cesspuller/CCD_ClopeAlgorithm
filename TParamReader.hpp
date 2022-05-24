#ifndef _T_PARAM_READER_HPP_
#define _T_PARAM_READER_HPP_

#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem/directory.hpp>

using namespace std;
using namespace boost::program_options;
using namespace boost::filesystem;

//! Структура входных параметров 
struct TParamStruct
{
   public:

      //! Конструктор по умолчанию 
      TParamStruct() = default;

      //! Деструктор по умолчанию 
      ~TParamStruct() = default;

      //! "Геттер" коэф-а отталкивания
      double getR();

      //! "Геттер" флага вывода информации 
      int getLogFlag();

      //! "Геттер" имени файла
      string getFileName();

      //! "Сетер" коэф-а отталкивания
      void setR( double r);

      //! "Сетер" флага вывода информации 
      void setLogFlag( int logFlag);

      //! "Сетер" имени файла
      void setFileName( string fileName );

   private:

      double r = 0.0;      //!< Коэффициент отталкивания
      int logFlag = 0;     //!< Флаг вывода отладочной информации 
      string fileName;     //!< Имя файла

};

//! Класс, реализующий чтение параметров из командной строки
class TParamReader
{
   public:
      
      //! Конструктор 
      TParamReader();

      //! Деструктор 
      ~TParamReader();

      //! Основной оператор чтения параметров командной строки
      //! argc - Количество передаевых параметров
      //! argv - Указатель на строковые параметры, которые были введение в командную строку  
      //! return - Результат проверки параметров
      int operator()( int argc, char* argv[] );

      //!< Функция передачи в программу введёных в консоль параметров 
      //!< return - Входные параметры.
      TParamStruct& getParamStruct();

   private:

      //! Функция проверки введных параметров на валидность 
      //! variableMaps - Контейнер map с введёными параметрами
      //! return - результат проверки параметров
      //!   true - параметры валидны
      //!   false - параметры не валидны 
      bool checkParam( const variables_map& variableMaps );

      options_description genericOption;                            //!< Описание общих опций вводимых в командную строку 
      options_description allOption;                                //!< Описание всех хранимых и доступных опций 
      variables_map variableMaps;                                   //!< Контейнер map с введёными параметрами
      TParamStruct prStr;                                           //!< Структура входных параметров


      string fileName;                                              //!< Имя файла, в котором лежат данные подлежащие кластеризации  

      const string keyHelp = "help";                                //!< Вывод информации о приложении  
      const string optionHelp = keyHelp + ",h";                     //!< ( доступные опции )  

      const string keyInputFile = "input";                          //!< Входной файл 
      const string optionInputFile = keyInputFile + ",i";           //!< 

      const string keyRepulsion = "repulsion";                      //!< Коэффициент отталкивания
      const string optionRepulsionCoeff = keyRepulsion + ",r";      //!<

      const string keyLogFlag = "log";                              //!< Отладочная информация
      const string optionLogFlag = keyLogFlag + ",l";               //!< 

      double r;                                                     //!< Коэффициент отталкивания

      int logFlag = 0;                                              //!< Флаг вывода отладочной информации 
};

#endif //_T_PARAM_READER_HPP_