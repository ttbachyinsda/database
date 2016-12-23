//
// Created by jameshuang on 16-12-14.
//

#include "queryoptimizer.h"
#include "joinstrategies/nestedloopjoin.h"
#include "joinstrategies/hashjoin.h"
#include "joinstrategies/sortmergejoin.h"
#include <climits>
#include <algorithm>

void QueryOptimizer::generatePlan(const std::vector<ConditionPair> &conditions,
                                  const std::vector<Table *> &tables) {
    if (joinStrategy) delete joinStrategy;
    transformedConditions.clear();
    // IMPORTANT: conditions get into the strategies must be first driver, second passenger!!!
    // IMPORTANT: be sure to SWITCH OPERAND DIRECTION!!!

    /**
     * Plan generate algorithm specially designed for THJDB.
     * - traverse conditions and get number of all pairs.
     *   We set number of pairs to \alpha.
     *   it indicates the decay coef for next iteration. (may)
     * - then we generate the optimized Strategy for each pair:
     *   Give each condition in a pair a score indicating estimated efforts.
     *   Test norm and inversed into strategy. This is \beta.
     * For persistency we can choose a coef \lambda to control.
     */

    ConditionPack selectedCP;
    selectedCP.estimatedCost = (numeric_limits<float>::max)();

    for (unsigned int i = 0; i < conditions.size(); ++ i) {
        float cost;
        char strategy;
        bool reverse = false;
        do {
            cost = getCost(conditions[i], reverse, tables, strategy);
            if (cost < selectedCP.estimatedCost) {
                selectedCP.estimatedCost = cost;
                selectedCP.conditionID = i;
                selectedCP.reverse = reverse;
                selectedCP.selectedStrategy = strategy;
            }
            reverse = !reverse;
        } while (reverse);
    }

    driverTableID = conditions[selectedCP.conditionID].left.tableIndex;
    int did = conditions[selectedCP.conditionID].left.columnIndex;
    passengerTableID = conditions[selectedCP.conditionID].right.tableIndex;
    int tid = conditions[selectedCP.conditionID].right.columnIndex;
    SQLOperand operand = conditions[selectedCP.conditionID].operand;

    if (selectedCP.reverse) {
        swap(driverTableID, passengerTableID);
        swap(tid, did);
        operand = QueryCondition::getInverseOperand(operand);
    }

    for (const ConditionPair& c : conditions) {
        if (c.left.tableIndex == driverTableID && c.right.tableIndex == passengerTableID) {
            transformedConditions.push_back(c);
        } else if (c.left.tableIndex == passengerTableID && c.right.tableIndex == driverTableID) {
            ConditionPair nc = c;
            swap(nc.left.tableIndex, nc.right.tableIndex);
            swap(nc.left.columnIndex, nc.right.columnIndex);
            nc.operand = QueryCondition::getInverseOperand(nc.operand);
            transformedConditions.push_back(nc);
        }
    }

    switch (selectedCP.selectedStrategy) {
        case 'n':
            joinStrategy = new NestedLoopJoin(transformedConditions);
            break;
        case 'h':
            joinStrategy = new HashJoin(transformedConditions);
            break;
        case 'm':
            joinStrategy = new SortMergeJoin(transformedConditions);
            break;
        default:
            assert(false);
    }

    joinStrategy->setMainCondition(did, tid, operand);
    joinStrategy->prepareTable(tables[driverTableID], tables[passengerTableID]);

}

float QueryOptimizer::getCost(const ConditionPair &cp, bool reverse,
                              const std::vector<Table *> &tables, char &strat) {
    int leftSize = tables[cp.left.tableIndex]->getTraverseCost();
    int rightSize = tables[cp.right.tableIndex]->getTraverseCost();
    bool leftIndexed = (tables[cp.left.tableIndex]->getindexes()[cp.left.columnIndex] != NULL);
    bool rightIndexed = (tables[cp.right.tableIndex]->getindexes()[cp.right.columnIndex] != NULL);
    SQLOperand op = cp.operand;

    if (reverse) {
        swap(leftSize, rightSize);
        swap(leftIndexed, rightIndexed);
        op = QueryCondition::getInverseOperand(op);
    }

    strat = 'n';

    return NestedLoopJoin::estimateCost(leftSize, rightSize, leftIndexed, rightIndexed, op);
}
