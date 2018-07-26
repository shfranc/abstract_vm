#ifndef INT8_HPP
# define INT8_HPP

# include "Token.hpp"
# include "IOperand.hpp"

class Int8 : public IOperand {

public:

	Int8( eOperandType type, std::string value );
	virtual	~Int8( void );

	virtual int					getPrecision( void ) const;
	virtual eOperandType		getType( void ) const;
	virtual std::string const &	toString( void ) const;

	// virtual IOperand const *	operator+( IOperand const & rhs ) const;
	// virtual IOperand const *	operator-( IOperand const & rhs ) const;
	// virtual IOperand const *	operator*( IOperand const & rhs ) const;
	// virtual IOperand const *	operator/( IOperand const & rhs ) const;
	// virtual IOperand const *	operator%( IOperand const & rhs ) const;



private:
	eOperandType	_type;
	int				_precision;
	std::string		_value;

	Int8( void );
	Int8( Int8 const & src );
	Int8 & operator=( Int8 const & rhs );

};

#endif