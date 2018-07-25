#include "Factory.hpp"

Factory::Factory( void ) {

	_factory[INT8] = &Factory::createInt8;
	_factory[INT16] = &Factory::createInt16;
	_factory[INT32] = &Factory::createInt32;
	_factory[DOUBLE] = &Factory::createDouble;
	_factory[FLOAT] = &Factory::createFloat;
	return;
}

Factory::~Factory( void ) {

	return;
}

IOperand const *	Factory::createOperand( eOperandType type, std::string const & value ) const {

	return (this->*_factory[type])( value );
}

IOperand const *	Factory::createInt8( std::string const & value ) const {

	return ( new Int8(INT8, value) );
}
IOperand const *	Factory::createInt16( std::string const & value ) const {

	return ( new Int8(INT8, value) );
}
IOperand const *	Factory::createInt32( std::string const & value ) const {

	return ( new Int8(INT8, value) );
}
IOperand const *	Factory::createFloat( std::string const & value ) const {

	return ( new Int8(INT8, value) );
}
IOperand const *	Factory::createDouble( std::string const & value ) const {

	return ( new Int8(INT8, value) );
}
