#include "Factory.hpp"
#include "Operand.tpp"

Factory::Factory( void ) {

	_factory[INT8] = &Factory::createInt8;
	_factory[INT16] = &Factory::createInt16;
	_factory[INT32] = &Factory::createInt32;
	_factory[FLOAT] = &Factory::createFloat;
	_factory[DOUBLE] = &Factory::createDouble;
	return;
}

Factory::~Factory( void ) {

	return;
}

IOperand const *	Factory::createOperand( eOperandType type, std::string const & value ) const {

	return ( (this->*_factory[type])( value ) );
}

IOperand const *	Factory::createInt8( std::string const & value ) const {

	return ( new Operand<int8_t>(INT8, value) );
}
IOperand const *	Factory::createInt16( std::string const & value ) const {

	return ( new Operand<int16_t>(INT16, value) );
}
IOperand const *	Factory::createInt32( std::string const & value ) const {

	return ( new Operand<int32_t>(INT32, value) );
}
IOperand const *	Factory::createFloat( std::string const & value ) const {

	return ( new Operand<float>(FLOAT, value) );
}
IOperand const *	Factory::createDouble( std::string const & value ) const {

	return ( new Operand<double>(DOUBLE, value) );
}
