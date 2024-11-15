#include "json.cpp"

void test_2()
{
    std::ifstream is("file.json");
    std::ofstream os("out.json");
    try {
        json j;
        os << "Is null, string, number, bool, list, dictionary: " << j.is_null()<<j.is_string()<<j.is_number()<<j.is_bool()<<j.is_list()<<j.is_dictionary() << '\n';

        is >> j;
        os << j << std::endl;
        os << std::endl;

        // Accessing nested elements
        os << "Nested value: " << j["quarta chiave"]["a"] << std::endl;
        os << std::endl;
		
		// Using iterators
        for (json::dictionary_iterator it = j.begin_dictionary(); it != j.end_dictionary(); ++it) {
            os << "Key: " << it->first << ", Value: " << it->second << '\n';
        }
        os << j << std::endl;
        os << std::endl;

        // Adding elements
		os << "Trying operator[] with the assign operator" << std::endl;
        json nested_dict;
        nested_dict.set_number(42);
        j["new_key"] = nested_dict;
        os << j << std::endl;
        os << std::endl;

        // Modifying values
        j.set_string("Modified string");
		os << j << std::endl;
        j.set_number(3.14);
		os << j << std::endl;
        j.set_bool(true);
		os << j << std::endl;
        
    } catch (const json_exception& e) {
        std::cout << e.msg << std::endl;
        return 1;
    }
}
