#ifndef STREAK_TRACKER_H
#define STREAK_TRACKER_H

class StreakTracker {
public:
    StreakTracker();
    int OnWin();   // update streak lalu return damage yang sesuai
    void OnLose(); // reset streak ke 0
    int GetStreak() const;

private:
    int streak_;
};

#endif
