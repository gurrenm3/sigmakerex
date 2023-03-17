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

	// loop over all functions.
	for (int i = 0; i < function_count; ++i)
	{
		//if (i < 9711 + 6289 + 6540 + 40640 + 10240 + 6750 + 1350)
		if (i < 9711) // start at 9711
			continue;

		if (i % (function_count / 100) == 0)
		{
			save();
			std::stringstream percent_msg;
			percent_msg << "Functions completed: " << std::to_string(i) << "\n";
			msg(percent_msg.str().c_str());
		}
		auto func_ptr = getn_func(i);

		// check that mangled name is not banned.
		qstring mangled_name;
		get_func_name(&mangled_name, func_ptr->start_ea);
		if (FunctionParser::is_name_banned(mangled_name.c_str()))
		{
			banned_functions.push_back(mangled_name.c_str());
			continue;
		}

		auto full_func_name = FunctionParser::get_function_name(func_ptr->start_ea);

		if (!should_export_sigs)
		{
			functions_and_sigs.emplace(full_func_name.c_str(), "");
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
	}

	// save to file.
	save();
}

void FunctionExporter::save()
{
	// save to file.
	nlohmann::json j;

	j["functions_and_sigs"] = functions_and_sigs;
	j["failed_to_find_functions_sigs"] = failed_to_find_functions_sigs;
	j["exception_finding_functions"] = exception_finding_functions;
	j["banned_functions"] = banned_functions;

	File json_file(path);
	json_file.Write(j.dump());
	

	/*std::ofstream json_file;
	json_file.open(path);
	json_file << j.dump();*/
}
