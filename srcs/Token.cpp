#include "Token.hpp"

Token::Token( void ) : _str(""), _type(INVALID) {

	return;
}

Token::Token( std::string str, size_t line ) : _str(str), _line(line), _instr( checkInstr() ), _operandType( checkOperandType() ), _type( checkType() ) {

	return;
}

Token::Token( Token const & src ) {

	*this = src;
	return;
}

Token::~Token( void ) {

	return;
}

Token &				Token::operator=( Token const & rhs ) {
	
	if ( this != &rhs ) {
		_str = rhs._str;
		_line = rhs._line;
		_instr = rhs._instr;
		_operandType = rhs._operandType;
		_type = rhs._type;
	}
	
    return *this;
}

eTokenType		Token::checkType( void ) {
	if ( _instr != NO_INSTR )
		return (INSTR);
	if ( _operandType != NO_OPERAND )
		return ( OPERAND );
	if ( _str == "<newline>" )
		return (SEP);
	if ( _str == ";;" )
		return (END_INSTR);	
	return (INVALID);
}

eInstructType		Token::checkInstr( void ) {

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
	if ( _str == "and" )
		return (AND);
	if ( _str == "or" )
		return (OR);
	if ( _str == "xor" )
		return (XOR);
	if ( _str == "reverse" )
		return (REVERSE);
	if ( _str == "drop" )
		return (DROP);
	return (NO_INSTR);
}

eOperandType		Token::checkOperandType( void ) {

	if ( std::regex_match(_str, std::regex("int8\\([-]?[0-9]+\\)") ) )
		return (INT8);
	if ( std::regex_match(_str, std::regex("int16\\([-]?[0-9]+\\)") ) )
		return (INT16);
	if ( std::regex_match(_str, std::regex("int32\\([-]?[0-9]+\\)") ) )
		return (INT32);		
	if ( std::regex_match(_str, std::regex("float\\([-]?[0-9]+\\.[0-9]*\\)") ) )
		return (FLOAT);
	if ( std::regex_match(_str, std::regex("double\\([-]?[0-9]+\\.[0-9]*\\)") ) )
		return (DOUBLE);
	return (NO_OPERAND);		
}

// ACCESSOR
std::string			Token::getStr( void ) const { return _str; }
size_t				Token::getLine( void ) const { return _line; }
eTokenType			Token::getType( void ) const { return _type; }
eInstructType		Token::getInstr( void ) const { return _instr; }
eOperandType		Token::getOperandType( void ) const { return _operandType; }
