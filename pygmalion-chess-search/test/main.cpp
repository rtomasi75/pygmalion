#include <pygmalion-chess-search.h>

using namespace pygmalion;
using namespace pygmalion::search;
using namespace pygmalion::chess;

int main(int argc, char* argv[])
{
	engine<pygmalion::chess::node> eng(std::cin, std::cout);
	eng.run();
	return 0;
}