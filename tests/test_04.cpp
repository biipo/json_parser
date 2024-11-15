#include "json.cpp"

void test_4()
{
    std::ifstream is("file.json");
    std::ofstream os("out.json");
    try {
        json j;
        is >> j;
		
		json b;
		b.set_number(87.3);
		std::pair<std::string, json> pair("stringa", b);
		j["seconda chiave"].insert(pair);
		os << j;
    } catch (const json_exception& e) {
        std::cout << e.msg << std::endl;
        exit(EXIT_FAILURE);
    }
}
