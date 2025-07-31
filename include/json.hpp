#include <iostream>
#include <string>
#include <limits>
#include <assert.h>
#include <fstream>
#include <stdlib.h>

struct json_exception {
	std::string msg;
};

class json {

public:
	
	struct list_iterator; // not 
	struct dictionary_iterator;// not 
	struct const_list_iterator;// not 
	struct const_dictionary_iterator;// not 
	
	json();// not 
	json(json const&);
	json(json&&);
	~json();// not 
	
	json& operator=(json const&);
	json& operator=(json&&);

	bool is_list() const;// not 
	bool is_dictionary() const;// not 
	bool is_string() const;// not 
	bool is_number() const;// not 
	bool is_bool() const;// not tested
	bool is_null() const;// not tested

	json const& operator[](std::string const&) const;// not tested
	json& operator[](std::string const&);// not tested

	list_iterator begin_list();// not tested
	const_list_iterator begin_list() const;// not tested
	list_iterator end_list();// not t
	const_list_iterator end_list() const;// not tested

	dictionary_iterator begin_dictionary();
	const_dictionary_iterator begin_dictionary() const;// not tested
	dictionary_iterator end_dictionary();// not tested
	const_dictionary_iterator end_dictionary() const;// not tested

	double& get_number();// not tested
double const& get_number() const;// not tested

	bool& get_bool();// not tested
bool const& get_bool() const;// not tested

	std::string& get_string();// not tested
	const std::string& get_string() const;

	void set_string (std::string const&);

	void set_number(double);
    void set_bool(bool);
	void set_null();
	void set_list();
	void set_dictionary();
	void push_front(json const&);
	void push_back(json const&);
	void insert(std::pair<std::string,json> const&);

private:
		
	struct impl;
	impl* pimpl;
	
};

std::ostream& operator<<(std::ostream& lhs, json const& rhs);
std::istream& operator>>(std::istream& lhs, json& rhs);
