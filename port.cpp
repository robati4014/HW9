#include "port.h"
#include <cstdlib>

Port::Port(String pattern): Field(pattern, PORT) {

}

bool Port::set_value(String val) {

	String *substrs;

	size_t size = 0;

	
	val.split("-", &substrs, &size);
	
	if(2 != size)
	{
		/* if size == 0 then substr was not allocated */
		if(0 != size){
			delete[] substrs;
		}
		return false;
	}

	/* now we should have 2 ports for port range */
	range[0] = substrs[0].trim().to_integer();
	range[1] = substrs[1].trim().to_integer();

	delete[] substrs;
	if(range[0] > range[1]){
		return false;
	}else{
		return true;
	}
}

bool Port::match_value(String val) const {
	int int_val = val.trim().to_integer();

	return ( (range[0] <= int_val) && (int_val <= range[1])); 
}

