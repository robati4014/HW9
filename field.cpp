#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>

/* Default constructor */
Field::Field(String pattern, field_type type) {
	this->pattern = pattern;
	this->type = type;
}

/* Copy construtoctor */
Field::Field(String pattern){
	this->pattern = pattern;
	this->type = GENERIC;
}

Field::~Field() {
}

field_type Field::get_type() const {
	return type;
}

/* will be overriden */
bool Field::set_value(String val) {
	if(type == IP){
		return ((Ip*)this)->set_value(val);
	}
	if(type == PORT){
		return ((Port*)this)->set_value(val);
	}
	return false;
}

/* will be overriden */
bool Field::match_value(String val) const {
	
	if(type == IP){
		return ((Ip*)this)->match_value(val);
	}
	if(type == PORT){
		return ((Port*)this)->match_value(val);
	}
	return false;
}


bool Field::match(String packet) {
	String *substrs;
	String *name_value_substrs;
	size_t size = 0, expected_size2 = 2; /*for name and value*/
	unsigned int i = 0;
	bool ret_val = false;

	/* split by "," */
	packet.split(",", &substrs, &size);
	if( 0 == size ){
		return false;
	}
	
	for(i = 0; i < size; i ++){
		/*split to name and value */
		substrs[i].split("=", &name_value_substrs, &expected_size2);
		
		if( 0 == expected_size2 ){
			continue;
		}  

		if(2 == expected_size2){
			if(pattern.trim().equals(name_value_substrs[0].trim())){
				ret_val = match_value(name_value_substrs[1].trim());
			}
		}
		
		delete[] name_value_substrs;
	}

	delete[] substrs;
	return ret_val;
}