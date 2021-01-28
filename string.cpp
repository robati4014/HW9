#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h" 

/* Default constructor */
String::String(){
	data = NULL;
	length = 0;
}

/* Copy constructor */
String::String(const String &str){
	length = str.length;
	
	/* if empty string - return */
	if(0 == length){
		data = NULL;
	}else{
		data = new char[length + 1];

		if(NULL != data){
			strncpy(data, str.data, length + 1);
		}else{
			length = 0;
		}
	}
}

/* constructor */
String::String(const char *str){
	// check for nullptr
	if(NULL == str){
		data = NULL;
		length = 0;
		return;
	}

	length = strlen(str); 
	
	/* if empty string - return */
	if(0 == length){
		data = NULL;
	}else{
		data = new char[length + 1];
		
		if(NULL != data){
			strncpy(data, str, length + 1);
		}else{
			length = 0;
		}
	}
}

String::~String(){
	if(NULL != data) {
		delete[] data;
	}
}

String& String::operator=(const String &rhs){
	
	/*Free old string */
	if(NULL != data) {
		delete[] data;
	}

	length = rhs.length;
	
	/* if empty string - return */
	if(0 == length){
		data = NULL;
	}
	else{
		data = new char[length];

		if(NULL != data){
			strncpy(data, rhs.data, length);
		}
		else{
			length = 0;
		}
	}

	return *this;
}

String& String::operator=(const char *str){
	/* Free old string */
length = strlen(str);
	

	if(NULL != data ) {
		delete[] data;
	}

	/*check for NULL parameter */
	if(NULL == str)
	{
		data = NULL;
		length = 0;
		return *this;
	}

	

	/* if empty string - return */
	if(0 == length){
		data = NULL;
	}else{
		data = new char[length + 1];
		
		if(NULL != data){
			strncpy(data, str, length + 1);
		}else{
			length = 0;
		}
	}

	return *this;
}

bool String::equals(const String &rhs) const {
	if(length != rhs.length){
		return false;
	}

	if(0 != strncmp(data, rhs.data, length)){
		return false;
	}

	return true;
}

bool String::equals(const char *rhs) const {
	if(NULL == rhs)
	{
		return false;
	}

	if(length != strlen(rhs)){
		return false;
	}

	/* Should we verify that data != NULL ? */
	if(0 != strncmp(data, rhs, length)){
		return false;
	}

	return true;
}

void String::split(const char *delimiters, String **output, size_t *size) const{
	int start = 0, substr = 0;
	unsigned int delimiter = 0, num_delimiters = 0;
	/* if no delimiters in our string then return the whole string - therefore 
	at least 1 substring */
	unsigned int num_substrings = 1; 
	char data_copy[length + 1] = {0};

	if(NULL == size){
		return;
	}

	*size = 0;

	if(NULL == delimiters || NULL == data){ 
		return;
	}

	/* copy original string to temporary value */
	strncpy(data_copy, data, length);
	data_copy[length] = '\0';

	num_delimiters = strlen(delimiters);
	/*count number of substrings */
	for(unsigned int i = 0; i < length; i++){
		for(delimiter = 0; delimiter < num_delimiters; delimiter++){
			if(data_copy[i] == delimiters[delimiter]){
				num_substrings++;
			}
		} 
	}

	*size = num_substrings;
		if(NULL == output){
			return;
		
	}

	/* allocate substrings */
	*output = new String[num_substrings];

	/*copy each substring to output */
	for(unsigned int i = 0; i < length; i++){
		for(delimiter = 0; delimiter < num_delimiters; delimiter++){
			if(data_copy[i] == delimiters[delimiter]){
				data_copy[i] = '\0';
				(*output)[substr] = String(&data_copy[start]);
				start = i + 1;
				substr++;
			}
		} 
	}

	/* set the last substring */
	(*output)[substr] = String(&data_copy[start]);
	return;
}

String String::trim() const {
	int start = 0;
	int end = length - 1;

	if(NULL == data){
		return String();
	}

	/*remove spaces from begining */
	while(data[start] == ' '){
		start++;
	}

	/*remove spaces from end */
	while((data[end] == ' ') && (start != end)){
		end--;
	}
	end++;

	/* if no characters in the string - return empty string */
	if(start >= end)
	{
		return String();
	}

	char new_data[end - start + 1];
	strncpy(new_data, &data[start], end - start);
	new_data[end - start] = '\0';


	return String(new_data);
}

int String::to_integer() const { 
	int ret = 0;
	String *substrs;
	size_t size = 0;

	/* if our data is a string representing ip */
	split(".", &substrs, &size);
	
	if(SEGMENTS == size) {

		/* trim the each  sub string and build full integer */
		for(unsigned int i = 0; i < size; i++){
			int byte = substrs[i].trim().to_integer();
			/* if substring is > 255 - the address is not valid */
			if((byte > 255) || (byte < 0)){
				delete[] substrs;
				return 0;
			}
			ret |= byte << (24 - (8 * i));
		}

		delete[] substrs;
		return ret;
	
	}else{ 
		
		ret = atoi((this->trim()).data);
		if(0 != ret){
			if( NULL != substrs){
				delete[] substrs;
			}
			return ret;
		}
	}

	if( NULL != substrs){
		delete[] substrs;
	}
	return 0;
}
