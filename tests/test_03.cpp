#include "json.cpp"

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
