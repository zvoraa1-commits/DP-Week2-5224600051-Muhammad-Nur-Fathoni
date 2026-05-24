#include "CombatResolver.h"
#include <cstdlib>

RoundResult CombatResolver::Resolve(Choice player, Choice enemy) const {
    if (player == enemy) return RoundResult::Draw;

    if ((player == Choice::Rock     && enemy == Choice::Scissors) ||
        (player == Choice::Scissors && enemy == Choice::Paper)    ||
        (player == Choice::Paper    && enemy == Choice::Rock)) {
        return RoundResult::PlayerWin;
    }

    return RoundResult::EnemyWin;
}

Choice CombatResolver::GetRandomChoice() const {
    return static_cast<Choice>(rand() % 3);
}

std::string CombatResolver::ChoiceToString(Choice c) const {
    if (c == Choice::Rock)     return "Rock";
    if (c == Choice::Paper)    return "Paper";
    return "Scissors";
}
