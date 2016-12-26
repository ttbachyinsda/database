//
// Created by jameshuang on 16-12-23.
//

#include "checkhelper.h"
#include "querycondition.h"

const int CheckHelper::choiceCode = 100;

bool CheckHelper::addCheckCondition(const vector<string> &clname,
                                    const vector<DataBaseType *> &ctypes, Table *tbl,
                                    SQLCheckGroup *checkGroup) {
    // Add constraints (conditions) to table
    for (SQLCheck* c : *checkGroup) {
        int colID = -1;
        for (unsigned dbi = 0; dbi < clname.size(); ++ dbi) {
            if (clname[dbi] == c->selector->tableName) {
                colID = (int) dbi;
                break;
            }
        }
        if (colID == -1) return false;

        char foundDBTypeStr = ctypes[colID]->getType()[6];
        if (c->isChoice) {
            string choiceStr;
            for (SQLValue* sqc : *c->choiceList) {
                if (!QueryCondition::typeComparable(sqc->type, foundDBTypeStr)) {
                    return false;
                }
                choiceStr += ((char)'\"' + sqc->content);
            }
            choiceStr = choiceStr.substr(1);
            tbl->gettablecondition()->push_back(make_triple(colID, choiceCode, choiceStr));
            continue;
        }
        // Judge Literal values.
        if (c->value.type == SQLValue::LiteralType::NUL ||
                !QueryCondition::typeComparable(c->value.type, foundDBTypeStr)) {
            return false;
        }
        tbl->gettablecondition()->push_back(make_triple(colID, c->operand, c->value.content));
    }
    return true;
}

bool CheckHelper::satisfy(Table *tbl, SQLValueGroup *const valueVecPtr,
                          const vector<vector<string> >& choiceListCache) {
    for (auto iter = tbl->gettablecondition()->begin();
         iter != tbl->gettablecondition()->end(); ++ iter) {
        char thisCondDataType = tbl->getcolumns()[iter->first]->getType()[6];
        SQLValue* thisCondValue = valueVecPtr->at(iter->first);
        if (iter->second.first == choiceCode) {
            const vector<string>& cache = choiceListCache[iter->first];
            bool match = false;
            for (const string & s : cache) {
                if (QueryCondition::match(SQLOperand::EQUAL,
                                          thisCondDataType,
                                          thisCondValue->content,
                                          thisCondValue->type == SQLValue::LiteralType::NUL,
                                          s, s.size() == 0)) {
                    match = true;
                    break;
                }
            }
            if (!match) return false;
        } else {
            bool thisCondMatch = QueryCondition::match((SQLOperand) iter->second.first,
                                                       thisCondDataType,
                                                       thisCondValue->content,
                                                       thisCondValue->type == SQLValue::LiteralType::NUL,
                                                       iter->second.second,
                                                       iter->second.second.size() == 0);
            if (!thisCondMatch) return false;
        }
    }
    return true;
}
