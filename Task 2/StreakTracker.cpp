#include "StreakTracker.h"

StreakTracker::StreakTracker() : streak_(0) {}

int StreakTracker::OnWin() {
    streak_++;

    // streak 1 = damage 1 (normal)
    // streak 2 = damage 2 (bonus +1)
    // streak 3 = damage 3 (bonus +2), lalu reset
    int damage = streak_;

    if (streak_ >= 3) {
        streak_ = 0; // reset setelah streak 3
    }

    return damage;
}

void StreakTracker::OnLose() {
    streak_ = 0;
}

int StreakTracker::GetStreak() const {
    return streak_;
}
