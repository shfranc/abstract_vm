#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "Int8.hpp"

class Factory {

public:

	typedef IOperand const * (Factory::*factory)( std::string const & value ) const;

	Factory( void );
	~Factory( void );

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
	factory			_factory[6];

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	Factory( Factory const & src );
	Factory & operator=( Factory const & rhs );

};

#endif