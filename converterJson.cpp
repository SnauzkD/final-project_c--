//
// Created by shoxk on 24.01.2026.
//

#include "../converterJson.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <exception>
#include <iostream>

std::vector<std::string> converterJson::GetTextDocuments() {
    std::vector<std::string> textDocuments;
    try {
        std::ifstream config("config.json");
        if (!config.is_open()) {
            throw std::runtime_error("Config file is missing!");
        }
        nlohmann::json j;
        config >> j;
        if (!j.contains("config") || j["config"].empty())
            throw std::runtime_error("config file is empty");
        for (auto file: j["files"]) {
            std::ifstream filestream(file);
            if (!filestream.is_open())
                throw std::runtime_error("Could not open the file");
            std::string content;
            std::stringstream buffer;
            buffer << filestream.rdbuf();

            content = buffer.str();
            textDocuments.push_back(content);
            filestream.close();
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return {};
    };
    return textDocuments;
}
int converterJson::GetResponsesLimit() {
    int limit = 5;
    try {
        std::ifstream config("config.json");
        if (!config.is_open()) {
            throw std::runtime_error("Config file is missing!");
        }
        nlohmann::json j;
        config >> j;
        if (!j.contains("config") || j["config"].empty())
            throw std::runtime_error("config file is empty");
        if (!j["config"].contains("max_responses"))
            return limit;
        limit = j["config"]["max_responses"].get<int>();
        config.close();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 5;
    }
    return limit;
}
std::vector<std::string> converterJson::GetRequests() {
    std::vector<std::string> requests;
    try {
        std::ifstream config("requests.json");
        if (!config.is_open()) {
            throw std::runtime_error("Requests file is missing!");
        }
        nlohmann::json j;
        config >> j;
        if (!j.contains("requests") || j["requests"].empty())
            throw std::runtime_error("requests file is empty");

        for (auto request: j["requests"]) {
            requests.push_back(request);
        }
        config.close();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return {};
    }
    return requests;
}
void converterJson::inputAnswers(std::vector<std::vector<std::pair<int, float> > > answers) {
    nlohmann::json answersJson;
    answersJson = {{"answers",nlohmann::json::object()}};
    for (int i = 0; i < answers.size();i++) {
            std::stringstream ss;
            ss << "request" << std::setw(3) << std::setfill('0') << (i + 1);
            std::string request = ss.str(); // request001
            answersJson["answers"][request];
        if (answers[i].empty()) {
            answersJson["answers"][request]["result"] = "false";
        }
        else {
            answersJson["answers"][request]["result"] = "true";

            nlohmann::json relevanceArray = nlohmann::json::array();

            for (auto& doc : answers[i]) {
                nlohmann::json docJson;
                docJson["docid"] = doc.first;
                docJson["rank"] = doc.second;
                relevanceArray.push_back(docJson);
            }
            answersJson["answers"][request]["relevance"] = relevanceArray;
        }

    }
    std::ofstream writeFile("answers.json");
    writeFile << answersJson;
    writeFile.close();
}




