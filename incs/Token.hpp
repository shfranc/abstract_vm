#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <regex>

typedef enum	tokenType
{
	INVALID,
	INSTR,
	OPERAND,
	SEP,
	END_INSTR
}				eTokenType;

typedef enum 	InstructType
{
	NO_INSTR,
	PUSH,
	POP,
	DUMP,
	ASSERT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PRINT,
	EXIT,
}				eInstructType;

typedef enum	OperandType {
	
	NO_OPERAND,
	INT8,
	INT16,
	INT32,
	FLOAT,
	DOUBLE
}				eOperandType;

class Token {

public:

	Token( void );
	Token( std::string str );
	Token( Token const & src );
	~Token( void );

	Token & 			operator=( Token const & rhs );
	std::string			getStr( void ) const;
	eInstructType		getInstr( void ) const;
	eOperandType		getOperandType( void ) const;
	eTokenType			getType( void ) const;

private:
	std::string			_str;
	eInstructType		_instr;
	eOperandType		_operandType;
	eTokenType			_type;

	eInstructType		checkInstr( void );
	eOperandType		checkOperandType( void );
	eTokenType			checkType( void );

};

#endif