#include <pygmalion-chess-dynamics.h>

using namespace pygmalion;
using namespace pygmalion::dynamics;
using namespace pygmalion::chess;

int main(int argc, char* argv[])
{
	engine<pygmalion::chess::generator> eng(std::cin, std::cout);
	eng.run();
	return 0;
}