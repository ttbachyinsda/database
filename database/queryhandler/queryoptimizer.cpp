//
// Created by jameshuang on 16-12-14.
//

#include "queryoptimizer.h"

void QueryOptimizer::generatePlan(const std::vector<ConditionPair> &conditions,
                                  const std::vector<Table *> &tables) {
    if (joinStrategy) delete joinStrategy;

}
