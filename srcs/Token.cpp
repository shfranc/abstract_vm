#include "Token.hpp"

Token::Token( void ) : _str(""), _type(NONE) {

	return;
}

Token::Token( std::string str ) : _str(str), _instr( checkInstr() ), _value( checkValue() ), _type( checkType() ) {

	return;
}

Token::Token( Token const & src ) {

	*this = src;
	return;
}

Token::~Token( void ) {

	return;
}

Token &	Token::operator=( Token const & rhs ) {
	
	if ( this != &rhs ) {
		_str = rhs._str;
		_instr = rhs._instr;
		_value = rhs._value;
		_type = rhs._type;
	}
	
    return *this;
}

int		Token::checkType( void ) {
	if ( _instr != NONE )
		return (INSTR);
	if ( _value != NONE )
		return (VALUE);
	if ( _str == "<newline>" )
		return (SEP);
	if ( _str == ";;" )
		return (END_INSTR);	
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
	if ( _str == "exit" )
		return (EXIT);
	return (NONE);
}

int		Token::checkValue( void ) {

	if ( std::regex_match(_str, std::regex("int(8|16|32)[(][-]?[0-9]+[)]") ) )
		return (V_INT);
	if ( std::regex_match(_str, std::regex("float[(][-]?[0-9]+[.]?[0-9]*[)]") ) )
		return (V_FLOAT);
	if ( std::regex_match(_str, std::regex("double[(][-]?[0-9]+[.]?[0-9]*[)]") ) )
		return (V_DOUBLE);
	return (NONE);		
}

// ACCESSOR
std::string		Token::getStr( void ) const { return _str; }
int				Token::getType( void ) const { return _type; }
int				Token::getInstr( void ) const { return _instr; }
int				Token::getValue( void ) const { return _value; }
