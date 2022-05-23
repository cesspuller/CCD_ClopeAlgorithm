#ifndef _T_PARAM_READER_HPP_
#define _T_PARAM_READER_HPP_

#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem/directory.hpp>

using namespace std;
using namespace boost::program_options;
using namespace boost::filesystem;

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

   private:

      //! Функция проверки введных параметров на валидность 
      //! variableMaps - Контейнер map с введёными параметрами
      //! return - результат проверки параметров
      //!   true - параметры валидны
      //!   false - параметры не валидны 
      bool checkParam( const variables_map& variableMaps );

      double r;                                                     //!< Коэффициент отталкивания 

      options_description genericOption;                            //!< Описание общих опций вводимых в командную строку 
      options_description allOption;                                //!< Описание всех хранимых и доступных опций 
      variables_map variableMaps;                                   //!< Контейнер map с введёными параметрами

      string fileName;                                              //!< Имя файла, в котором лежат данные подлежащие кластеризации  

      const string keyHelp = "help";                                //!< Вывод информации о приложении  
      const string optionHelp = keyHelp + ",h";                     //!< ( доступные опции )  

      const string keyInputFile = "input";                          //!< Входной файл 
      const string optionInputFile = keyInputFile + ",i";           //!< 

      const string keyRepulsion = "repulsion";                      //!< Коэффициент отталкивания
      const string optionRepulsionCoeff = keyRepulsion + ",r";      //!<

};

#endif //_T_PARAM_READER_HPP_