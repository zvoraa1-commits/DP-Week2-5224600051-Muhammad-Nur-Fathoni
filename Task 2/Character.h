#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    Character(std::string name, int hp);
    std::string GetName() const;
    int GetHP() const;
    void TakeDamage(int damage);
    bool IsAlive() const;

private:
    std::string name_;
    int hp_;
};

#endif
