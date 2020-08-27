#include <pygmalion-chess.h>

int main(int argc, char* argv[])
{
	pygmalion::chess::engine eng(std::cin, std::cout);
	eng.run();
	return 0;
}