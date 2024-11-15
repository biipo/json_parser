#include "json.cpp"

void test_7()
{
	std::ifstream is("file.json");
	std::ofstream os("out.json");
	try{
		json j;
		is >> j;
		 json j1;
    j1.set_string("Hello, world!");
    std::cout << j1.get_string() << std::endl; // prints "Hello, world!"

    // Create a json object of type number
    json j2;
    j2.set_number(3.14);
    std::cout << j2.get_number() << std::endl; // prints "3.14"

    // Create a json object of type boolean
    json j3;
    j3.set_bool(true);
    std::cout << std::boolalpha << j3.get_bool() << std::endl; // prints "true"

    // Create a json object of type list
    json j4;
    j4.set_list();
    j4.push_back(j1);
    j4.push_back(j2);
    j4.push_back(j3);

    // Iterate over the elements in the list
    for (json::list_iterator it = j4.begin_list(); it != j4.end_list(); ++it) {
        if (it->is_string()) {
            std::cout << it->get_string() << ' ';
        } else if (it->is_number()) {
            std::cout << it->get_number() << ' ';
        } else if (it->is_bool()) {
            std::cout << std::boolalpha << it->get_bool() << ' ';
        }
    }
    std::cout << std::endl; // prints "Hello, world! 3.14 true "

    // Create a json object of type dictionary
    json j5;
    j5.set_dictionary();
    j5.insert({"string", j1});
    j5.insert({"number", j2});
    j5.insert({"boolean", j3});

    // Access elements in the dictionary using the operator[]
    std::cout << j5["string"].get_string() << ' '; // prints "Hello, world! "
    std::cout << j5["number"].get_number() << ' '; // prints "3.14 "
    std::cout << std::boolalpha << j5["boolean"].get_bool() << ' '; // prints "true "
		os << j;
		os << std::endl;
	} catch(const json_exception& e){
		std::cout << e.msg << std::endl;
		exit(EXIT_FAILURE);
	}
}
