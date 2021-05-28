#pragma once

#include <string>
#include <vector>
#include "../DesignExtractor.h"
#include <unordered_map>
#include <unordered_set>

class QueryDEInterface {
private:
    QueryDEInterface(); // Prevent construction
    QueryDEInterface(const PKB&); // Prevent construction by copying
    QueryDEInterface& operator=(const PKB&); // Prevent assignment
    ~QueryDEInterface(); // Prevent unwanted destruction

public:
    //Singleton Implementation

    static QueryDEInterface& getInstance() {
        static QueryDEInterface instance;
        return instance;
    }

    //CACHE
    void clearTemporaryCache();

	//Design Abstractions (relRef)
	//--NEXT*--------------------------------------------------------------------------------------------------
	//----Find----
    std::vector<std::string> getNextStar(std::string firstLine);
    std::vector<std::string> getPreviousStar(std::string nextLine);
    int getSizeNextStar();
    int getSizePreviousStar();
    int getAreaNextStar();
	//----Assert----
    bool isNextStar(std::string firstLine, std::string secondLine);
    //bool isNextStarEmpty();

    //--Affects--------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAffects(std::string firstLine);
    std::vector<std::string> getAffectedBy(std::string nextLine);

    //----Assert----
    bool isAffects(std::string firstLine, std::string secondLine);

    //--Affects*--------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAffectsStar(std::string firstLine);
    std::vector<std::string> getAffectedByStar(std::string nextLine);

    //----Assert----
    bool isAffectsStar(std::string firstLine, std::string secondLine);

};

