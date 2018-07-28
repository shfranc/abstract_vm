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
	for (;!_stack.empty(); _stack.pop()) {
		delete _stack.top();
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

	if ( !checkError( _error ) || _reader->getContent() == "" )
		return;

	_parser = new Parser( _reader->getContent() );
	_parser->parse();
	std::cout << *_parser;
	_instructions = _parser->getInstructions();
}

void					Avm::compute() {

	if ( !checkError( _parser->getError() ) || !_instructions )
		return;

	for (size_t i = 0; i < _instructions->size(); i++)
	{
		i = doInstruction(i);
	}
}

int				Avm::doInstruction( int i ) {

	if ( (*_instructions)[i].getInstr() == PUSH || (*_instructions)[i].getInstr() == ASSERT ) {
		(this->*_execute[(*_instructions)[i].getStr()])( (*_instructions)[i + 1] );
		i++;
	}
	else {
		(this->*_execute[(*_instructions)[i].getStr()])( (*_instructions)[i] );
	}
	return (i);
}

// INSTRUCTIONS

void					Avm::push( Token const & token ) {

	std::cout << "** push" << std::endl;
	try {
		IOperand const *	tmp = _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) );
		_stack.push( tmp );
	} catch (std::out_of_range e) {
		std::cerr << e.what() << std::endl;
	}
	return;
}

void					Avm::pop( Token const & token ) {
	
	std::cout << "** pop" << std::endl;
	if ( !_stack.empty() )
		_stack.pop();
	else {
		std::cerr << "Line " << token.getLine() << ": Exec error: `" << token.getStr() << "' on an empty stack." << std::endl;
		// exit(1);
	}
	return;
}

void					Avm::dump( Token const & token ) {

	std::cout << "** dump" << std::endl;
	if ( !_stack.empty() ) {
		for (std::stack<IOperand const *> dump = _stack; !dump.empty(); dump.pop())
			std::cout << dump.top()->toString() << std::endl;
	}
	else {
		std::cerr << "Line " << token.getLine() << ": Exec error: `" << token.getStr() << "' on an empty stack." << std::endl;
		// exit(1);
	}	 	
}

void					Avm::a_ssert( Token const & token ) {
	IOperand const *	reference = _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) );
	IOperand const *	tmp;

	std::cout << "** assert" << std::endl;

	if ( !_stack.empty() ) {

		tmp = _stack.top();
		if ( compareOperand(tmp, reference) == false ) {
			std::cerr << "Line " << token.getLine() << ": Exec error: `" << tmp->toString() << "' is not equal to `" << reference->toString() << "'." << std::endl;
		// exit(1);			
		}
	}
	else {
		std::cerr << "Line " << token.getLine() << ": Exec error: `" << token.getStr() << "' on an empty stack." << std::endl;
		// exit(1);
	}
	delete reference;
	return;
}

void					Avm::add( Token const & token ) {

	std::cout << "** add" << std::endl;
	(void)token;
	return;
}

void					Avm::sub( Token const & token ) {

	std::cout << "** sub" << std::endl;
	(void)token;
	return;
}

void					Avm::mul( Token const & token ) {

	std::cout << "** mul" << std::endl;
	(void)token;
	return;
}

void					Avm::div( Token const & token ) {
	
	std::cout << "** div" << std::endl;
	(void)token;
	return;
}

void					Avm::mod( Token const & token ) {

	std::cout << "** mod" << std::endl;
	(void)token;
	return;
}

void					Avm::print( Token const & token ) {
	
	IOperand const *	tmp;

	std::cout << "** print" << std::endl;
	if ( !_stack.empty() ) {

		tmp = _stack.top();
		if ( tmp->getType() == INT8 ) {
			int c = std::stoi( tmp->toString() );
			std::cout << static_cast<char>(c) << std::endl;
		}
		else {
			std::cerr << "Line " << token.getLine() << ": Exec error: `" << tmp->toString() << "' is not an 8-bit integer." << std::endl;			
		}
	}
	else {
		std::cerr << "Line " << token.getLine() << ": Exec error: `" << token.getStr() << "' on an empty stack." << std::endl;
		// exit(1);
	}
	(void)token;
	return;
}

void					Avm::e_xit( Token const & token ) {

	std::cout << "** exit" << std::endl;
	(void)token;
	_exit = true;
	return;
}

// ERROR HANDLING
bool					Avm::checkError( std::ostringstream const & error ) const {

	if ( error.str() == "")
		return true;
	flushError(error);
	return false;
}
void					Avm::flushError( std::ostringstream const & error ) const {

	std::cerr << error.str();
}

// TOOLS

std::string				Avm::captureNumericValue( std::string str ) const {

	std::smatch m;
	std::regex e("\\((.+)\\)");

	std::regex_search( str, m, e );
	std::cout << m[1] << std::endl;

	return (m[1]);
}

bool					Avm::compareOperand(IOperand const * O1, IOperand const * O2) const {

	if ( O1->getType() == O2->getType() )
	{
		if ( std::strcmp( O1->toString().c_str(), O2->toString().c_str() ) == 0 )
			return (true);
	}
	return (false);
}

// ACCESSORS

std::ostringstream const &	Avm::getError( void ) const { return _error; }