#include <iostream>

void	ft_usage( void )
{
	std::cerr << "./avm [input_file]" << std::endl;
}

int main( int argc, char const *argv[] )
{
	if (argc == 1)
		std::cout << "mode std::cin" << std::endl;
	else if (argc == 2)
		std::cout << "mode file: " << argv[1] << std::endl;
	else
		ft_usage();
	return 0;
}
