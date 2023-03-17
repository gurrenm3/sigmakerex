#include "FunctionParser.h"

bool FunctionParser::is_name_banned(std::string funcName)
{
    if (!funcName.starts_with("?") || funcName.starts_with("??") || StringUtils::contains(funcName, "TkSTLAllocatorShim")
        || StringUtils::contains(funcName, "StackAllocator") || StringUtils::contains(funcName, "cTkLinearHashTable"))
        return false;

    if (StringUtils::contains(funcName, "_Func_impl_no_alloc") || StringUtils::contains(funcName, "robin_hood"))
        return false;

    if (StringUtils::contains(funcName, "deleteNodeContent@XMLNode@@QEAA"))
    {
        msg("Found \"deleteNodeContent@XMLNode@@QEAA\", skipping\n");
        return false;
    }

    return  true;
}

qstring FunctionParser::get_function_name(ea_t func_address)
{
    // get function info
    auto tif = tinfo_t();
    get_tinfo(&tif, func_address);
    auto func_data = func_type_data_t();
    tif.get_func_details(&func_data);

    if (!tif.is_func())
        return nullptr;

    // get demangled name.
    qstring demangled_name;
    get_func_name(&demangled_name, func_address);
    demangled_name = demangle_name(demangled_name.c_str(), 0);


    std::stringstream full_func_name;

    // adds the return type and function name
    full_func_name << StringUtils::split(demangled_name.c_str(), '(')[0];


	// add arguments
	bool firstArg = true;
	full_func_name << "(";
	for (auto arg : func_data)
	{
		if (!firstArg)
			full_func_name << ", ";

		/*qstring argType = dstr_tinfo(&arg.type);
		full_func_name << argType.c_str() << " " << arg.name.c_str();*/
        
        full_func_name << dstr_tinfo(&arg.type) << " " << arg.name.c_str();        
		firstArg = false;
	}
    full_func_name << ")";

    // clean name:
    qstring final_func_name = full_func_name.str().c_str();
    final_func_name.replace("public: ", "");
    final_func_name.replace("protected: ", "");
    final_func_name.replace("private: ", "");
    final_func_name.replace("internal: ", "");
    final_func_name.replace("virtual ", "");
    final_func_name.replace("static ", "");
    final_func_name.replace("class ", "");
    final_func_name.replace("enum ", "");
    final_func_name.replace("struct ", "");

    final_func_name.replace("unsigned ", "u");
    final_func_name.replace("int64", "long");
    final_func_name.replace("int32", "int");
    final_func_name.replace("int16", "short");
    final_func_name.replace("struct ", "");
    final_func_name.replace("const ", "");
    final_func_name.replace("enum ", "");
    final_func_name.replace(" &", "*");
    final_func_name.replace(" *", "*");
    final_func_name.replace("__", "");

    return final_func_name;
}
