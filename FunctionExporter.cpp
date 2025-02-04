#include "FunctionExporter.h"

//#include <fstream>
#include "File.h"

//#include <fstream>


//#include <funcs.hpp>
//#include <kernwin.hpp>
//#include <sstream>
//#include "FunctionParser.h"
//#include "SigMaker.h"
//#include "SigResults.h"

FunctionExporter::FunctionExporter(std::string path)
{
	this->path = path;
	std::stringstream output;
	output << "Function Exporter will save to: \"" << path << "\"\n";
	msg(output.str().c_str());
}

void FunctionExporter::export_all(bool should_export_sigs)
{
	const int function_count = get_func_qty();

	// print count message.
	std::stringstream count_msg;
	count_msg << "Exporting " << std::to_string(function_count) << " functions...\n";
	msg(count_msg.str().c_str());

	int printCount = 0;

	// loop over all functions.
	for (int i = 0; i < function_count; ++i)
	{
		//if (i < 9711 + 6289 + 6540 + 40640 + 10240 + 6750 + 1350)
		if (i < 9711) // start at 9711
			continue;

		if (i % (function_count / 100) == 0)
		{
			/*save();
			std::stringstream percent_msg;
			percent_msg << "Functions completed: " << std::to_string(i) << "\n";
			msg(percent_msg.str().c_str());*/
		}
		func_t* func_ptr = getn_func(i);
		auto eaStart = &func_ptr->start_ea;
		auto eaEnd = &func_ptr->end_ea;

		std::stringstream funcPtr_msg;
		funcPtr_msg << "----------------------------------\n";
		funcPtr_msg << "funcPtr: " << std::to_string((long)func_ptr) << "...\n";
		funcPtr_msg << "start_ea: " << std::to_string((long)eaStart) << "...\n";
		funcPtr_msg << "eaEnd: " << std::to_string((long)eaEnd) << "...\n";
		msg(funcPtr_msg.str().c_str());

		printCount++;
		if (printCount > 15)
			return;
		continue;



		// check that mangled name is not banned.
		qstring mangled_name;
		get_func_name(&mangled_name, func_ptr->start_ea);


		/*bool isCtorDtor = StringUtils::contains(mangled_name.c_str(), "??"); 
		if (!StringUtils::contains(mangled_name.c_str(), "NetMessage") && !StringUtils::contains(mangled_name.c_str(), "SetupSlotUI"))
		{
			continue;
		}

		if (StringUtils::contains(mangled_name.c_str(), "cGcRpcCall"))
		{
			continue;
		}*/

		std::stringstream ss;
		ss << "MangledName: " << mangled_name.c_str() << "\n";
		msg(ss.str().c_str());


		if (FunctionParser::is_name_banned(mangled_name.c_str()))
		{
			banned_functions.push_back(mangled_name.c_str());
			continue;
		}

		auto full_func_name = FunctionParser::get_function_name(func_ptr->start_ea);

		if (!should_export_sigs)
		{
			functions_and_sigs.emplace(full_func_name.c_str(), "");
			auto details = FunctionDetails(full_func_name.c_str(), "", false, isCtorDtor);
			extracted_functions.push_back(details);
			continue;
		}

		// get function sig
		SigResults scan_results;
		try
		{
			scan_results = CreateFunctionSig(func_ptr, false);
		}
		catch (...)
		{
			std::stringstream ss;
			ss << "Encountered exception when trying to get pattern for " << full_func_name.c_str() << "\n";
			msg(ss.str().c_str());
			exception_finding_functions.push_back(full_func_name.c_str());
			continue;
		}

		if (!scan_results.DidSucceed())
		{
			failed_to_find_functions_sigs.push_back(full_func_name.c_str());
			continue;
		}

		qstring patternStr;
		scan_results.outSig.ToIdaString(patternStr);

		functions_and_sigs.emplace(full_func_name.c_str(), patternStr.c_str());

		auto details = FunctionDetails(full_func_name.c_str(), patternStr.c_str(), scan_results.IsXRefSig(), isCtorDtor);
		extracted_functions.push_back(details);
	}

	// save to file.
	save();
}

void FunctionExporter::save()
{
	// save to file.
	nlohmann::json jsonFile;

	jsonFile["GamePlatform"] = "GOG";

	std::vector<nlohmann::json> test;
	for (size_t i = 0; i < extracted_functions.size(); i++)
	{
		nlohmann::json functionInfo;
		auto function = extracted_functions[i];
		functionInfo["name"] = function.functionName;
		functionInfo["sig"] = function.functionSig;
		functionInfo["isXrefSig"] = function.isXrefSig;
		functionInfo["isConstructor"] = function.isConstructor;
		functionInfo["isDestructor"] = function.isDestructor;
		test.push_back(functionInfo);
	}

	jsonFile["functions_and_sigs"] = test;

	jsonFile["failed_to_find_functions_sigs"] = failed_to_find_functions_sigs;
	jsonFile["exception_finding_functions"] = exception_finding_functions;
	jsonFile["banned_functions"] = banned_functions;

	
	File json_file(path);
	json_file.Write(jsonFile.dump(1));
}

//void FunctionExporter::save()
//{
//	// save to file.
//	nlohmann::json j;
//
//	j["GamePlatform"] = "GOG";
//	j["functions_and_sigs"] = functions_and_sigs;
//	j["failed_to_find_functions_sigs"] = failed_to_find_functions_sigs;
//	j["exception_finding_functions"] = exception_finding_functions;
//	j["banned_functions"] = banned_functions;
//
//	File json_file(path);
//	json_file.Write(j.dump());
//	
//
//	/*std::ofstream json_file;
//	json_file.open(path);
//	json_file << j.dump();*/
//}
