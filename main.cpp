#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"


extern int check_args(int, char**);
extern void parse_input(Field&);

#if 1
int main(int argc, char **argv){



	if( 0 != check_args(argc, argv) ) {
		return 1;
	}


	String filter(argv[1]);
	String *substrs;
	size_t size = 0;

	/* there is only 1 rule*/
	filter.split("=", &substrs, &size);

	/* parse IP rule */
	if(substrs[0].trim().equals(String("src-ip")) || 
	   substrs[0].trim().equals(String("dst-ip"))){
		Ip ip_filter(substrs[0].trim()); 
		ip_filter.set_value(substrs[1].trim()); 
		/* filter  the packets from input according to rule */
		parse_input(ip_filter); 
	}

	/* parse PORT rule */
	if(substrs[0].trim().equals(String("src-port")) ||
	   substrs[0].trim().equals(String("dst-port"))){
	    Port port_filter(substrs[0].trim()); 
		port_filter.set_value(substrs[1].trim()); 
		/* filter  the packets from input according to rule*/
		parse_input(port_filter); 
	}

	delete[] substrs;
}


#endif






