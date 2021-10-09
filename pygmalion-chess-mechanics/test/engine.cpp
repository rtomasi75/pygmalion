#include <pygmalion-chess-mechanics.h>

using namespace pygmalion;
using namespace pygmalion::mechanics;
using namespace pygmalion::chess;

int main(int argc, char* argv[])
{
	engine<pygmalion::chess::motor> eng(std::cin, std::cout);
	eng.run();
	return 0;
}