#include "json.cpp"
#include "tests/tests.h"
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

int main(void)
{
	test_1();
	return 0;
}
