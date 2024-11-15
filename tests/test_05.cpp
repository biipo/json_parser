#include "json.cpp"

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
}
