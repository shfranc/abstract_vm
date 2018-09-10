#include "Avm.hpp"

// INSTRUCTIONS

void					Avm::push( Token const & token ) {

	IOperand const *	tmp = _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) );
	_stack.emplace( _stack.begin(), tmp );
}

void					Avm::pop( Token const & token ) {
	
	if ( !_stack.empty() ) {
		delete *_stack.begin();
		_stack.erase( _stack.begin() );
	} else
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
}

void					Avm::dump( Token const & token ) {

	if ( !_stack.empty() ) {
		for (size_t i = 0; i < _stack.size(); i++)
			std::cout << (_stack[i])->toString() << std::endl;
	}
	else
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
}

void					Avm::a_ssert( Token const & token ) {

	IOperand const *	tmp;

	if ( !_stack.empty() ) {
		IOperand const *	reference = _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) );
		tmp = _stack.front();
		if ( compareOperand(tmp, reference) == false ) {
			std::string error = tmp->toString() + ASSERT_ERROR + reference->toString() + "'.";
			delete reference;
			throw ExecException( std::to_string( token.getLine()), error );			
		}
		delete reference;
	}
	else
		throw ExecException( std::to_string( token.getLine()), ASSERT_EMPTY_STACK );		
}

void					Avm::add( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		IOperand const * result = *operand_1 + *operand_2;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::sub( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		IOperand const * result = *operand_2 - *operand_1;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::mul( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		IOperand const * result = *operand_1 * *operand_2;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::div( Token const & token ) {
	
	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		if ( std::stod(operand_1->toString()) == 0 )
			throw ExecException( std::to_string( token.getLine()), token.getStr() + FORBIDDEN_OPERATION );	
		IOperand const * result = *operand_2 / *operand_1;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::mod( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		if ( std::stod(operand_1->toString()) == 0 )
			throw ExecException( std::to_string( token.getLine()), token.getStr() + FORBIDDEN_OPERATION );	
		if ( operand_1->getType() == DOUBLE || operand_1->getType() == FLOAT\
			||  operand_2->getType() == DOUBLE || operand_2->getType() == FLOAT ) {
			throw ExecException( std::to_string( token.getLine()), token.getStr() + MOD_IMPOSSIBLE );
		}	
		IOperand const * result = *operand_2 % *operand_1;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::print( Token const & token ) {
	
	IOperand const *	tmp;

	if ( !_stack.empty() ) {
		tmp = _stack.front();
		if ( tmp->getType() == INT8 ) {
			int c = std::stoi( tmp->toString() );
			std::cout << static_cast<char>(c);
		} else
			throw ExecException( std::to_string( token.getLine()), tmp->toString() + WRONG_TYPE );
	} else
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
}

void					Avm::e_xit( Token const & token ) {

	(void)token;
	_exit = true;
}

// BONUS

void					Avm::b_and( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		if ( operand_1->getType() == DOUBLE || operand_1->getType() == FLOAT\
			||  operand_2->getType() == DOUBLE || operand_2->getType() == FLOAT ) {
			throw ExecException( std::to_string( token.getLine()), token.getStr() + MOD_IMPOSSIBLE );
		}
		IOperand const * result = *operand_2 & *operand_1;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::b_or( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		if ( operand_1->getType() == DOUBLE || operand_1->getType() == FLOAT\
			||  operand_2->getType() == DOUBLE || operand_2->getType() == FLOAT ) {
			throw ExecException( std::to_string( token.getLine()), token.getStr() + MOD_IMPOSSIBLE );
		}
		IOperand const * result = *operand_2 | *operand_1;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::b_xor( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		IOperand const * operand_1 = _stack[0];
		IOperand const * operand_2 = _stack[1];
		if ( operand_1->getType() == DOUBLE || operand_1->getType() == FLOAT\
			||  operand_2->getType() == DOUBLE || operand_2->getType() == FLOAT ) {
			throw ExecException( std::to_string( token.getLine()), token.getStr() + MOD_IMPOSSIBLE );
		}
		IOperand const * result = *operand_2 ^ *operand_1;
		popTowOperands();
		_stack.emplace( _stack.begin(), result );
	}
}

void					Avm::reverse( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else
		std::reverse( _stack.begin(), _stack.end() );
}

void					Avm::drop( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else {
		for ( _stack.begin(); !_stack.empty(); _stack.erase( _stack.begin() )) {
			delete *(_stack.begin());
		}
	}
}

void					Avm::my_sort( Token const & token ) {

	if ( _stack.empty() )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + EMPTY_STACK );
	else if ( _stack.size() < 2 )
		throw ExecException( std::to_string( token.getLine()), token.getStr() + LESS_OPERAND );
	else {
		std::sort( _stack.begin(), _stack.end(), []( IOperand const * operand_1, IOperand const * operand_2) {
			return ( std::stod(operand_1->toString()) < std::stod(operand_2->toString()) );
		});
	}
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

void					Avm::popTowOperands( void ) {

	delete _stack[0];
	_stack.erase( _stack.begin() );
	delete _stack[0];
	_stack.erase( _stack.begin() );
}