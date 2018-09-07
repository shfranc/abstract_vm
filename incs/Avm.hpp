#ifndef AVM_HPP
# define AVM_HPP

#include "Reader.hpp"
#include "Parser.hpp"
#include "Factory.hpp"
#include "IOperand.hpp"
#include "ExecException.hpp"
#include <map>
#include <sstream>

# define PARSER_OPT	"--parser"

class Avm {

public:
	Factory						_factory;

	typedef void (Avm::*execute)( Token const & );

	Avm( void );
	Avm( std::string filename );
	~Avm( void );

	void						readUserInput();	
	void						parseInstructions();
	void						compute();

	// ACCESSORS
	std::stringstream const &	getError( void ) const;
	Parser const *				getParser( void ) const;

private:
	Reader *						_reader;
	Parser *						_parser;
	std::vector<IOperand const *>	_stack;
	std::vector<Token> *			_instructions;
	std::map<std::string, execute>	_execute;
	std::stringstream				_error;
	bool							_exit;

	Avm( Avm const & src );
	Avm & 			operator=( Avm const & rhs );

	// INIT INSTRUCTIONS MAP
	void			initExecute( void );

	// INSTRUCTIONS
	int				doInstruction(int i);
	void			push( Token const & );
	void			pop( Token const & );
	void			dump( Token const & );
	void			a_ssert( Token const & );
	void			add( Token const & );
	void			sub( Token const & );
	void			mul( Token const & );
	void			div( Token const & );
	void			mod( Token const & );
	void			print( Token const & );
	void			e_xit( Token const & );

	// INSTRUCTIONS BONUS
	void			b_and( Token const & );

	// ERROR HANDLING
	bool			checkError( std::stringstream const & error ) const;
	void			flushError( std::stringstream const & error ) const;

	// TOOLS
	std::string		captureNumericValue( std::string str ) const;
	bool			compareOperand(IOperand const * operand_1, IOperand const * operand_2) const;
	void			popTowOperands( void );

};

#endif