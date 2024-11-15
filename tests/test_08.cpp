#include "json.cpp"

void test_8()
{
    std::ifstream is("file.json");
    std::ofstream os("out.json");
    try {
        json j;
        is >> j;

        // Test the json object here
        std::cout << j["string"].get_string() << std::endl; // prints "Hello, world!"
        std::cout << j["number"].get_number() << std::endl; // prints "3.14"
        std::cout << std::boolalpha << j["boolean"].get_bool() << std::endl; // prints "true"

        json list = j["list"];
        for (json::list_iterator it = list.begin_list(); it != list.end_list(); ++it) {
            if (it->is_string()) {
                std::cout << it->get_string() << ' ';
            } else if (it->is_number()) {
                std::cout << it->get_number() << ' ';
            } else if (it->is_bool()) {
                std::cout << std::boolalpha << it->get_bool() << ' ';
            }
        }
        std::cout << std::endl; // prints "one 2 false "

        json dict = j["dictionary"];
        std::cout << dict["key1"].get_string() << ' '; // prints "value1 "
        std::cout << dict["key2"].get_number() << ' '; // prints "42 "
        std::cout << std::endl;

        os << j;
        os << std::endl;
    } catch (const json_exception& e) {
        std::cout << e.msg << std::endl;
		exit(EXIT_FAILURE);
    }
}
