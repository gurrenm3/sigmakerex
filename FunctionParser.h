#pragma once
#include <pro.h>
#include <string>
#include <sstream>

class FunctionParser
{
public:
	static bool is_name_banned(std::string funcName);
	static qstring get_function_name(ea_t func_address);
};

