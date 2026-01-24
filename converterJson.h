#ifndef FINALPROJECT_CONVERTERJSON_H
#define FINALPROJECT_CONVERTERJSON_H
#include <string>
#include <vector>

class converterJson {
    converterJson() = default;
public:
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string>GetRequests();
    void inputAnswers(std::vector<std::vector<std::pair<int,float>>> answers);

};


#endif //FINALPROJECT_CONVERTERJSON_H