#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "Character.h"
#include "CombatResolver.h"
#include "StreakTracker.h"

// GameSession: hanya mengatur urutan phase (INVARIANT)
// Tidak boleh mengandung logic RPS, damage, atau streak calculation
class GameSession {
public:
    GameSession();
    void StartGame();

private:
    void PlayRound(int roundNumber);
    Choice GetPlayerChoice() const;
    bool IsGameOver() const;

    Character player_;
    Character enemy_;
    CombatResolver resolver_;
    StreakTracker streak_;
};

#endif
