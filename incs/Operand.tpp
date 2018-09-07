#ifndef OPERAND_HPP
# define OPERAND_HPP

# include <algorithm>
# include <limits>
# include <float.h>
# include <stdexcept>
# include "IOperand.hpp"

# define OVER_FLOW	"\033[1;31mOverFlow:\033[0m "
# define UNDER_FLOW	"\033[1;31mUnderFlow:\033[0m "
# define GREATER	" is greater than "
# define SMALLER	" is smaller than "

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

		long double		check;
		T				value;

		check = std::stold( str );
		checkFlows( check, str );

		if ( _type == INT8 || _type == INT16 || _type == INT32 ) {
			value = std::stoi( str );
		} else if ( _type == FLOAT ) {
			value = std::stof( str );
		} else {
			value = std::stod( str );
		}
		return (value);
	}

	void				checkFlows( long double value, std::string str ) {

		if ( _type == INT8 && value > SCHAR_MAX )
			throw std::overflow_error( OVER_FLOW + str + GREATER + std::to_string(SCHAR_MAX) + "." );
		if ( _type == INT8 && value < SCHAR_MIN )
			throw std::underflow_error( UNDER_FLOW + str + SMALLER + std::to_string(SCHAR_MIN) + "." );
		if ( _type == INT16 && value > SHRT_MAX )
			throw std::overflow_error( OVER_FLOW + str + GREATER + std::to_string(SHRT_MAX) + "." );
		if ( _type == INT16 && value < SHRT_MIN )
			throw std::underflow_error( UNDER_FLOW + str + SMALLER + std::to_string(SHRT_MIN) + "." );
		if ( _type == INT32 && value > INT_MAX )
			throw std::overflow_error( OVER_FLOW + str + GREATER + std::to_string(INT_MAX) + "." );
		if ( _type == INT32 && value < INT_MIN )
			throw std::underflow_error( UNDER_FLOW + str + SMALLER + std::to_string(INT_MIN) + "." );
		if ( _type == FLOAT && value > FLT_MAX )
			throw std::overflow_error( OVER_FLOW + str + GREATER + std::to_string(FLT_MAX) + "." );
		if ( _type == FLOAT && value < -FLT_MAX )
			throw std::underflow_error( UNDER_FLOW + str + SMALLER + std::to_string(-FLT_MAX) + "." );
		if ( _type == DOUBLE && value > DBL_MAX )
			throw std::overflow_error( OVER_FLOW + str + GREATER + std::to_string(DBL_MAX) + "." );
		if ( _type == DOUBLE && value < -DBL_MAX )
			throw std::underflow_error( UNDER_FLOW + str + SMALLER + std::to_string(-DBL_MAX) + "." );		
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

	IOperand const *	operator/( IOperand const & rhs ) const {

		return _factory.createOperand( std::max( _type, rhs.getType() ), std::to_string(_value / std::stod( rhs.toString()) ) );
	}

	IOperand const *	operator%( IOperand const & rhs ) const {

		return _factory.createOperand( std::max( _type, rhs.getType() ), std::to_string(static_cast<int>(_value) % std::stoi( rhs.toString()) ) );
	}

	IOperand const *	operator&( IOperand const & rhs ) const {

		return _factory.createOperand( std::max( _type, rhs.getType() ), std::to_string(static_cast<int>(_value) & std::stoi( rhs.toString()) ) );
	}

private:
	Factory			_factory;
	eOperandType	_type;
	int				_precision;
	T				_value;
	std::string		_str;

	Operand( void );
	Operand( Operand< T > const & src );
	Operand & operator=( Operand< T > const & rhs );

};

#endif