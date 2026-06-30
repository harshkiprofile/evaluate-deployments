/*
===============================================================================
Problem    : Evaluate Deployment Logs
Language   : C++17

Description:
Given a log file containing deployment records in JSON format, determine the
number of successful deployments, failed deployments, and invalid/error records.

Validation Rules:
- deployment_id must match: d-[a-z0-9]{10}
- status must be either "Success" or "Fail"
- Malformed JSON, missing fields, invalid data types, or invalid values are
  counted as errors.

Approach:
1. Read deployment logs from a file.
2. Parse each log using nlohmann::json.
3. Validate the deployment ID using std::regex.
4. Validate the deployment status.
5. Maintain counters for Success, Fail, and Error.

Time Complexity : O(n)
Space Complexity: O(n)
===============================================================================
*/

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "Header.h"

using json = nlohmann::json;

// Valid deployment ID:
// d- followed by exactly 10 lowercase alphanumeric characters.
const std::regex DEPLOYMENT_ID_PATTERN(R"(^d-[a-z0-9]{10}$)");

void readLogs(std::ifstream& file, std::vector<std::string>& logs)
{
    std::string line;

    while (std::getline(file, line))
    {
        // Ignore empty lines in the log file.
        if (!line.empty())
        {
            logs.push_back(line);
        }
    }
}

bool isValidDeploymentId(const std::string& deploymentId)
{
    return std::regex_match(deploymentId, DEPLOYMENT_ID_PATTERN);
}

int main()
{
    std::ifstream logFile("json.log");

    if (!logFile.is_open())
    {
        std::cerr << "Error: Unable to open json.log\n";
        return EXIT_FAILURE;
    }

    std::vector<std::string> deploymentLogs;
    readLogs(logFile, deploymentLogs);

    int success = 0;
    int failed = 0;
    int errors = 0;

    for (const auto& log : deploymentLogs)
    {
        try
        {
            json parsedJson = json::parse(log);

            const std::string deploymentId = parsedJson.at("deployment_id");
            const std::string status = parsedJson.at("status");

            if (!isValidDeploymentId(deploymentId))
            {
                ++errors;
                continue;
            }

            if (status == "Success")
            {
                ++success;
            }
            else if (status == "Fail")
            {
                ++failed;
            }
            else
            {
                ++errors;
            }
        }
        catch (const json::exception&)
        {
            // Handles malformed JSON, missing keys,
            // invalid types, and other JSON-related errors.
            ++errors;
        }
    }

    std::cout << "=====================================\n";
    std::cout << " Deployment Summary\n";
    std::cout << "=====================================\n";
    std::cout << "Successful Deployments : " << success << '\n';
    std::cout << "Failed Deployments     : " << failed << '\n';
    std::cout << "Invalid/Error Records  : " << errors << '\n';
    std::cout << "=====================================\n";

    return EXIT_SUCCESS;
}