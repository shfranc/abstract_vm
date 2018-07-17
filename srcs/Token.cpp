#include "Token.hpp"

Token::Token( void ) : _str(""), _type(NONE) {

	std::cout << "Token: default contruct " << _str << std::endl;
	return;
}

Token::Token( std::string str ) : _str(str), _type( checkType() ) {

	std::cout << "Token: param contruct " << _str << std::endl;
	return;
}

Token::Token( Token const & src ) {

	std::cout << "Token: copy contruct " << src._str << std::endl;
	*this = src;
	return;
}

Token::~Token( void ) {

	std::cout << "Token: destruct " << _str << std::endl;
	return;
}

Token &	Token::operator=( Token const & rhs ) {
	
	if ( this != &rhs ) {
		_str = rhs._str;
		_type = rhs._type;
	}
	
    return *this;
}

int		Token::checkType( void ) {
	if ( (_instr = checkInstr()) != NONE )
		return (INSTR);
	if ( checkValue() != NONE )
		return (VALUE);
	if ( _str == "<newline>" )
		return (SEP);
	return (INVALID);
}

int		Token::checkInstr( void ) {

	if ( _str == "push" )
		return (PUSH);
	if ( _str == "pop" )
		return (POP);
	if ( _str == "dump" )
		return (DUMP);
	if ( _str == "assert" )
		return (ASSERT);							
	if ( _str == "add" )
		return (ADD);
	if ( _str == "sub" )
		return (SUB);
	if ( _str == "mul" )
		return (MUL);
	if ( _str == "div" )
		return (DIV);
	if ( _str == "mod" )
		return (MOD);
	if ( _str == "print" )
		return (PRINT);
	if ( _str == "exit" || _str == ";;" )
		return (EXIT);
	return (NONE);
}

int		Token::checkValue( void ) {

	if ( std::regex_match(_str, std::regex("int(8|16|32)[(][-]?[0-9]+[)]") ) )
	{
		_value = V_INT;
		return (VALUE);
	}
	if ( std::regex_match(_str, std::regex("float[(][-]?[0-9]+[.]?[0-9]*[)]") ) )
	{
		_value = V_FLOAT;
		return (VALUE);
	}
	if ( std::regex_match(_str, std::regex("double[(][-]?[0-9]+[.]?[0-9]*[)]") ) )
	{
		_value = V_DOUBLE;
		return (VALUE);
	}
	return (NONE);		
}

// ACCESSOR
std::string		Token::getStr( void ) const { return _str; }
int				Token::getType( void ) const { return _type; }
int				Token::getInstr( void ) const { return _instr; }
int				Token::getValue( void ) const { return _value; }
