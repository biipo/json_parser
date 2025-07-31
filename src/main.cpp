#include "json.hpp"
#include <iostream>

int main(void)
{
    std::cout << "Hello World!" << std::endl;
	return 0;
}
/*
void printObjectsWithKey(const json& j, std::ofstream& os, int& count) {
    if (j.is_dictionary()) {
        for (json::const_dictionary_iterator it = j.begin_dictionary(); it != j.end_dictionary(); ++it) {
            if (it->first == "name") {
                os << "Pokemon number -" << ++count << "- is: " << it->second << '\n';
            }
            printObjectsWithKey(it->second, os, count);
        }
    } else if (j.is_list()) {
        for (json::const_list_iterator it = j.begin_list(); it != j.end_list(); ++it) {
            printObjectsWithKey(*it, os, count);
        }
    }
}
*/
/*
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
void test_5()
{
    std::ifstream is("file.json");
	std::ifstream is_2("file_2.json");
    std::ofstream os("out.json");
    try {
        json j;
        os << "Is null, string, number, bool, list, dictionary: " 
			<< j.is_null()<<j.is_string() << j.is_number() <<
			j.is_bool() << j.is_list()<<j.is_dictionary() << '\n';
		json p;
		os << "Is null, string, number, bool, list, dictionary: "
			<< j.is_null()<<j.is_string()<<j.is_number()<<
			j.is_bool()<<j.is_list()<<j.is_dictionary() << '\n';
		
        is >> j;
		is_2 >> p;
		json dd(p);
		os << p.is_list() << std::endl;
		os << "file.json..." << "is_dictionary, (null,string,number,bool,list): "
			<<j.is_dictionary()<<" "<< j.is_null()<<j.is_string()<<
			j.is_number()<<j.is_bool()<<j.is_list() << '\n' << j << std::endl;
		os << '\n'<<"file_2.json..."<<"is list, (null,string,number,bool,dictionary): 
			<<p.is_list()<<" "<< p.is_null()<<p.is_string()<<p.is_number()
			<<p.is_bool()<<p.is_dictionary()<< '\n' << p << std::endl;

		json a;
		a.set_bool(false);
		os << '\n' << a << " | Is_bool: " << a.is_bool() << std::endl;
		json nn;
		nn.set_string("stringa finale");
		p.push_back(nn); // pericoloso
		os << p << std::endl;
		
		p.push_front(a);
		os << p << std::endl;
		os << std::endl;
		
		int i = 0;
		for(json::list_iterator it = p.begin_list(); it != p.end_list(); ++it){
			os << ++i << "--> " << *it << '\n';
		}
		
		p = j;
		os <<'\n' << p << std::endl;
		p.set_null();
		os << "is null: " << p.is_null() << " --> " << p << std::endl<< std::endl;

		json b;
		b.set_number(87.3);
		std::pair<std::string,json> new_pair("insert_string", b);
		j["quarta chiave"].insert(new_pair);
		os << j << '\n'<<std::endl;
*/
/*	
		json c;
		c.set_bool(true);
		std::pair<std::string,json> pa_pair("sabfhhjda", c);
		
		j["new-key"] = dd;
		j.insert(pa_pair); // prova di insert su j di base
		j["seconda chiave"].push_back(b);
		j["seconda chiave"].push_front(c);
		os <<std::endl<< j << std::endl;

		} catch (const json_exception& e) {
        std::cout << e.msg << std::endl;
        return 1;
    }
*/
/*
}
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
void findKey(const json& j, const std::string& keyToFind, std::ofstream& os)
{
    if (j.is_dictionary()) {
        for (json::const_dictionary_iterator it = j.begin_dictionary();
				it != j.end_dictionary(); ++it) {
            if (it->first == keyToFind) {
                os << "Found key: " << keyToFind << ", value: " << it->second << '\n';
            }
            findKey(it->second, keyToFind, os);
        }
    } else if (j.is_list()) {
        for (json::const_list_iterator it = j.begin_list(); it != j.end_list(); ++it) {
            findKey(*it, keyToFind, os);
        }
    }
}

void test_3()
{
    std::ifstream is("file.json");
    std::ofstream os("out.json");
    try {
        json j;
        is >> j;
		findKey(j, "key-to-find-in-large-file", os); // should be "result-in-big-file"
		os << std::endl;
    } catch (const json_exception& e) {
        std::cout << e.msg << std::endl;
        return 1;
    }
}
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
*/
