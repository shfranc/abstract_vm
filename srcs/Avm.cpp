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
	// for (;!_stack.empty(); _stack.pop()) {
		// delete _stack.top();
	// }

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
	return;
}

// PUBLIC

void					Avm::readUserInput() {

	try {
		_reader->read();
	}
	catch ( std::invalid_argument e) {
		_error << e.what() << std::endl;
	}
}	

void					Avm::parseInstructions() {

	if ( !checkError( _error ) || _reader->getContent() == "" ) {
		flushError(_error);
		return;
	}
	
	_parser = new Parser( _reader->getContent() );
	_parser->parse();
	std::cout << *_parser;
	_instructions = _parser->getInstructions();
}

void					Avm::compute() {

	if ( !checkError( _error ) || !checkError( _parser->getError() ) || !_instructions ) {
		return;
	}

	for (size_t i = 0; i < _instructions->size(); i++)
	{
		try {
			i = doInstruction(i);

		} catch ( ExecException const & e ) {
			std::cerr << e.what() << std::endl;
			return ;
		}

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

	if ( error.str() == "")
		return true;
	return false;
}
void					Avm::flushError( std::stringstream const & error ) const {

	std::cerr << error.str();
}

// ACCESSORS

std::stringstream const &	Avm::getError( void ) const { return _error; }