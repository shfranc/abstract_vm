#include "Int8.hpp"

Int8::Int8( eOperandType type, std::string value ) : _type(type), _precision(0), _value(value) { return; }
Int8::~Int8( void ) { return; }

// ACCESSOR
int				Int8::getPrecision( void ) const { return _precision; }
eOperandType	Int8::getType( void ) const { return _type; }
std::string const &	Int8::toString( void ) const { return _value; }

// OPERATOR

// IOperand const *	Int8::operator+( IOperand const & rhs ) const {

// }

// IOperand const *	Int8::operator-( IOperand const & rhs ) const {

// }

// IOperand const *	Int8::operator*( IOperand const & rhs ) const {

// }

// IOperand const *	Int8::operator/( IOperand const & rhs ) const {

// }

// IOperand const *	Int8::operator%( IOperand const & rhs ) const {

// }



