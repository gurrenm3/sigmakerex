#pragma once
//#include <map>
//#include <string>
//#include <vector>
//#include <sstream>

#include "nlohmann/json.hpp"
#include "FunctionParser.h"
#include "SigMaker.h"
#include "SigResults.h"


class FunctionExporter
{
public:
	FunctionExporter(std::string path);
	void export_all(bool should_export_sigs = true);

private:
	std::string path;
	std::map<std::string, std::string> functions_and_sigs;
	std::vector<std::string> banned_functions;
	std::vector<std::string> failed_to_find_functions_sigs;
	std::vector<std::string> exception_finding_functions;

	void save();
};

