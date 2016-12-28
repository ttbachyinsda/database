//
// Created by jameshuang on 16-12-20.
//

#include "grouphandler.h"
#include "rawgroup.h"

bool GroupHandler::prepareQuery(Table *table, SQLSelectorGroup *selectorGroup, SQLTableGroup *groupByGroup) {
    myTable = table;
    if (groupByGroup != NULL) {
        for (const std::string& colName : *groupByGroup) {
            int id = table->getColumnIndexByName(colName);
            if (id == -1) {
                driver->addErrorMessage("No such column " + colName + " in table " + table->getname());
                return false;
            }
            referers.push_back(id);
        }
        hasGroupClause = true;
    }
    for (SQLSelector* s : selectorGroup->selectors) {
        int id = table->getColumnIndexByName(s->tableName);
        if (id == -1) {
            driver->addErrorMessage("No such column " + s->tableName + " in table " + table->getname());
            return false;
        }
        if (s->groupMethod == BLANK) {
            // Check if exists in refers
            int displayIndex = -1;
            for (unsigned int i = 0; i < referers.size(); ++ i) {
                if (referers[i] == id) {
                    displayIndex = i;
                    break;
                }
            }
            if (displayIndex == -1) {
                driver->addErrorMessage("Select targets must be in group targets.");
                return false;
            }
            displays.push_back(displayIndex);
        } else {
            GroupTarget currentTarget;
            currentTarget.method = s->groupMethod;
            currentTarget.columnID = id;
            displays.push_back(1000 + (int) groupTargets.size());
            groupTargets.push_back(currentTarget);
        }
    }
    return true;
}

SQLResult* GroupHandler::executeQuery() {
    if (hasGroupClause) return executeQueryWithGroup();
    else return executeQueryWithoutGroup();
}

SQLResult *GroupHandler::executeQueryWithGroup() {
    rawGroupMap rawGroups;

    strIntMap* referColDicts = new strIntMap[referers.size()];
    strIntMap::iterator referColDictIterator;
    vector<string>* referColUniqueVal = new vector<string>[referers.size()];

    Iterator* iterator = IteratorFactory::getiterator(myTable);
    Record* record = RecordFactory::getrecord(myTable);

    while (iterator->available()) {
        iterator->getdata(record);

        std::vector<int> refLoopUpResult;

        for (unsigned int i = 0; i < referers.size(); ++ i) {
            string colValue = record->getAt(referers[i]);
            referColDictIterator = referColDicts[i].find(colValue);
            if (referColDictIterator == referColDicts[i].end()) {
                referColDicts[i][colValue] = (int) referColUniqueVal[i].size();
                refLoopUpResult.push_back((int) referColUniqueVal[i].size());
                referColUniqueVal[i].push_back(colValue);
            } else {
                refLoopUpResult.push_back(referColDictIterator->second);
            }
        }

        // If hash exists, put the target value in raw groups.
        rawGroupMap::iterator rgIt = rawGroups.find(refLoopUpResult);
        if (rgIt == rawGroups.end()) {
            rgIt = rawGroups.insert(make_pair(refLoopUpResult, std::vector<RawGroup*>(groupTargets.size()))).first;
            for (unsigned int i = 0; i < groupTargets.size(); ++ i) {
                rgIt->second[i] = new RawGroup();
            }
        }
//        assert(false);
        //You can't use get At for group algorithm.
        //So I write some code to replace it.
        //please check it.

        for (unsigned int i = 0; i < groupTargets.size(); ++ i) {
            char type = record->getcolumns()[groupTargets[i].columnID]->getType()[6];
            rgIt->second[i]->add(getGroupableValue(type, record->getAt(groupTargets[i].columnID)));
        }

//        for (unsigned int i = 0; i < groupTargets.size(); ++ i) {
//            rgIt->second[i]->add(record->getAt(groupTargets[i].columnID));
//        }


        ++ (*iterator);
    }

    // At last, gather and generate results.
    SQLResult* retVal = new SQLResult((int) displays.size());
    for (unsigned int i = 0; i < displays.size(); ++ i) {
        if (displays[i] >= 1000) {
            int groupTargetID = displays[i] - 1000;
            retVal->addTitleField(convertTitle(myTable->getcolumnname(
                    groupTargets[groupTargetID].columnID), groupTargets[groupTargetID].method));
        } else {
            retVal->addTitleField(myTable->getcolumnname(referers[displays[i]]));
        }
    }

    vector<char> dispTypes;
    for (unsigned int j = 0; j < displays.size(); ++ j) {
        if (displays[j] >= 1000) dispTypes.push_back('P');
        else dispTypes.push_back(myTable->getcolumns()[referers[displays[j]]]->getType()[6]);
    }

    for (rawGroupMap::iterator iterator1 = rawGroups.begin(); iterator1 != rawGroups.end(); ++ iterator1) {
        retVal->addNew();
        for (unsigned int j = 0; j < displays.size(); ++ j) {
            string colDisp;
            if (displays[j] >= 1000) {
                int idInGroupTargets = displays[j] - 1000;
                switch (groupTargets[idInGroupTargets].method) {
                    case MAX:
                        colDisp = iterator1->second[idInGroupTargets]->getmax();
                        break;
                    case MIN:
                        colDisp = iterator1->second[idInGroupTargets]->getmin();
                        break;
                    case AVG:
                        colDisp = iterator1->second[idInGroupTargets]->getaverage();
                        break;
                    case SUM:
                        colDisp = iterator1->second[idInGroupTargets]->getsum();
                        break;
                    case BLANK:
                        assert(false);
                }
            } else {
                int colValUniqueID = iterator1->first[displays[j]];
                colDisp = referColUniqueVal[displays[j]][colValUniqueID];
                colDisp = UIC::getUserOutput(dispTypes[j], colDisp, false);
            }
            retVal->setData(j, colDisp);
        }
        for (RawGroup* rg : iterator1->second) {
            delete rg;
        }
    }

    delete[] referColDicts;
    delete[] referColUniqueVal;

    delete iterator;
    delete record;

    return retVal;
}

SQLResult *GroupHandler::executeQueryWithoutGroup() {

    Iterator* iterator = IteratorFactory::getiterator(myTable);
    Record* record = RecordFactory::getrecord(myTable);

    std::vector<RawGroup*> resultGroup(groupTargets.size());

    for (unsigned int i = 0; i < resultGroup.size(); ++ i) {
        resultGroup[i] = new RawGroup();
    }

    while (iterator->available()) {
        iterator->getdata(record);

        for (unsigned int i = 0; i < groupTargets.size(); ++ i) {
            char type = record->getcolumns()[groupTargets[i].columnID]->getType()[6];
            resultGroup[i]->add(getGroupableValue(type, record->getAt(groupTargets[i].columnID)));
        }

//        for (unsigned int i = 0; i < groupTargets.size(); ++ i) {
//            resultGroup[i]->add(record->getAt(groupTargets[i].columnID));
//        }

        ++ (*iterator);
    }

    // At last, gather and generate results.
    SQLResult* retVal = new SQLResult((int) displays.size());
    for (unsigned int i = 0; i < displays.size(); ++ i) {
        if (displays[i] >= 1000) {
            int groupTargetID = displays[i] - 1000;
            retVal->addTitleField(convertTitle(myTable->getcolumnname(
                    groupTargets[groupTargetID].columnID), groupTargets[groupTargetID].method));
        } else {
            retVal->addTitleField(myTable->getcolumnname(referers[displays[i]]));
        }
    }

    // Only one line is needed.
    retVal->addNew();
    for (unsigned int j = 0; j < displays.size(); ++ j) {
        string colDisp;
        if (displays[j] >= 1000) {
            int idInGroupTargets = displays[j] - 1000;
            switch (groupTargets[idInGroupTargets].method) {
                case MAX:
                    colDisp = resultGroup[idInGroupTargets]->getmax();
                    break;
                case MIN:
                    colDisp = resultGroup[idInGroupTargets]->getmin();
                    break;
                case AVG:
                    colDisp = resultGroup[idInGroupTargets]->getaverage();
                    break;
                case SUM:
                    colDisp = resultGroup[idInGroupTargets]->getsum();
                    break;
                case BLANK:
                    assert(false);
            }
        }
        retVal->setData(j, colDisp);
    }
    for (RawGroup* rg : resultGroup) {
        delete rg;
    }

    delete iterator;
    delete record;

    return retVal;
}

string GroupHandler::convertTitle(const string &orig, SQLGroupMethod method) {
    if (method == SUM) return orig + ".sum";
    if (method == AVG) return orig + ".average";
    if (method == MAX) return orig + ".max";
    if (method == MIN) return orig + ".min";
    return orig;
}

string GroupHandler::getGroupableValue(char type, const string &val) {
    static stringstream ss;
    static long long l1;
    static double r1;
    switch (type)
    {
        case 'I':
            return val;
        case 'L':
//            memcpy(&l1, val.data(), 8);
            l1 = *((long long*) val.data());
            ss.clear();
            ss << l1;
            return ss.str();
        case 'R':
//            memcpy(&r1, val.data(), 8);
            r1 = *((double*) val.data());
            ss.clear();
            ss << r1;
            return ss.str();
    }
    return "";
}
