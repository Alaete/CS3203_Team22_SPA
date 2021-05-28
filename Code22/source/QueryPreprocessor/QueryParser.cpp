#include "QueryParser.h"
#include "Query.h"

// Constructor and Deconstructor
QueryParser::QueryParser() {}
QueryParser::~QueryParser() {}

// Instance of Query Parser
QueryParser& QueryParser::getInstance() {
    static QueryParser instance;
    return instance;
}

void QueryParser::reset(bool isValid) {
    result.reset(isValid);
    queryString.clear();
    synonymsTable.clear();
    clauses.clear();
    selectedSynonyms.clear();
    startIndex = 0;
    endIndex = 0;
    isSelectBoolean = false;
    isValidSyntax = isValid;
}

// Main method for parsing and validating query
Query& QueryParser::parseQuery(const std::string& query_str) {
    reset(true);
    queryString = query_str;

    try {
        std::vector<std::string> listOfSubqueries = splitQuery(queryString, ';');

        // Parse declarations 
        for (unsigned int i = 0; i < listOfSubqueries.size() - 1; i++) {
            // parse and validate declaration
            parseDeclaration(listOfSubqueries[i]);
        }
        // Parse select
        parseSelect(listOfSubqueries.back());
    }
    catch (SyntaxErrorException& syntaxcError) {
        std::cout << syntaxcError.what() << std::endl;
        if (isSelectBoolean) {
            result.setIsSelectBoolean(true);
            result.addSelectedSynonyms(selectedSynonyms);
            result.addSynonymTable(synonymsTable);
            result.setIsValidSyntax(true);
            setInvalidQuery();
            result.setIsValidSemantic(true);
            result.addClauses(clauses);
            return GetQueryResult();
        }
        setInvalidQuery();
    }
    catch (SemanticErrorException& semanticError) {
        std::cout << semanticError.what() << std::endl;
        result.setIsValidSemantic(false);

        if (isSelectBoolean) {
            result.setIsSelectBoolean(true);
            result.addSelectedSynonyms(selectedSynonyms);
            result.addSynonymTable(synonymsTable);
            result.setIsValidSyntax(true);
            setInvalidQuery();
            result.setIsValidSemantic(true);
            result.addClauses(clauses);
            return GetQueryResult();
        }
        setInvalidQuery();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        setInvalidQuery();
    }

    if (isSelectBoolean) {
        result.setIsSelectBoolean(true);
    }

    result.addSelectedSynonyms(selectedSynonyms);
    result.addSynonymTable(synonymsTable);
    result.addClauses(clauses);
    result.setIsValidSemantic(true);
    return GetQueryResult();
};

Query& QueryParser::GetQueryResult() { return this->result; }

void QueryParser::setInvalidQuery() {
    reset(false);
}

// Parse Declarations and add declarations to synonym table
void QueryParser::parseDeclaration(std::string& str) {
    std::string declaration = trim(str);
    if (declaration.empty()) {
        throw SyntaxErrorException("Empty declaration");
    }
    unsigned int spaceIndex = declaration.find(" ");
    std::string design_entity = declaration.substr(0, spaceIndex);

    if (spaceIndex == std::string::npos) {
        throw SyntaxErrorException("Invalid declaration: " + declaration);
    }
    Query::DesignEntityType dentity_type = getDesignEntity(design_entity);

    std::string synonyms = declaration.substr(spaceIndex + 1);
    std::vector<std::string> synonyms_list = splitSynonym(synonyms, ',');

    if (synonyms_list.size() == 0) {
        throw SyntaxErrorException("Missing synonym");
    }

    extractAndAddToSynonymTable(synonyms_list, dentity_type);
}

// Get synonyms from declaration
void QueryParser::extractAndAddToSynonymTable(std::vector<std::string>& synonymsList, Query::DesignEntityType& dentityType) {
    if (synonymsList.empty()) {
        throw SyntaxErrorException("No synonym found from declaration");
    }
    for (unsigned int i = 0; i < synonymsList.size(); i++) {
        std::string synonym = trim(synonymsList[i]);
        if (!isSynonym(synonym)) {
            throw SyntaxErrorException(synonym + " is not a valid synonym");
        }
        else if (containSynonymName(synonym)) {
            throw SyntaxErrorException("Duplicate found!");
        }
        else {
            //std::cout << "Synonym here is: " + synonym + "\n";
            synonymsTable.insert(std::make_pair(synonym, dentityType));
        }
    }
}

// Method to print synonym table for checking
void QueryParser::printSynonymTable() {
    for (auto index = synonymsTable.begin(); index != synonymsTable.end(); ++index)
    {
        std::cout << "Print the synonym table strings: " << index->first + "\n";
    }
}

// Check if synonym table contains synonym
bool QueryParser::containSynonymName(std::string& synonym) {
    return this->synonymsTable.find(synonym) != synonymsTable.end();
}

Query::DesignEntityType QueryParser::getDesignEntity(std::string& type) {
    if (type == designEntityAssign) {
        return Query::DesignEntityType::ASSIGN;
    }
    else if (type == designEntityStmt) {
        return Query::DesignEntityType::STMT;
    }
    else if (type == designEntityRead) {
        return Query::DesignEntityType::READ;
    }
    else if (type == designEntityCall) {
        return Query::DesignEntityType::CALL;
    }
    else if (type == designEntityPrint) {
        return Query::DesignEntityType::PRINT;
    }
    else if (type == designEntityWhile) {
        return Query::DesignEntityType::WHILE;
    }
    else if (type == designEntityIf) {
        return Query::DesignEntityType::IF;
    }
    else if (type == designEntityVariable) {
        return Query::DesignEntityType::VARIABLE;
    }
    else if (type == designEntityConstant) {
        return Query::DesignEntityType::CONSTANT;
    }
    else if (type == designEntityProcedure) {
        return Query::DesignEntityType::PROCEDURE;
    }
    else if (type == designEntityProgLine) {
        return Query::DesignEntityType::PROG_LINE;
    }
    throw SyntaxErrorException("Invalid design entity type: " + type);
}


Query::DesignAbstractionType QueryParser::getDesignAbstractionType(std::string& type) {
    Query::DesignAbstractionType designAbstractionType;
    type = trim(type);

    if (type == designAbstractFollows) {
        designAbstractionType = Query::DesignAbstractionType::FOLLOWS;
    }
    else if (type == designAbstractFollowsStar) {
        designAbstractionType = Query::DesignAbstractionType::FOLLOWS_STAR;
    }
    else if (type == designAbstractModifies) {
        designAbstractionType = Query::DesignAbstractionType::MODIFIES;
    }
    else if (type == designAbstractParent) {
        designAbstractionType = Query::DesignAbstractionType::PARENT;
    }
    else if (type == designAbstractParentStar) {
        designAbstractionType = Query::DesignAbstractionType::PARENT_STAR;
    }
    else if (type == designAbstractUses) {
        designAbstractionType = Query::DesignAbstractionType::USES;
    }
    else if (type == designAbstractCalls) {
        designAbstractionType = Query::DesignAbstractionType::CALLS;
    }
    else if (type == designAbstractCallsStar) {
        designAbstractionType = Query::DesignAbstractionType::CALLS_STAR;
    }
    else if (type == designAbstractNext) {
        designAbstractionType = Query::DesignAbstractionType::NEXT;
    }
    else if (type == designAbstractNextStar) {
        designAbstractionType = Query::DesignAbstractionType::NEXT_STAR;
    }
    else if (type == designAbstractAffects) {
        designAbstractionType = Query::DesignAbstractionType::AFFECTS;
    }
    else if (type == designAbstractAffectsStar) {
        designAbstractionType = Query::DesignAbstractionType::AFFECTS_STAR;
    }
    else if (type == designAbstractNextBip) {
        designAbstractionType = Query::DesignAbstractionType::NEXTBIP;
    }
    else if (type == designAbstractNextBipStar) {
        designAbstractionType = Query::DesignAbstractionType::NEXTBIP_STAR;
    }
    else if (type == designAbstractAffectsBip) {
        designAbstractionType = Query::DesignAbstractionType::AFFECTSBIP;
    }
    else if (type == designAbstractAffectsBipStar) {
        designAbstractionType = Query::DesignAbstractionType::AFFECTSBIP_STAR;
    }
    else {
        throw SyntaxErrorException(type + "is invalid data abstraction type");
    }

    return designAbstractionType;
}

void QueryParser::parseSelect(std::string& str) {
    startIndex = 0;
    std::string stmt;
    stmt = trim(str);

    if (stmt.at(6) != ' ') {
        throw SyntaxErrorException("Select token not valid");
    }
    if (stmt.back() == ';') {
        throw SyntaxErrorException("Cannot end with ';' for Select Clause");
    }

    std::string keyword = stmt.substr(startIndex, 6);
    endIndex = 6;

    startIndex = endIndex + 1;

    if (keyword != keywordSelect) {
        throw SyntaxErrorException("Expected " + keywordSelect + ", but obtained " + keyword);
    }

    parseSelectedSynonyms(stmt);

    parseClauses(stmt, clauseAnd);
};

std::string QueryParser::getNextToken(std::string& stmt, char delim1, char delim2, bool isLast) {
    startIndex = stmt.find_first_not_of(delim1, startIndex);
    unsigned int delimIndex = stmt.find_first_of(delim2, startIndex);

    if (delimIndex >= stmt.size()) {
        if (isLast) {
            delimIndex = stmt.size();
        }
        else {
            throw SyntaxErrorException("Stmt is not complete");
        }
    }
    int tempStartIndex = startIndex;
    startIndex = delimIndex + 1;
    return stmt.substr(tempStartIndex, delimIndex - tempStartIndex);
}

std::string QueryParser::getExpression(std::string& stmt) {
    startIndex = stmt.find_first_not_of(' ', startIndex);
    int delimIndex;
    int tempStartIndex;

    int numberOfOpenParentheses = 1;
    for (size_t index = startIndex; index < stmt.length(); ++index) {
        if (stmt[index] == '(') {
            numberOfOpenParentheses++;
        }
        else if (stmt[index] == ')') {
            if (numberOfOpenParentheses == 1) {
                delimIndex = index;
                tempStartIndex = startIndex;
                startIndex = delimIndex + 1;
                return stmt.substr(tempStartIndex, delimIndex - tempStartIndex);
            }
            numberOfOpenParentheses--;
        }
    }
    if (numberOfOpenParentheses != 0) {
        throw SyntaxErrorException("Stmt is not complete");
    }
    delimIndex = stmt.size();
    tempStartIndex = startIndex;
    startIndex = delimIndex + 1;
    return stmt.substr(tempStartIndex, delimIndex - tempStartIndex);
}

void QueryParser::parseSelectedSynonyms(std::string& stmt) {
    // if its not a tuple
    if (stmt.find_first_of("<", startIndex) == std::string::npos) {
        std::string synonym = getNextToken(stmt, ' ', ' ', true);
        synonym = trim(synonym);
        if (synonym == "BOOLEAN") {
            isSelectBoolean = true;
        }
        else {
            Query::Element synonymAndAttribute = getSynonymAndAttributes(synonym);
            selectedSynonyms.push_back(synonymAndAttribute);
        }
    }
    else {
        // if its a tuple, trim and handle it
        std::string tuple = getNextToken(stmt, ' ', '>', false);
        tuple = trim(tuple);

        if (tuple[0] != '<' || tuple.size() <= 1) {
            throw SyntaxErrorException("Tuple is invalid");
        }
        // remove '<' from string
        tuple = tuple.substr(1, tuple.size() - 1);
        std::vector<std::string> synonyms = splitSynonym(tuple, ',');
        if (synonyms.size() == 0) {
            throw SyntaxErrorException("Empty tuple");
        }
        for (unsigned int i = 0; i < synonyms.size(); i++) {
            Query::Element synonymAndAttribute = getSynonymAndAttributes(synonyms[i]);
            selectedSynonyms.push_back(synonymAndAttribute);
        }
        startIndex = stmt.find_first_not_of(" ", startIndex);
    }
}

Query::Element QueryParser::getSynonymAndAttributes(std::string& string) {
    Query::Element element;
    string = trim(string);

    // if there is no ".", its just a single synonym
    if (string.find_first_of(".", 0) == std::string::npos) {
        if (!containSynonymName(string)) {
            throw SyntaxErrorException("Selected synonym is not declared");
        }

        element.synonymString = string;
        element.elementAttribType = Query::ReferenceAttributeType::NONE;
        element.elementType = Query::ElementType::SYNONYM;
        return element;
    }
    else {
        unsigned int delimiterIndex = string.find_first_of(".", 0);

        std::string synonym = string.substr(0, delimiterIndex);
        synonym = trim(synonym);

        std::string attribute = string.substr(delimiterIndex + 1, string.size() - delimiterIndex - 1);

        // check if synonym is declared
        if (!containSynonymName(synonym)) {
            throw SyntaxErrorException("Selected synonym is not declared");
        }

        Query::ReferenceAttributeType attributeType = getReferenceAttributeType(attribute);
        Query::DesignEntityType designEntityType = getDesignEntityTypeFromTable(synonym);

        // validation of attribute and synonym relationship
        if (!isValidSynonymAndAttribute(attributeType, designEntityType)) {
            throw SemanticErrorException("Invalid Synonym and Attribute rs");
        }

        element.elementType = Query::ElementType::ATTRIBUTE;
        element.elementAttribType = attributeType;
        element.synonymString = synonym;
        return element;
    }
}

bool QueryParser::isValidSynonymAndAttribute(Query::ReferenceAttributeType attributeType, Query::DesignEntityType designEntityType) {
    switch (attributeType) {
    case Query::ReferenceAttributeType::PROCNAME:
        if ((designEntityType == Query::DesignEntityType::PROCEDURE) ||
            (designEntityType == Query::DesignEntityType::CALL)) {
            return true;
        }
        break;
    case Query::ReferenceAttributeType::STMTNUM:
        if ((designEntityType == Query::DesignEntityType::ASSIGN) ||
            (designEntityType == Query::DesignEntityType::STMT) ||
            (designEntityType == Query::DesignEntityType::CALL) ||
            (designEntityType == Query::DesignEntityType::IF) ||
            (designEntityType == Query::DesignEntityType::PRINT) ||
            (designEntityType == Query::DesignEntityType::WHILE) ||
            (designEntityType == Query::DesignEntityType::READ)) {
            return true;
        }
        break;
    case Query::ReferenceAttributeType::VALUE:
        if (designEntityType == Query::DesignEntityType::CONSTANT) {
            return true;
        }
        break;
    case Query::ReferenceAttributeType::VARNAME:
        if ((designEntityType == Query::DesignEntityType::VARIABLE) ||
            (designEntityType == Query::DesignEntityType::READ) ||
            (designEntityType == Query::DesignEntityType::PRINT)) {
            return true;
        }
        break;
    case Query::ReferenceAttributeType::NONE:
        return true;
        break;
    default:
        throw SemanticErrorException("Missing ref attribute type");
    }
    return false;
};

Query::ReferenceAttributeType QueryParser::getReferenceAttributeType(std::string& ref) {
    ref = trim(ref);

    if (ref == attributeProcName) {
        return Query::ReferenceAttributeType::PROCNAME;
    }
    else if (ref == attributeVarName) {
        return Query::ReferenceAttributeType::VARNAME;
    }
    else if (ref == attributeValue) {
        return Query::ReferenceAttributeType::VALUE;
    }
    else if (ref == attributeStmt) {
        return Query::ReferenceAttributeType::STMTNUM;
    }
    else {
        throw SyntaxErrorException(ref + " is not a valid reference attribute type");
    }
}


void QueryParser::parseClauses(std::string& stmt, std::string prevClauseType) {
    if (startIndex >= stmt.size()) {
        return;
    }
    std::string keyword = getNextToken(stmt, ' ', ' ', false);
    keyword = trim(keyword);

    if (keyword == clauseAnd) {
        if (prevClauseType == clauseSuch) {
            parseSuchThatClause(stmt);
        }
        else {
            if (prevClauseType == clausePattern) {
                parsePatternClause(stmt);
            }
            else if (prevClauseType == clauseWith) {
                parseWithClause(stmt);
            }
            else {
                throw SyntaxErrorException(keyword + " is not a valid clause");
            }
        }
    }
    else {
        if (keyword == clauseSuch) {
            std::string clauseKeyword = getNextToken(stmt, ' ', ' ', false);
            clauseKeyword = trim(clauseKeyword);
            if (clauseKeyword == clauseThat) {
                parseSuchThatClause(stmt);
            }
            else {
                throw SyntaxErrorException("Invalid such that clause");
            }
        }
        else if (keyword == clausePattern) {
            parsePatternClause(stmt);
        }
        else if (keyword == clauseWith) {
            parseWithClause(stmt);
        }
        else {
            throw SyntaxErrorException(keyword + " is not a valid clause");
        }
    }
}

void QueryParser::parseWithClause(std::string& stmt) {
    Query::Clause clause;
    clause.clauseType = Query::ClauseType::WITH;

    std::string leftRef = getNextToken(stmt, ' ', '=', false);
    leftRef = trim(leftRef);
    parseWithRef(clause.leftRef, leftRef);

    std::string rightRef = getNextToken(stmt, ' ', ' ', true);
    parseWithRef(clause.rightRef, rightRef);

    validateWithReferences(clause);
    clauses.push_back(clause);
    parseClauses(stmt, clauseWith);
}

void QueryParser::validateWithReferences(Query::Clause& clause) {
    if ((clause.leftRef.refDentityType == Query::DesignEntityType::PROG_LINE &&
        clause.leftRef.refAttribType != Query::ReferenceAttributeType::NONE) ||
        (clause.rightRef.refDentityType == Query::DesignEntityType::PROG_LINE &&
            clause.rightRef.refAttribType != Query::ReferenceAttributeType::NONE)) {
        throw SemanticErrorException(
            "Prog_line Design Entity cannot have attribute");
    }

    QueryParser::DataType leftRefDataType = getDataType(clause.leftRef.refType, clause.leftRef.refAttribType);
    QueryParser::DataType rightRefDataType = getDataType(clause.rightRef.refType, clause.rightRef.refAttribType);

    // check data type for both sides
    if (leftRefDataType != rightRefDataType) {
        throw SemanticErrorException("The refs are not of the same data type");
    }
};


QueryParser::DataType QueryParser::getDataType(Query::ReferenceType refType, Query::ReferenceAttributeType attribType) {
    if (refType == Query::ReferenceType::QUOTATION) {
        return DataType::NAME;
    }
    else if (refType == Query::ReferenceType::INTEGER) {
        return DataType::NUMBER;
    }
    else if (refType == Query::ReferenceType::SYNONYM || refType == Query::ReferenceType::ATTRIBUTE) {
        if (attribType == Query::ReferenceAttributeType::NONE ||
            attribType == Query::ReferenceAttributeType::VALUE ||
            attribType == Query::ReferenceAttributeType::STMTNUM)
        {
            return DataType::NUMBER;
        }
        else if (attribType == Query::ReferenceAttributeType::PROCNAME ||
            attribType == Query::ReferenceAttributeType::VARNAME) {
            return DataType::NAME;
        }
        else {
            throw SemanticErrorException("Invalid Design Entity type");
        }
    }
    else {
        throw SyntaxErrorException("Invalid Reference type");
    }
};

void QueryParser::parseWithRef(Query::Reference& clauseRef, std::string& ref) {
    // it has "."
    clauseRef.refAttribType = Query::ReferenceAttributeType::NONE;

    if (ref.find_first_of(".", 0) != std::string::npos) {
        Query::Element element = getSynonymAndAttributes(ref);
        clauseRef.refDentityType = getDesignEntityTypeFromTable(element.synonymString);
        clauseRef.refAttribType = element.elementAttribType;
        clauseRef.refType = Query::ReferenceType::ATTRIBUTE;
        clauseRef.synonym = element.synonymString;
        clauseRef.refString = ref;
    }
    // dont have ".", ifs either "" | INTEGER | attrRef | synonym
    else {
        clauseRef = getReference(ref);
        clauseRef.refAttribType = Query::ReferenceAttributeType::NONE;
        if (clauseRef.refType == Query::ReferenceType::WILDCARD) {
            throw SemanticErrorException("Invalid ref for with clause");
        }
    }
}

void QueryParser::parseSuchThatClause(std::string& stmt) {
    std::string designAbstractStr = getNextToken(stmt, ' ', '(', false);
    Query::DesignAbstractionType designAbstractType = getDesignAbstractionType(designAbstractStr);
    std::string firstRef = getNextToken(stmt, ' ', ',', false);
    std::string secondRef = getNextToken(stmt, ' ', ')', false);

    // Create such that clause and initialize clause
    Query::Clause clause;
    firstRef = trim(firstRef);
    secondRef = trim(secondRef);

    Query::Reference leftRef = getReference(firstRef);
    Query::Reference rightRef = getReference(secondRef);

    clause.designAbstractionType = designAbstractType;
    clause.leftRef = leftRef;
    clause.rightRef = rightRef;
    createClause(clause, Query::ClauseType::SUCH_THAT);

    if (!isValidDesignAbstractReference(designAbstractType, leftRef, rightRef)) {
        throw SemanticErrorException("Invalid Design Abstraction");
    }
    clauses.push_back(clause);
    parseClauses(stmt, clauseSuch);
}

// Get reference and assign reference type and dentity type to reference
Query::Reference QueryParser::getReference(std::string& ref) {
    Query::Reference reference;
    ref = trim(ref);

    if (ref.size() == 0) {
        throw SyntaxErrorException("Empty reference");
    }
    if (ref == "_") {
        reference.refType = Query::ReferenceType::WILDCARD;
        reference.refAttribType = Query::ReferenceAttributeType::NONE;
        reference.refDentityType = Query::DesignEntityType::WILDCARD;
        reference.refString = ref;
    }
    else if (isInteger(ref)) {
        reference.refType = Query::ReferenceType::INTEGER;
        reference.refDentityType = Query::DesignEntityType::STMT;
        reference.refString = ref;
    }
    else if (containSynonymName(ref)) {
        reference.refType = Query::ReferenceType::SYNONYM;
        reference.refDentityType = getDesignEntityTypeFromTable(ref);
        reference.refString = ref;
    }
    else if (ref[0] == '"' && ref[ref.size() - 1] == '"'
        && ref.size() > 2 && (isSynonym(ref.substr(1, ref.size() - 2)))) {
        reference.refType = Query::ReferenceType::QUOTATION;
        reference.refAttribType = Query::ReferenceAttributeType::NONE;
        reference.refDentityType = Query::DesignEntityType::NONE;
        reference.refString = ref.substr(1, ref.size() - 2);
    }
    else {
        throw SyntaxErrorException(ref + " is not a valid reference");
    }
    return reference;
}

Query::DesignEntityType QueryParser::getDesignEntityTypeFromTable(std::string& ref) {
    std::unordered_map<std::string, Query::DesignEntityType>::const_iterator table_iterator = synonymsTable.find(ref);

    if (table_iterator != synonymsTable.end()) {
        //std::cout << "Found " << ref << "\n\n";
        return table_iterator->second;
    }
    else {
        //std::cout << ref << " not found\n\n";
        return Query::DesignEntityType::NONE;
    }
}

bool QueryParser::isValidDesignAbstractReference(Query::DesignAbstractionType designAbstractType,
    Query::Reference leftRef, Query::Reference rightRef) {

    switch (designAbstractType) {
    case Query::DesignAbstractionType::CALLS:
    case Query::DesignAbstractionType::CALLS_STAR:
        if ((leftRef.refDentityType == Query::DesignEntityType::PROCEDURE ||
            leftRef.refDentityType == Query::DesignEntityType::WILDCARD ||
            leftRef.refDentityType == Query::DesignEntityType::NONE) &&
            (rightRef.refDentityType == Query::DesignEntityType::PROCEDURE) ||
            (rightRef.refDentityType == Query::DesignEntityType::WILDCARD) ||
            (rightRef.refDentityType == Query::DesignEntityType::NONE)) {
            return true;
        }
        break;
    case Query::DesignAbstractionType::FOLLOWS:
    case Query::DesignAbstractionType::FOLLOWS_STAR:
    case Query::DesignAbstractionType::NEXT:
    case Query::DesignAbstractionType::NEXT_STAR:
    case Query::DesignAbstractionType::NEXTBIP:
    case Query::DesignAbstractionType::NEXTBIP_STAR:
    case Query::DesignAbstractionType::PARENT:
    case Query::DesignAbstractionType::PARENT_STAR:
        if (leftRef.refDentityType != Query::DesignEntityType::CONSTANT &&
            leftRef.refDentityType != Query::DesignEntityType::PROCEDURE &&
            leftRef.refDentityType != Query::DesignEntityType::VARIABLE &&
            rightRef.refDentityType != Query::DesignEntityType::CONSTANT &&
            rightRef.refDentityType != Query::DesignEntityType::PROCEDURE &&
            rightRef.refDentityType != Query::DesignEntityType::VARIABLE) {
            return true;
        }
        break;
    case Query::DesignAbstractionType::MODIFIES:
    case Query::DesignAbstractionType::USES:
        if ((leftRef.refDentityType != Query::DesignEntityType::WILDCARD) &&
            (leftRef.refDentityType != Query::DesignEntityType::VARIABLE) &&
            (leftRef.refDentityType != Query::DesignEntityType::CONSTANT) &&
            (rightRef.refDentityType == Query::DesignEntityType::VARIABLE ||
                rightRef.refDentityType == Query::DesignEntityType::WILDCARD ||
                rightRef.refDentityType == Query::DesignEntityType::NONE)) {
            return true;
        }
        break;
    case Query::DesignAbstractionType::AFFECTS:
    case Query::DesignAbstractionType::AFFECTS_STAR:
    case Query::DesignAbstractionType::AFFECTSBIP:
    case Query::DesignAbstractionType::AFFECTSBIP_STAR:
        if (((leftRef.refDentityType == Query::DesignEntityType::WILDCARD) ||
            (leftRef.refDentityType == Query::DesignEntityType::ASSIGN) || 
            (leftRef.refDentityType == Query::DesignEntityType::STMT) ||
            (leftRef.refDentityType == Query::DesignEntityType::PROG_LINE)) &&
            ((rightRef.refDentityType == Query::DesignEntityType::WILDCARD) ||
            (rightRef.refDentityType == Query::DesignEntityType::ASSIGN) ||
            (rightRef.refDentityType == Query::DesignEntityType::STMT) ||
            (rightRef.refDentityType == Query::DesignEntityType::PROG_LINE))) {
            return true;
        }
        break;
    default:
        throw SyntaxErrorException("Not valid design abstraction ref");
    }
    return false;
}

void QueryParser::createClause(Query::Clause& clause, Query::ClauseType clauseType) {
    clause.clauseType = clauseType;
}

void QueryParser::parsePatternClause(std::string& stmt) {
    Query::Clause clause;
    createClause(clause, Query::ClauseType::PATTERN);

    std::string patternSynonym = getNextToken(stmt, ' ', '(', false);

    stmt = trim(stmt);
    clause.leftRef = getReference(patternSynonym);

    std::string entRef = getNextToken(stmt, ' ', ',', false);
    entRef = trim(entRef);
    clause.rightRef = getReference(entRef);

    // check entRef
    if (clause.rightRef.refType == Query::ReferenceType::INTEGER) {
        throw SemanticErrorException("Invalid left input for pattern clause");
    }
    else if (clause.rightRef.refType == Query::ReferenceType::SYNONYM && getDesignEntityTypeFromTable(entRef) != Query::DesignEntityType::VARIABLE) {
        throw SemanticErrorException("Invalid left input design entity");
    }

    // call respective pattern clauses
    if (synonymsTable.count(patternSynonym) != 0) {
        if (synonymsTable.at(patternSynonym) == Query::DesignEntityType::ASSIGN) {
            clause.patternAbstractionType = Query::PatternAbstractionType::ASSIGN;
            parsePatternAssignClause(clause, stmt, entRef);
        }
        else if (synonymsTable.at(patternSynonym) == Query::DesignEntityType::WHILE) {
            clause.patternAbstractionType = Query::PatternAbstractionType::WHILE;
            parsePatternWhileClause(clause, stmt);
        }
        else if (synonymsTable.at(patternSynonym) == Query::DesignEntityType::IF) {
            clause.patternAbstractionType = Query::PatternAbstractionType::IF;
            parsePatternIfClause(clause, stmt);
        }
        else {
            throw SemanticErrorException(patternSynonym + " is an invalid synonym type for expression");
        }
    }
    else {
        throw SyntaxErrorException(patternSynonym + " is not declared");
    }

    clauses.push_back(clause);

    parseClauses(stmt, clausePattern);
}

void QueryParser::parsePatternAssignClause(Query::Clause& clause, std::string& stmt, std::string& entRef) {
    stmt = trim(stmt);

    std::string exprString = getExpression(stmt);

    assignExpressionTypeToClause(clause, exprString);
    validatePatternClauseReference(entRef, exprString);
};

void QueryParser::parsePatternIfClause(Query::Clause& clause, std::string& stmt) {
    stmt = trim(stmt);
    std::string firstRef = getNextToken(stmt, ' ', ',', false);
    firstRef = trim(firstRef);
    if (firstRef != "_") {
        throw SemanticErrorException("Invalid If clause reference");
    }

    std::string secondRef = getNextToken(stmt, ' ', ')', false);
    secondRef = trim(secondRef);
    if (secondRef != "_") {
        throw SemanticErrorException("Invalid If clause reference");
    }
};

void QueryParser::parsePatternWhileClause(Query::Clause& clause, std::string& stmt) {
    std::string nextToken = getNextToken(stmt, ' ', ')', false);
    nextToken = trim(nextToken);
    if (nextToken != "_") {
        throw SemanticErrorException("Invalid While clause reference");
    }
};

// Assign Pattern Abstraction type and expression type to expression in clause
void QueryParser::assignExpressionTypeToClause(Query::Clause& clause, std::string& expr) {
    clause.expr.exprString = expr;

    if (expr == "_") {
        clause.expr.exprType = Query::ExpressionType::NO_MATCH;
    }
    else if (expr.front() == '_' && expr.back() == '_') {
        clause.expr.exprType = Query::ExpressionType::PARTIAL_MATCH;
    }
    else if (expr.front() == '\"' && expr.back() == '\"') {
        clause.expr.exprType = Query::ExpressionType::EXACT_MATCH;
    }
};


void QueryParser::validateQuotes(std::string target, std::string errorString) {
    int quote_num = std::count(target.begin(), target.end(), '\"');
    if (target.size() > 1) {
        // There should be either 2 quotes or 0 quotes
        if (quote_num == 2) {
            // If there are 2 quotes, it must be either front and back, or front and back ignoring underscores
            if (!((target[0] == '\"' && target.end()[-1] == '\"') || (target[1] == '\"' && target.end()[-2] == '\"'))) {
                throw SemanticErrorException(errorString);
            }
        }
        else {
            // If not 2 quotes, then must be 0 or throw error
            if (quote_num != 0) {
                throw SemanticErrorException(errorString);
            }
        }
    }
}

std::vector<std::string> QueryParser::tokenizeExpression(std::string expression) {
    int expressionLength = expression.length();
    std::string token;
    std::vector<std::string> tokens;
    for (int i = 0; i < expressionLength; ++i) {
        if (ispunct(expression[i])) {
            if (token.length() != 0) {
                tokens.push_back(token);
                token = "";
            }
            std::string stringToken(1, expression[i]);
            tokens.push_back(stringToken);
        }
        else {
            token += expression[i];
            if (i == expressionLength - 1) {
                tokens.push_back(token);
            }
        }
    }
    return tokens;
}

void QueryParser::validateExpression(std::vector<std::string> tokens, std::string errorString) {
    std::unordered_set<std::string> operators = { "+", "-", "*", "/", "%" };
    int numberOfOpenParentheses = 0;
    bool emptyExpression = true;
    bool lastWasVariable = false;
    bool lastWasOperator = false;
    bool lastWasOpenParenthesis = false;
    bool lastWasCloseParenthesis = false;
    for (unsigned int index = 0; index < tokens.size(); ++index) {
        std::string token = tokens[index];
        if (token == "(") {
            if (lastWasCloseParenthesis || lastWasVariable) {
                throw SemanticErrorException(errorString);
            }
            numberOfOpenParentheses++;
            emptyExpression = false;
            lastWasOperator = false;
            lastWasVariable = false;
            lastWasOpenParenthesis = true;
            lastWasCloseParenthesis = false;
        }
        else if (token == ")") {
            if (numberOfOpenParentheses <= 0 || lastWasOperator || lastWasOpenParenthesis || emptyExpression) {
                throw SemanticErrorException(errorString);
            }
            emptyExpression = false;
            lastWasOperator = false;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = true;
            numberOfOpenParentheses--;
        }
        else if (operators.find(token) != operators.end()) {
            if (lastWasOperator || lastWasOpenParenthesis || emptyExpression) {
                throw SemanticErrorException(errorString);
            }
            emptyExpression = false;
            lastWasOperator = true;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
        }
        else if (isSynonym(token) || isInteger(token)) {
            if (lastWasVariable || lastWasCloseParenthesis) {
                throw SemanticErrorException(errorString);
            }
            emptyExpression = false;
            lastWasOperator = false;
            lastWasVariable = true;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
        }
        else {
            // Unexpected token
            throw SemanticErrorException(errorString);
        }
        if (index == tokens.size() - 1) {
            // It shouldn't end with an open parenthesis left unclosed, an operator or an open parenthesis
            if (numberOfOpenParentheses != 0 || lastWasOperator || lastWasOpenParenthesis) {
                throw SemanticErrorException(errorString);
            }
        }
    }
}

void QueryParser::validatePatternClauseReference(std::string& leftRef, std::string& rightRef) {

    std::string firstError = leftRef + " is not a valid LHS!";
    if (leftRef.size() > 1) {
        QueryParser::validateQuotes(leftRef, firstError);
    }
    else {
        if (!(isalpha(leftRef[0]) || leftRef == "_")) {
            throw SemanticErrorException(firstError);
        }
    }

    std::string secondError = rightRef + " is not a valid RHS!";
    int secondUnderscoreNum = std::count(rightRef.begin(), rightRef.end(), '_');

    if (rightRef.size() > 1) {
        if (secondUnderscoreNum != 2 && secondUnderscoreNum != 0) {
            throw SemanticErrorException(secondError);
        }
        else {
            if (rightRef.front() == '_') {
                if (rightRef.back() != '_') {
                    throw SemanticErrorException(secondError);
                }
                else {
                    // Cannot have __
                    if (rightRef.size() == 2) {
                        throw SemanticErrorException(secondError);
                    }
                }
            }
            QueryParser::validateQuotes(rightRef, secondError);
            std::string trimmedExpr = "";
            for (auto element : rightRef) {
                if (!isspace(element) && element != '_' && element != '\"') {
                    trimmedExpr += element;
                }
            }

            if (trimmedExpr.empty()) {
                throw SemanticErrorException(secondError);
            }

            QueryParser::validateExpression(tokenizeExpression(trimmedExpr), secondError);
        }
    }
    // if RHS is size 1, it must be an underscore or throw error
    else {
        if (rightRef != "_") {
            throw SemanticErrorException(secondError);
        }
    }
}

// Split query by delimiter
std::vector<std::string> QueryParser::splitQuery(std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    unsigned int startingIndex = 0;
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == delimiter && i == str.size() - 1) {
            throw SyntaxErrorException("Select Clause cannot end with ';' ");
        }
        else if (str[i] == delimiter && startingIndex < i) {
            tokens.push_back(str.substr(startingIndex, i - startingIndex));
            startingIndex = i + 1;
        }
        else if (i == str.size() - 1) {
            if (startingIndex <= i) {
                tokens.push_back(str.substr(startingIndex, i - startingIndex + 1));
            }
        }
    }
    return tokens;
}

// Split synonym by delimiter
std::vector<std::string> QueryParser::splitSynonym(std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    unsigned int startingIndex = 0;
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == delimiter && startingIndex < i) {
            tokens.push_back(str.substr(startingIndex, i - startingIndex));
            startingIndex = i + 1;
        }
        else if (i == str.size() - 1) {
            if (startingIndex <= i) {
                tokens.push_back(str.substr(startingIndex, i - startingIndex + 1));
            }
        }
    }
    return tokens;
}

// Trim leading and trailing spaces
std::string QueryParser::trim(std::string& str) {
    unsigned int i = 0;
    unsigned int len = str.size();
    std::string result_;

    while (i < len && (isspace(str[i]) || str[i] <= ' ')) {
        i++;
    }

    while ((i < len) && (isspace(str[len - 1]) || str[len - 1] <= ' ')) {
        len--;
    }

    if (i > 0 || len < str.size()) {
        result_ = str.substr(i, len - i);
        return result_;
    }
    else {
        return str;
    }
}

bool QueryParser::isInteger(std::string& str) {
    if (str.at(0) == '0' && str.size() > 1) {
        return false;
    }
    for (unsigned int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool QueryParser::isSynonym(std::string str) {
    std::string curr = trim(str);

    if (str.size() == 0 || !isalpha(str[0])) {
        return false;
    }

    for (unsigned int i = 1; i < str.size(); i++) {
        if (!isalpha(curr[i]) && !isdigit(curr[i])) {
            return false;
        }
    }
    return true;
}
