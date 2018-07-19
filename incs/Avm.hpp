#ifndef AVM_HPP
# define AVM_HPP

#include "Reader.hpp"
#include "Parser.hpp"
#include "IOperand.hpp"

class Avm {

public:

	Avm( void );
	Avm( std::string filename );
	~Avm( void );

	void		readUserInput();	
	void		parseInstructions();

private:
	Reader			*_reader;
	Parser			*_parser;


	Avm( Avm const & src );
	Avm & operator=( Avm const & rhs );
	
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;	

};

#endif