#include "json.cpp"

void test_1()
{
	std::ifstream is("file.json");
	std::ofstream os("out.json");
	try{
		json j;
		is >> j;
		os << j;
		os << std::endl;
	} catch(const json_exception& e){
		std::cout << e.msg << std::endl;
		return 1;
	}
}
