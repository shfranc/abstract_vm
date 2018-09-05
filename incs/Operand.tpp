#ifndef OPERAND_HPP
# define OPERAND_HPP

# include <algorithm>
# include "IOperand.hpp"

class Factory;

template< typename T >
class Operand : public IOperand {

public:

	Operand( eOperandType type, std::string str ) :
		_type(type),
		_precision(type),
		_value(setValue( str )),
		_str(std::to_string( _value )) {

		return;
	}

	~Operand( void ) { return; }

	// ACCESSOR

	eOperandType		getType( void ) const { return _type; }
	int					getPrecision( void ) const { return _precision; }
	T					getValue( void ) const { return _value; }
	std::string const &	toString( void ) const { return _str; }

	T					setValue( std::string str ) {

		T		value;

		if ( _type == INT8 || _type == INT16 || _type == INT32 ) {
			value = std::stoi( str );
		} else if ( _type == FLOAT ) {
			value = std::stof( str );
		} else {
			value = std::stod( str );
		}
		return (value);
	}

	IOperand const *	operator+( IOperand const & rhs ) const {

		return _factory.createOperand( std::max( _type, rhs.getType() ), std::to_string(_value + std::stod( rhs.toString()) ) );
	}

	IOperand const *	operator-( IOperand const & rhs ) const {

		return _factory.createOperand( std::max( _type, rhs.getType() ), std::to_string(_value - std::stod( rhs.toString()) ) );
	}

	IOperand const *	operator*( IOperand const & rhs ) const {

		return _factory.createOperand( std::max( _type, rhs.getType() ), std::to_string(_value * std::stod( rhs.toString()) ) );
	}

	// IOperand const *	operator/( IOperand const & rhs ) const;
	// IOperand const *	operator%( IOperand const & rhs ) const;

private:
	Factory			_factory;
	eOperandType	_type;
	int				_precision;
	T				_value;
	std::string		_str;

	Operand( void );
	Operand( Operand< T > const & src ); // avec T ou pas ?
	Operand & operator=( Operand< T > const & rhs );

};

#endif