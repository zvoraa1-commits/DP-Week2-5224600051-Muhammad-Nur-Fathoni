#ifndef COMBAT_RESOLVER_H
#define COMBAT_RESOLVER_H

#include "TurnChoice.h"
#include <string>

enum class RoundResult { PlayerWin, EnemyWin, Draw };

class CombatResolver {
public:
    RoundResult Resolve(Choice playerChoice, Choice enemyChoice) const;
    Choice GetRandomChoice() const;
    std::string ChoiceToString(Choice c) const;
};

#endif
