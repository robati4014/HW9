#include "ip.h"
#include <cstring>
#include <iostream>

Ip::Ip(String pattern): Field(pattern, IP) {

}


bool Ip::set_value(String val){

	String *substrs;

	size_t size = 0;

	val.split("/", &substrs, &size);

	if(2 != size)
	{
		/* if size == 0 then substr was not allocated */
		if(0 != size){
			delete[] substrs;
		}
		return false;
	}

	/* now we should have ip address and mask number */
	int ip = substrs[0].trim().to_integer();
	/* 32 - val = nubmer of lower bits to ignore */
	int n = 32 - substrs[1].trim().to_integer(); 
	
	delete[] substrs;

	
	if((n < 0) || (n > 32)) {
		return false;
	}

	/* set lower n bits to 1 */
	unsigned int bitmask = (n == 32) ? 0xFFFFFFFF : ((unsigned int)1 << n) - 1;


	/* val: 192.168.1.0/8
	address = 192.168.1.0 , mask = 8
	n = 32 - 8 = 24
	low = 192.0.0.0
	high = 192.255.255.255
	*/

	low = ip & (~bitmask);
	high = ip | bitmask; 

	return true;
}

bool Ip::match_value(String val) const {
	unsigned int int_val = (unsigned int)val.trim().to_integer();
	return ((low <= int_val) && (int_val <= high));
}