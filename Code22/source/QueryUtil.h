#pragma once

#include <iostream>

#include "QueryPreprocessor/Query.h"

//Debugging purposes. Delete it near submission?
class QueryUtil {
public:
    static void printClauseType(Query::ClauseType clauseType) {
        switch (clauseType) {
        case Query::ClauseType::NONE:
            std::cout << "        NONE" << std::endl;
            break;
        case Query::ClauseType::PATTERN:
            std::cout << "        PATTERN" << std::endl;
            break;
        case Query::ClauseType::SELECT:
            std::cout << "        SELECT" << std::endl;
            break;
        case Query::ClauseType::SUCH_THAT:
            std::cout << "        SUCH_THAT" << std::endl;
            break;
        case Query::ClauseType::WITH:
            std::cout << "        WITH" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printDesignEntityType(Query::DesignEntityType designEntityType) {
        switch (designEntityType) {
        case Query::DesignEntityType::ASSIGN:
            std::cout << "        ASSIGN" << std::endl;
            break;
        case Query::DesignEntityType::CALL:
            std::cout << "        CALL" << std::endl;
            break;
        case Query::DesignEntityType::CONSTANT:
            std::cout << "        CONSTANT" << std::endl;
            break;
        case Query::DesignEntityType::IF:
            std::cout << "        IF" << std::endl;
            break;
        case Query::DesignEntityType::NONE:
            std::cout << "        NONE" << std::endl;
            break;
        case Query::DesignEntityType::PRINT:
            std::cout << "        PRINT" << std::endl;
            break;
        case Query::DesignEntityType::PROCEDURE:
            std::cout << "        PROCEDURE" << std::endl;
            break;
        case Query::DesignEntityType::PROG_LINE:
            std::cout << "        PROG_LINE" << std::endl;
            break;
        case Query::DesignEntityType::READ:
            std::cout << "        READ" << std::endl;
            break;
        case Query::DesignEntityType::STMT:
            std::cout << "        STMT" << std::endl;
            break;
        case Query::DesignEntityType::VARIABLE:
            std::cout << "        VARIABLE" << std::endl;
            break;
        case Query::DesignEntityType::WHILE:
            std::cout << "        WHILE" << std::endl;
            break;
        case Query::DesignEntityType::WILDCARD:
            std::cout << "        WILDCARD" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printDesignAbstractionType(Query::DesignAbstractionType designAbstractionType) {
        switch (designAbstractionType) {
        case Query::DesignAbstractionType::CALLS:
            std::cout << "        CALLS" << std::endl;
            break;
        case Query::DesignAbstractionType::CALLS_STAR:
            std::cout << "        CALLS_STAR" << std::endl;
            break;
        case Query::DesignAbstractionType::FOLLOWS:
            std::cout << "        FOLLOWS" << std::endl;
            break;
        case Query::DesignAbstractionType::FOLLOWS_STAR:
            std::cout << "        FOLLOWS_STAR" << std::endl;
            break;
        case Query::DesignAbstractionType::MODIFIES:
            std::cout << "        MODIFIES" << std::endl;
            break;
        case Query::DesignAbstractionType::NEXT:
            std::cout << "        NEXT" << std::endl;
            break;
        case Query::DesignAbstractionType::NEXT_STAR:
            std::cout << "        NEXT_STAR" << std::endl;
            break;
        case Query::DesignAbstractionType::PARENT:
            std::cout << "        PARENT" << std::endl;
            break;
        case Query::DesignAbstractionType::PARENT_STAR:
            std::cout << "        PARENT_STAR" << std::endl;
            break;
        case Query::DesignAbstractionType::USES:
            std::cout << "        USES" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printReferenceAttributeType(Query::ReferenceAttributeType referenceAttribType) {
        switch (referenceAttribType) {
        case Query::ReferenceAttributeType::NONE:
            std::cout << "        NONE" << std::endl;
            break;
        case Query::ReferenceAttributeType::PROCNAME:
            std::cout << "        PROCNAME" << std::endl;
            break;
        case Query::ReferenceAttributeType::VARNAME:
            std::cout << "        VARNAME" << std::endl;
            break;
        case Query::ReferenceAttributeType::VALUE:
            std::cout << "        VALUE" << std::endl;
            break;
        case Query::ReferenceAttributeType::STMTNUM:
            std::cout << "        STMTNUM" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printReferenceType(Query::ReferenceType referenceType) {
        switch (referenceType) {
        case Query::ReferenceType::SYNONYM:
            std::cout << "        SYNONYM" << std::endl;
            break;
        case Query::ReferenceType::INTEGER:
            std::cout << "        INTEGER" << std::endl;
            break;
        case Query::ReferenceType::WILDCARD:
            std::cout << "        WILDCARD" << std::endl;
            break;
        case Query::ReferenceType::QUOTATION:
            std::cout << "        QUOTATION" << std::endl;
            break;
        case Query::ReferenceType::ATTRIBUTE:
            std::cout << "        ATTRIBUTE" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printReference(Query::Reference reference) {
        std::cout << "    refDentityType" << std::endl;
        printDesignEntityType(reference.refDentityType);

        std::cout << "    refAttribType" << std::endl;
        printReferenceAttributeType(reference.refAttribType);

        std::cout << "    refType" << std::endl;
        printReferenceType(reference.refType);

        std::cout << "    refString" << std::endl;
        std::cout << "        " << reference.refString << std::endl;

        std::cout << "    synonym" << std::endl;
        std::cout << "        " << reference.synonym << std::endl;
    }

    static void printPatternAbstractionType(Query::PatternAbstractionType patternAbstractionType) {
        switch (patternAbstractionType) {
        case Query::PatternAbstractionType::ASSIGN:
            std::cout << "        ASSIGN" << std::endl;
            break;
        case Query::PatternAbstractionType::IF:
            std::cout << "        IF" << std::endl;
            break;
        case Query::PatternAbstractionType::WHILE:
            std::cout << "        WHILE" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printExpressionType(Query::ExpressionType exprType) {
        switch (exprType) {
        case Query::ExpressionType::PARTIAL_MATCH:
            std::cout << "        PARTIAL_MATCH" << std::endl;
            break;
        case Query::ExpressionType::EXACT_MATCH:
            std::cout << "        EXACT_MATCH" << std::endl;
            break;
        case Query::ExpressionType::NO_MATCH:
            std::cout << "        NO_MATCH" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printExpression(Query::Expression expr) {
        std::cout << "    exprType" << std::endl;
        printExpressionType(expr.exprType);
        
        std::cout << "    exprString" << std::endl;
        std::cout << "        " << expr.exprString << std::endl;
    }

    static void printClause(Query::Clause clause) {
        std::cout << "clauseType" << std::endl;
        printClauseType(clause.clauseType);

        std::cout << "designAbstractionType" << std::endl;
        printDesignAbstractionType(clause.designAbstractionType);

        std::cout << "leftRef" << std::endl;
        printReference(clause.leftRef);

        std::cout << "rightRef" << std::endl;
        printReference(clause.rightRef);

        std::cout << "patternAbstractionType" << std::endl;
        printPatternAbstractionType(clause.patternAbstractionType);

        std::cout << "expr" << std::endl;
        printExpression(clause.expr);
    }

    static void printElementType(Query::ElementType elementType) {
        switch (elementType) {
        case Query::ElementType::SYNONYM:
            std::cout << "        SYNONYM" << std::endl;
            break;
        case Query::ElementType::ATTRIBUTE:
            std::cout << "        ATTRIBUTE" << std::endl;
            break;
        default:
            std::cout << "        ERROR" << std::endl;
        }
    }

    static void printElement(Query::Element element) {
        std::cout << "    elementType" << std::endl;
        printElementType(element.elementType);

        std::cout << "    elementAttribType" << std::endl;
        printReferenceAttributeType(element.elementAttribType);

        std::cout << "    synonymString" << std::endl;
        std::cout << "        " << element.synonymString << std::endl;
    }
};

