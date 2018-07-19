#ifndef INT8_HPP
# define INT8_HPP

# include "Token.hpp"
# include "IOperand.hpp"

class Int8 : public IOperand {

	virtual int				getPrecision( void ) const;
	virtual eOperandType	getType( void ) const;

	// virtual IOperand const *	operator+( IOperand const & rhs ) const;
	// virtual IOperand const *	operator-( IOperand const & rhs ) const;
	// virtual IOperand const *	operator*( IOperand const & rhs ) const;
	// virtual IOperand const *	operator/( IOperand const & rhs ) const;
	// virtual IOperand const *	operator%( IOperand const & rhs ) const;

	// virtual std::string const &	toString( void ) const;

	virtual	~Int8( void ) {}

private:
	int				_precision;
	eOperandType	_type;
	std::string		_value;
};

#endif