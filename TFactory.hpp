#ifndef _T_HPP_FACTORY_READER_
#define _T_HPP_FACTORY_READER_

#include <string>
#include <map>
#include "TBaseReader.hpp"
#include "TReader.hpp"

using namespace std;

//! Интерфейс для создателя объектов чтения из файла
class TIAbstractReadOnDeviceCreator
{
   public:

   //! Виртуальный деструктор 
   virtual ~TIAbstractReadOnDeviceCreator() = default;

   //! Функция создания объектов
   virtual TBaseReader* create() const = 0;
};

//! Шаблонный класс создания объектов 
template<typename readerType>
class TReadOnDeviceCreator final : public TIAbstractReadOnDeviceCreator
{
   //! Функция создания объектов
   TBaseReader* create() const override
   {
      return new readerType();
   };
};

//! Фабрика объектов 
class TFactory
{
   protected:

   typedef map<string, TIAbstractReadOnDeviceCreator*> factoryMap;     //<! Сокращение записи 
   factoryMap factory;                                                 //<! Хранилище доступных объектов 

   public:

   //! Конструктор         
   TFactory()
   {
      this->add<TReader>( mashroomType );
   };

   //! Деструктор 
   ~TFactory()
   {
   };

   //! Функция добавления возможных комбинаций [ключ-класс]
   //! id - тип класс для поиска ключа
   template<typename readerType>
   void add( const string& id )
   {
      factoryMap::iterator it = factory.find( id );

      if ( it == factory.end() )
         factory[id] = new TReadOnDeviceCreator<readerType>;
   };

   //! Функция создания объектов по id
   //! findKeyParams - структура параметров для преобразования Фурье
   //! return - указатель на объект фабрики
   TBaseReader* create( string typeReader )
   {
      factoryMap::iterator it = factory.find( typeReader );

      if ( it != factory.end() )
         return it->second->create();

      return nullptr;
   };

   private:

   const string mashroomType = "MR";              //!< Идентификатор для класса чтения "задача про грибы"  
};

#endif // _T_HPP_FACTORY_READER_

