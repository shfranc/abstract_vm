#ifndef AVM_HPP
# define AVM_HPP

#include "Reader.hpp"
#include "Parser.hpp"
#include "Int8.hpp"

class Avm {

public:

	Avm( void );
	Avm( std::string filename );
	~Avm( void );

	void		readUserInput();	
	void		parseInstructions();
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;	

private:
	Reader			*_reader;
	Parser			*_parser;


	Avm( Avm const & src );
	Avm & operator=( Avm const & rhs );
	

};

#endif