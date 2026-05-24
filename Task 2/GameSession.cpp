#include <iostream>
#include "GameSession.h"

GameSession::GameSession()
    : player_("Player", 15), enemy_("Enemy", 15) {}

void GameSession::StartGame() {
    std::cout << "=== ROCK PAPER SCISSORS RPG ===\n";
    std::cout << "Player HP: " << player_.GetHP()
              << " | Enemy HP: " << enemy_.GetHP() << "\n\n";

    int round = 1;
    while (!IsGameOver()) {
        PlayRound(round++);
    }

    std::cout << "=== GAME OVER ===\n";
    if (player_.IsAlive()) {
        std::cout << "Player WINS the game!\n";
    } else {
        std::cout << "Enemy WINS the game!\n";
    }
}

void GameSession::PlayRound(int roundNumber) {
    std::cout << "--- Round " << roundNumber << " ---\n";

    // Phase 1: Player memilih aksi
    Choice playerChoice = GetPlayerChoice();

    // Phase 2: Enemy memilih aksi secara random
    Choice enemyChoice = resolver_.GetRandomChoice();
    std::cout << "[ENEMY] chose: " << resolver_.ChoiceToString(enemyChoice) << "\n";

    // Phase 3: Resolve pertarungan
    RoundResult result = resolver_.Resolve(playerChoice, enemyChoice);

    // Phase 4 & 5: Hitung damage & update streak
    if (result == RoundResult::PlayerWin) {
        int damage = streak_.OnWin();
        std::cout << "[RESULT] Player wins this round!\n";
        if (damage == 2) std::cout << "[STREAK] Streak 2! Bonus +1 damage!\n";
        if (damage == 3) std::cout << "[STREAK] Streak 3! Bonus +2 damage! Streak reset.\n";

        // Phase 6: Update HP musuh
        enemy_.TakeDamage(damage);
        std::cout << "[DAMAGE] Enemy takes " << damage << " damage | Enemy HP: " << enemy_.GetHP() << "\n";

    } else if (result == RoundResult::EnemyWin) {
        streak_.OnLose();
        std::cout << "[RESULT] Enemy wins this round! Streak reset.\n";

        // Phase 6: Update HP player
        player_.TakeDamage(1);
        std::cout << "[DAMAGE] Player takes 1 damage | Player HP: " << player_.GetHP() << "\n";

    } else {
        std::cout << "[RESULT] Draw! No damage.\n";
    }

    // Phase 7: Cek kondisi menang/kalah
    std::cout << "[STATUS] Player HP: " << player_.GetHP()
              << " | Enemy HP: " << enemy_.GetHP() << "\n\n";
}

Choice GameSession::GetPlayerChoice() const {
    int input;
    std::cout << "[ACTION] Choose: 1=Rock, 2=Paper, 3=Scissors > ";
    std::cin >> input;

    if (input == 1) return Choice::Rock;
    if (input == 2) return Choice::Paper;
    return Choice::Scissors;
}

bool GameSession::IsGameOver() const {
    return !player_.IsAlive() || !enemy_.IsAlive();
}
