#ifndef T_HPP_BASE_READER_
#define T_HPP_BASE_READER_

#include <string>
#include <vector>

using namespace std;

//! Базовый класс для объектов чтения транзакций
class TBaseReader
{
   public:

      TBaseReader() = default;

      //! Виртуальный деструктор 
      virtual ~TBaseReader() = default;

      //! Интерфейс инициализирующей функции объекта чтения
      virtual void setNameFile( string fileName ) = 0;

      //! Интерфейс функции получения транзакции 
      virtual bool getTransaction( vector<int>& transaction ) = 0;

      //! Интерфейс функции возврата коретки потока ввода в начало файла
      virtual void returnStart() = 0;

   private:

};


#endif // T_HPP_BASE_READER_
