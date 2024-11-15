#include "json.cpp"

void test_6()
{
    std::ifstream is("file.json");
    std::ifstream is_2("file_2.json");
    std::ofstream os("out.json");
    try {
        json j;
		json z;
        is >> j;
		is_2 >> z;
		(*(++j.begin_list()))["prima chiave"] = z;
		os << j;
    } catch (const json_exception& e) {
        std::cout << e.msg << std::endl;
		exit(EXIT_FAILURE);
    }
}
