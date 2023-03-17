#pragma once
#include <pro.h>
#include <string>
#include <sstream>
#include <typeinf.hpp>
#include "StringUtils.h"

class FunctionParser
{
public:
	static bool is_name_banned(std::string funcName);
	static qstring get_function_name(ea_t func_address);
};

