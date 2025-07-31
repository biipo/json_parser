#include "json.hpp"

enum data{
	Null,
	Number,
	Boolean,
	String,
	List,
	Dictionary,
};

struct list{
		json info;
		list* next;
};
typedef list* list_ptr;

struct dictionary{
		std::pair<std::string, json> pa;
		dictionary* next;
};
typedef dictionary* dict_ptr;


struct json::impl{
	data data_type {Null};

	double n {0.0};
	bool b {false};
	std::string string {nullptr};

	list_ptr l_head {nullptr};
	list_ptr l_tail {nullptr};
	
	dict_ptr d_head {nullptr};
	dict_ptr d_tail {nullptr};

	list_ptr list_copy(const list_ptr& j_head);
	dict_ptr dict_copy(const dict_ptr& j_head);
	void delete_all();
	void delete_rec_list(list_ptr& l);
	void delete_rec_dict(dict_ptr& d);
};


// The default constructor set the object to null
json::json()
    : pimpl(new impl) {
	//pimpl->data_type = Null;
	//pimpl->n = 0.0;
	//pimpl->b = false;
	//pimpl->l_head = pimpl->l_tail = nullptr;
	//pimpl->d_head = pimpl->d_tail = nullptr;
}

json::json(json const& j) : pimpl(new impl) {
	pimpl->data_type = j.pimpl->data_type;
	if(pimpl->data_type == Number){
		pimpl->n = j.pimpl->n;
	}else if(pimpl->data_type == Boolean){
		pimpl->b = j.pimpl->b;
	}else if(pimpl->data_type == String){
		pimpl->string = j.pimpl->string;
	}else if(pimpl->data_type == List){
		pimpl->l_head = pimpl->list_copy(j.pimpl->l_head);
		pimpl->l_tail = pimpl->l_head;
		while(pimpl->l_tail && pimpl->l_tail->next){
			pimpl->l_tail = pimpl->l_tail->next;
		}
	}else if(pimpl->data_type == Dictionary){
		pimpl->d_head = pimpl->dict_copy(j.pimpl->d_head);
		pimpl->d_tail = pimpl->d_head;
		while(pimpl->d_tail && pimpl->d_tail->next){
			pimpl->d_tail = pimpl->d_tail->next;
		}
	}
}

json::json(json&& j) : json() {
	*this = j;
}


json::~json(){
	pimpl->delete_all();
	delete pimpl;
}

//-----------------------------------------------------------------------------------
// NON-const list iterator
struct json::list_iterator{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = json;
		using pointer = json*;
		using reference = json&;
		list_iterator(list* p) : ptr(p){} // have to be list* ptr, because if is json* in operator++() 
										  // the iterator would have moved the head ptr
		reference operator*() const{
			return ptr->info;
		}
		pointer operator->() const{
			return &(ptr->info);
		}
		list_iterator& operator++(){
			ptr = ptr->next;
			return *this;
		}
		list_iterator operator++(int){
			list_iterator it = {ptr};
			++(*this);
			return it;
		}
		bool operator==(list_iterator const& it) const{
			return ptr == it.ptr;
		}
		bool operator!=(list_iterator const& it) const{
			return ptr != it.ptr;
		}
		operator bool() const{
			return ptr;
		}
	private:
		list* ptr;
};

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// CONST list iterator
struct json::const_list_iterator{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = const json;
		using pointer = const json*;
		using reference = const json&;
		const_list_iterator(list* p) : ptr(p){} // have to be list* ptr, because if is json* in operator++() 
										  // the iterator would have moved the head ptr
		reference operator*() const{
			return ptr->info;
		}
		pointer operator->() const{
			return &(ptr->info);
		}
		const_list_iterator& operator++(){
			ptr = ptr->next;
			return *this;
		}
		const_list_iterator operator++(int){
			const_list_iterator it = {ptr};
			++(*this);
			return it;
		}
		bool operator==(const_list_iterator const& it) const{
			return ptr == it.ptr;
		}
		bool operator!=(const_list_iterator const& it) const{
			return ptr != it.ptr;
		}
		operator bool() const{
			return ptr;
		}
	private:
		list* ptr;
};

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// CONST dictionary iterator
struct json::const_dictionary_iterator{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = const std::pair<std::string, json>;
		using pointer = const std::pair<std::string, json>*;
		using reference = const std::pair<std::string, json>&;
		const_dictionary_iterator(dictionary* p) : ptr(p){} // have to be list* ptr, because if is json* in operator++() 
										  // the iterator would have moved the head ptr
		reference operator*() const{
			return ptr->pa;
		}
		pointer operator->() const{
			return &(ptr->pa);
		}
		const_dictionary_iterator& operator++(){
			ptr = ptr->next;
			return *this;
		}
		const_dictionary_iterator operator++(int){
			const_dictionary_iterator it = {ptr};
			++(*this);
			return it;
		}
		bool operator==(const_dictionary_iterator const& it) const{
			return ptr == it.ptr;
		}
		bool operator!=(const_dictionary_iterator const& it) const{
			return ptr != it.ptr;
		}
		operator bool() const{
			return ptr;
		}
	private:
		dictionary* ptr;
};

//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// NON-const dictionary iterator
struct json::dictionary_iterator{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = std::pair<std::string, json>;
		using pointer = std::pair<std::string, json>*;
		using reference = std::pair<std::string, json>&;
		dictionary_iterator(dictionary* p) : ptr(p){} // have to be list* ptr, because if is json* in operator++() 
										  // the iterator would have moved the head ptr
		reference operator*() const{
			return ptr->pa;
		}
		pointer operator->() const{
			return &(ptr->pa);
		}
		dictionary_iterator& operator++(){
			ptr = ptr->next;
			return *this;
		}
		dictionary_iterator operator++(int){
			dictionary_iterator it = {ptr};
			++(*this);
			return it;
		}
		bool operator==(dictionary_iterator const& it) const{
			return ptr == it.ptr;
		}
		bool operator!=(dictionary_iterator const& it) const{
			return ptr != it.ptr;
		}
		operator bool() const{
			return ptr;
		}
	private:
		dictionary* ptr;
};

//-----------------------------------------------------------------------------------

list_ptr json::impl::list_copy(const list_ptr& j_head){
	if(!j_head){
		return nullptr;
	}
	list_ptr new_head = new list{j_head->info, nullptr};
	list_ptr new_tail = new_head;
	list_ptr tmp = j_head->next;
	while(tmp){
		new_tail->next = new list{tmp->info, nullptr};
		new_tail = new_tail->next;
		tmp = tmp->next;
	}
	return new_head;
}

dict_ptr json::impl::dict_copy(const dict_ptr& j_head){
	if(!j_head){
		return nullptr;
	}
	dict_ptr new_head = new dictionary{j_head->pa, nullptr};
	dict_ptr new_tail = new_head;
	dict_ptr tmp = j_head->next;
	while(tmp){
		new_tail->next = new dictionary {tmp->pa, nullptr};
		new_tail = new_tail->next;
		tmp = tmp->next;
	}
    return new_head;
}

json& json::operator=(const json& j){ // copy assignment
	if(this != &j){
		pimpl->delete_all();
		pimpl->data_type = j.pimpl->data_type;
		if(is_number()){
			pimpl->n = j.get_number();
		}
		else if(is_string()){
			pimpl->string = j.get_string();
		}
		else if(is_bool()){
			pimpl->b = j.get_bool();
		}
		else if(is_list()){
			pimpl->l_head = pimpl->list_copy(j.pimpl->l_head);
		}
		else if(is_dictionary()){
			pimpl->d_head = pimpl->dict_copy(j.pimpl->d_head);
		}
	}
	return *this;
}

json& json::operator=(json&& j){ // move assignment
	if(this != &j){
		pimpl->delete_all();
		pimpl->data_type = j.pimpl->data_type;
		if(is_number()){
			pimpl->n = j.get_number();
		}
		else if(is_string()){
			pimpl->string = j.get_string();
			j.pimpl->string.clear();
		}
		else if(is_bool()){
			pimpl->b = j.get_bool();
		}
		else if(j.is_list()){
			pimpl->l_head = j.pimpl->l_head;
			pimpl->l_tail = j.pimpl->l_tail;
		}else if(j.is_dictionary()){
			pimpl->d_head = j.pimpl->d_head;
			pimpl->d_tail = j.pimpl->d_tail;
		}
		j.set_null();
	}
	return *this;
}

bool json::is_list() const{
	return pimpl->data_type == List;
}

bool json::is_dictionary() const{
	return pimpl->data_type == Dictionary;
}

bool json::is_string() const{
	return pimpl->data_type == String;
}


bool json::is_number() const{
	return pimpl->data_type == Number;
}


bool json::is_bool() const{
	return pimpl->data_type == Boolean;
}

bool json::is_null() const{
	return pimpl->data_type == Null;
}

const json& json::operator[](const std::string& str) const{
	if(is_dictionary()){
		for(const_dictionary_iterator it = begin_dictionary(); it != end_dictionary(); ++it){
			if(it->first == str){
				return it->second;
			}
		}
		throw json_exception {"String-key not found"};
	}
	else {
		throw json_exception {"You're trying to access to something other than a dictionary(const one)"};
	}
}

json& json::operator[](const std::string& str){
	if(is_dictionary()){
		for(dictionary_iterator it = begin_dictionary(); it != end_dictionary(); ++it){
			if(it->first == str){
				return it->second;
			}
		}
		json t;
		std::pair<std::string,json> pair(str, t);
		pimpl->d_tail->next = new dictionary{pair, nullptr};
		pimpl->d_tail = pimpl->d_tail->next;
		return pimpl->d_tail->pa.second;
	}
	else {
		throw json_exception {"You're trying to access to something other than a dictionary"};
	}
}

json::list_iterator json::begin_list(){
	if(is_list()){
		return {pimpl->l_head};
	}else{
		throw json_exception {"Called begin_list (no const) in a type other than a list"};
	}
}
json::list_iterator json::end_list(){
	if(is_list()){
		return {nullptr};
	}else{
		throw json_exception {"Called end_list (no const) in a type other than a list"};
	}
}

json::const_list_iterator json::begin_list() const{
	if(is_list()){
		return {pimpl->l_head};
	}else{
		throw json_exception {"Called begin_list (const) in a type other than a list"};
	}
}
json::const_list_iterator json::end_list() const{
	if(is_list()){
		return {nullptr};
	}else{
		throw json_exception {"Called end_list (const) in a type other than a list"};
	}
}

json::dictionary_iterator json::begin_dictionary(){
	if(is_dictionary()){
		return {pimpl->d_head};
	}else{
		throw json_exception {"Called begin_dictionary (no const) in a type other than a dictionary"};
	}
}
json::dictionary_iterator json::end_dictionary(){
	if(is_dictionary()){
		return {nullptr};
	}else{
		throw json_exception {"Called end_dictionary (no const) in a type other than a dictionary"};
	}
}

json::const_dictionary_iterator json::begin_dictionary() const{
	if(is_dictionary()){
		return {pimpl->d_head};
	}else{
		throw json_exception {"Called begin_dictionary (const) in a type other than a dictionary"};
	}
}
json::const_dictionary_iterator json::end_dictionary() const{
	if(is_dictionary()){
		return {nullptr};
	}else{
		throw json_exception {"Called end_dictionary (const) in a type other than a dictionary"};
	}
}

double& json::get_number(){
	if(is_number()){
		return pimpl->n;
	}
	else {
		throw json_exception {"You're trying to get a non-number"};
	}
}

const double& json::get_number() const{
	if(is_number()){
		return pimpl->n;
	}
	else {
		throw json_exception {"You're trying to get a non-number (const)"};
	}
}

bool& json::get_bool(){
	if(is_bool()){
		return pimpl->b;
	}
	else {
		throw json_exception {"You're trying to get a non-boolean"};
	}
}

const bool& json::get_bool() const{
	if(is_bool()){
		return pimpl->b;
	}
	else {
		throw json_exception {"You're trying to get a non-boolean (const)"};
	}
}

std::string& json::get_string(){
	if(is_string()){
		return pimpl->string;
	}
	else {
		throw json_exception {"You're trying to get a non-string"};
	}
}

const std::string& json::get_string() const{
	if(is_string()){
		return pimpl->string;
	}
	else {
		throw json_exception {"You're trying to get a non-string (const)"};
	}
}

void json::impl::delete_all(){
	if(data_type == List){
		delete_rec_list(l_head);
		l_head = l_tail = nullptr;
	}
	else if(data_type == Dictionary){
		delete_rec_dict(d_head);
		d_head = d_tail = nullptr;
	}
	n = 0.0;
	b = false;
	string.clear();
	data_type = Null;
}

void json::impl::delete_rec_list(list_ptr& l){
	if(l){
		delete_rec_list(l->next);
		l->info.pimpl->delete_all();
		delete l;
		l = nullptr;
	}
}

void json::impl::delete_rec_dict(dict_ptr& d){
	if(d){
		delete_rec_dict(d->next);
		d->pa.second.pimpl->delete_all();
		delete d;
		d = nullptr;
	}
}

void json::set_string(const std::string& str){
	pimpl->delete_all();
	pimpl->data_type = String;
	pimpl->string = str;
}

void json::set_bool(bool b){
	pimpl->delete_all();
	pimpl->data_type = Boolean;
	pimpl->b = b;
}

void json::set_number(double num){
	pimpl->delete_all();
	pimpl->data_type = Number;
	pimpl->n = num;
}

void json::set_null(){
	pimpl->delete_all();
	pimpl->data_type = Null;
}

void json::set_list(){
	pimpl->delete_all();
	pimpl->data_type = List;
	pimpl->l_head = pimpl->l_tail = nullptr;
}

void json::set_dictionary(){
	pimpl->delete_all();
	pimpl->data_type = Dictionary;
	pimpl->d_head = pimpl->d_tail = nullptr;
}

void json::push_front(const json& x){
	if(is_list()){
		pimpl->l_head = new list{x, pimpl->l_head}; // this is the new first list block with info = x and next = l_head
	}													// after the generation of the new block it will automatically be assigned to l_head as new head
	else{
		throw json_exception {"Trying a push front to a non-list type"};
	}
}

void json::push_back(const json& x){
	if(is_list()){
		if(!pimpl->l_head && !pimpl->l_tail){
			pimpl->l_head = pimpl->l_tail = new list{x, nullptr};
		}else{
			pimpl->l_tail->next = new list{x, nullptr}; // place the new json object as next of the tail of the list
			pimpl->l_tail = pimpl->l_tail->next; // move the tail to the new last element
		}
	}													
	else{
		throw json_exception {"Trying a push back to a non-list type"};
	}
}

void json::insert(const std::pair<std::string,json>& j){
	if(is_dictionary()){
		if(!pimpl->d_head){
			pimpl->d_head = pimpl->d_tail = new dictionary{j, nullptr};
		}else{
			pimpl->d_tail->next = new dictionary{j, nullptr};
			pimpl->d_tail = pimpl->d_tail->next;
		}
	}
	else{
		throw json_exception {"Trying an insert to a non-dictionary type"};
	}
}

/*	I       -> [ L ] | { D } | "string" | number | boolean | null
	L       -> I L' (it's just L,L)
	L'      -> ε | , I L'
	D       -> "string" : I D'
	D'      -> ε | , D
*/
void L(std::istream& lhs, json& rhs);
void D(std::istream& lhs, json& rhs);

std::istream& operator>>(std::istream& lhs, json& rhs){
	char c = 0;
	lhs >> c;
	if((c >= '0' && c <= '9') || (c == '"') || (c == 't' || c == 'f') || (c == 'n')){ // terminals
		if(c >= '0' && c <= '9'){
			lhs.putback(c);
			double num;
			lhs >> num;
			rhs.set_number(num);
		}
		else if(c == '"'){
			c = static_cast<char>(lhs.get());
			char prev = 0;// keep the 'prev' char one char berfore 'curr' in the input stream
			std::string s;
			bool stop = false;
			while(!stop){
				if(c == '"'){
					if(prev != '\\'){
						stop = true;
					}else{
						s.push_back(c);
						prev = c;
						c = static_cast<char>(lhs.get());
					}
				}else{
					s.push_back(c);
					prev = c;
					c = static_cast<char>(lhs.get());
				}
			}
			rhs.set_string(s);
		}
		else if(c == 't' || c == 'f'){ // means there is true of false
			std::string boolean;
			if(c == 't'){
				lhs.putback(c);
				int i = 0;
				while(i < 4){
					boolean += static_cast<char>(lhs.get());
					i++;
				}
			}
			else if (c == 'f') {
				lhs.putback(c);
				int i = 0;
				while(i < 5){
					boolean += static_cast<char>(lhs.get());
					i++;
				}
			}
			if(boolean == "true"){
				rhs.set_bool(true);
			}
			else if(boolean == "false"){
				rhs.set_bool(false);
			}
			else{
				throw json_exception {"An error occurred while retrieving a boolean variable"};
			}
		}
		else if(c == 'n'){
			std::string null;
			int i = 0;
			while(i < 4){
				null += c;
				lhs.get(c);
				i++;
			}
			lhs.putback(c); // put back on the stream the end char
			if(null == "null"){
				rhs.set_null();
			}
			else{
				throw json_exception {"An error occurred while retrieving a null variable"};
			}
		}
		else{
			throw json_exception {"An error occurred while retrieving a null/boolean/double/string variable"};
		}
	}
	else if(c == '['){ // list
		rhs.set_list();
		L(lhs, rhs);
		lhs >> c;
		if(c != ']'){
			throw json_exception {"There might be a missing ']' at the end of a list"};
		}
		if(lhs.peek() == ']' || lhs.peek() == '}'){
			throw json_exception {"There might be an extra '}' or ']'"};
		}
	}
	else if(c == '{'){ // dictionary
		rhs.set_dictionary();
		D(lhs, rhs);
		lhs >> c;
		if(c != '}'){
			throw json_exception {"There might be a missing '}' at the end of a dictionary"};
		}
		if(lhs.peek() == ']' || lhs.peek() == '}'){
			throw json_exception {"There might be an extra '}' or ']'"};
		}
	}
	else{
		throw json_exception {"Unknown token"};
	}
	return lhs;
}

void L(std::istream& lhs, json& rhs){
	char c = 0;
	json j;
	if(lhs.peek() == ']'){
		return;
	}else{
		lhs >> j;
		rhs.push_back(j);
		lhs >> c;
		if(c == ','){
			L(lhs, rhs);
		}else if(c == ']'){
			lhs.putback(c);
			return;
		}else{
			throw json_exception {"Invalid list"};
		}
	}
}

void D(std::istream& lhs, json& rhs){
	if(lhs.peek() == '}'){
		return;
	}
	char c = 0;
	std::pair<std::string,json> pa;
	lhs >> c;
	if(c == '"'){
		char prev = 0;// keep the 'prev' char one char berfore 'curr' in the input stream
		c = static_cast<char>(lhs.get());
		bool stop = false;
		while(!stop){
			if(c == '"'){
				if(prev != '\\'){
					stop = true;
				}else{
					pa.first.push_back(c);
					prev = c;
					c = static_cast<char>(lhs.get());
				}
			}else{
				pa.first.push_back(c);
				prev = c;
				c = static_cast<char>(lhs.get());
			}
		}
		lhs >> c;
		if(c == ':'){
			lhs >> pa.second;
			rhs.insert(pa);
			lhs >> c;
			if(c == ','){
				D(lhs, rhs);
			}
			else if(c == '}'){
				lhs.putback(c);
				return;
			}
		} 
		else{
			throw json_exception {"Possible missing or too many characters in a dictionary"};
		}
		
	}
	else{
		throw json_exception {"Invalid dictionary"};
	}
}

	

void list_print(std::ostream& lhs, const json& rhs);
void dictionary_print(std::ostream& lhs, const json& rhs);

std::ostream& operator<<(std::ostream& lhs, const json& rhs){
	if(rhs.is_number()){
		lhs << rhs.get_number();
	}
	else if(rhs.is_bool()){
		bool res = rhs.get_bool();
		if(res){
			lhs << "true";
		}else{
			lhs << "false";
		}
	}
	else if(rhs.is_string()){
		lhs << '"' << rhs.get_string() << '"';
	}
	else if(rhs.is_list()){
		list_print(lhs, rhs);
	}
	else if(rhs.is_dictionary()){
		dictionary_print(lhs, rhs);
	}
	return lhs;
}

void list_print(std::ostream& lhs, const json& rhs){
	lhs << "[";
	json::const_list_iterator it = rhs.begin_list();
	if(it != rhs.end_list()){
		lhs << *it;
		++it;
	}
	while(it != rhs.end_list()){
		if(!it->is_null()){
			lhs << ',' << *it;
		}
		++it;
	}
	lhs << "]";
}

void dictionary_print(std::ostream& lhs, const json& rhs){
	lhs << "{";
	json::const_dictionary_iterator it = rhs.begin_dictionary();
	if(it != rhs.end_dictionary()){
		lhs << '"' << it->first << '"' << ":" << it->second;
		++it;
	}
	while(it != rhs.end_dictionary()){
		if(it->second.is_null()){
			lhs << ',' << '"' << it->first << '"' << ":";
			++it;
		}else{
			lhs << ',' << '"' << it->first << '"' << ":" << it->second;
			++it;
		}
	}
	lhs << "}";
}

/* 
 * Nel main ci sarà:
 * #include <fstream>
 * 
 * ...
 * 
 * std::ifstream is("in.json");
 * std::ofstream os("out.json");
 * json j;
 * is >> j;
 * os << j;
 * 
 * ...
 * 
 * */
