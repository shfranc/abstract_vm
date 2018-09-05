#include "Avm.hpp"

// INSTRUCTIONS

void					Avm::push( Token const & token ) {

	std::cout << "** push" << std::endl;
	try {
		IOperand const *	tmp = _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) );
		_stack.emplace( _stack.begin(), tmp );
	} catch (std::out_of_range e) {
		std::cerr << e.what() << std::endl;
	}
	return;
}

void					Avm::pop( Token const & token ) {
	
	std::cout << "** pop" << std::endl;
	if ( !_stack.empty() ) {
		delete *_stack.begin();
		_stack.erase( _stack.begin() );
	} else {
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	}
	return;
}

void					Avm::dump( Token const & token ) {

	std::cout << "** dump" << std::endl;
	if ( !_stack.empty() ) {
		for (size_t i = 0; i < _stack.size(); i++)
			std::cout << (_stack[i])->toString() << std::endl;
	}
	else {
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	}
}

void					Avm::a_ssert( Token const & token ) {
	IOperand const *	tmp;

	std::cout << "** assert" << std::endl;

	if ( !_stack.empty() ) {
		try {
			IOperand const *	reference = _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) );

			tmp = _stack.front();
			if ( compareOperand(tmp, reference) == false ) {
				std::string error = tmp->toString() + ASSERT_ERROR + reference->toString() + "'.";
				delete reference;
				throw ExecException( std::to_string( token.getLine()), error );			
			}
			delete reference;

		} catch (std::out_of_range e) {
			std::cerr << e.what() << std::endl;
		return ;
	}	
	}
	else {
		throw ExecException( std::to_string( token.getLine()), ASSERT_EMPTY_STACK );		
	}
	return;
}

void					Avm::add( Token const & token ) {

	std::cout << "** add" << std::endl;

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		IOperand const * result = *operand_1 + *operand_2;

		delete _stack[0];
		_stack.erase( _stack.begin() );
		delete _stack[0];
		_stack.erase( _stack.begin() );
		_stack.emplace( _stack.begin(), result );
	}

	return;
}

void					Avm::sub( Token const & token ) {

	std::cout << "** sub" << std::endl;

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		IOperand const * result = *operand_1 - *operand_2;

		delete _stack[0];
		_stack.erase( _stack.begin() );
		delete _stack[0];
		_stack.erase( _stack.begin() );
		_stack.emplace( _stack.begin(), result );
	}

	return;
}

void					Avm::mul( Token const & token ) {

	std::cout << "** mul" << std::endl;

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		IOperand const * result = *operand_1 * *operand_2;

		delete _stack[0];
		_stack.erase( _stack.begin() );
		delete _stack[0];
		_stack.erase( _stack.begin() );
		_stack.emplace( _stack.begin(), result );
	}

	return;
}

void					Avm::div( Token const & token ) {
	
	std::cout << "** div" << std::endl;

	if ( _stack.size() >= 2 ) {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		
		if ( std::stod(operand_1->toString()) == 0 )
			throw ExecException( std::to_string( token.getLine()), token.getStr() + FORBIDDEN_OPERATION );

		IOperand const * result = *operand_1 * *operand_2;

		delete _stack[0];
		_stack.erase( _stack.begin() );
		delete _stack[0];
		_stack.erase( _stack.begin() );

		_stack.emplace( _stack.begin(), result );

	} else if ( !_stack.empty() && _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );

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
		tmp = _stack.front();
		if ( tmp->getType() == INT8 ) {
			int c = std::stoi( tmp->toString() );
			std::cout << static_cast<char>(c);
		} else {
			throw ExecException( std::to_string( token.getLine()), tmp->toString() + WRONG_TYPE );		
		}
	} else {
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );		
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

// TOOLS

std::string				Avm::captureNumericValue( std::string str ) const {

	std::smatch m;
	std::regex e("\\((.+)\\)");

	std::regex_search( str, m, e );
	return (m[1]);
}

bool					Avm::compareOperand(IOperand const * operand_1, IOperand const * operand_2) const {

	if ( operand_1->toString() == operand_2->toString() )
		return (true);
	return (false);
}