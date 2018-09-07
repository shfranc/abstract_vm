#include "Avm.hpp"

Avm::Avm( void ) : _reader( new Reader() ), _exit(false) {
	
	initExecute();
	return;
}

Avm::Avm( std::string filename ) : _reader( new Reader(filename) ), _exit(false) {
	
	initExecute();
	return;
}

Avm::~Avm( void ) {

	delete _reader;
	delete _parser;
	for ( _stack.begin(); !_stack.empty(); _stack.erase( _stack.begin() )) {
		delete *(_stack.begin());
	}
	return;
}

void					Avm::initExecute( void ) {

	_execute["push"] = &Avm::push;
	_execute["pop"] = &Avm::pop;
	_execute["dump"] = &Avm::dump;
	_execute["assert"] = &Avm::a_ssert;
	_execute["add"] = &Avm::add;
	_execute["sub"] = &Avm::sub;
	_execute["mul"] = &Avm::mul;
	_execute["div"] = &Avm::div;
	_execute["mod"] = &Avm::mod;
	_execute["print"] = &Avm::print;
	_execute["exit"] = &Avm::e_xit;
	_execute["and"] = &Avm::b_and;
	_execute["or"] = &Avm::b_or;
	_execute["xor"] = &Avm::b_xor;
	_execute["reverse"] = &Avm::reverse;
	_execute["drop"] = &Avm::drop;
	_execute["sort"] = &Avm::my_sort;
	return;
}

// PUBLIC

void					Avm::readUserInput() {

	_reader->read();
}	

void					Avm::parseInstructions() {
	
	_parser = new Parser( _reader->getContent() );
	_parser->parse();
	_instructions = _parser->getInstructions();
}

void					Avm::compute() {
	

	if ( !checkError( _parser->getError() ) || !_instructions ) {
		flushError( _parser->getError() );
		return;
	}
	for (size_t i = 0; i < _instructions->size(); i++)
	{
		i = doInstruction(i);		

		if ( (*_instructions)[i].getInstr() == PUSH || (*_instructions)[i].getInstr() == ASSERT )
			i++;
		
		if ( _exit )
			return ;
	}
	if ( _exit == false )
		std::cerr << "Exec error: Missing the token `exit' at the end of the program." << std::endl;
}

int				Avm::doInstruction( int i ) {

	if ( (*_instructions)[i].getInstr() == PUSH || (*_instructions)[i].getInstr() == ASSERT ) {
		(this->*_execute[(*_instructions)[i].getStr()])( (*_instructions)[i + 1] );
	}
	else {
		(this->*_execute[(*_instructions)[i].getStr()])( (*_instructions)[i] );
	}
	return (i);
}

// ERROR HANDLING
bool					Avm::checkError( std::stringstream const & error ) const {

	if ( error.str() == "" )
		return true;
	return false;
}
void					Avm::flushError( std::stringstream const & error ) const {

	std::cerr << error.rdbuf();
}

// ACCESSORS

std::stringstream const &	Avm::getError( void ) const { return _error; }
Parser const *				Avm::getParser( void ) const { return _parser; }
