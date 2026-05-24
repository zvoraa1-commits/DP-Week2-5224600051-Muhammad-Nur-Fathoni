#include "Character.h"

Character::Character(std::string name, int hp)
    : name_(name), hp_(hp) {}

std::string Character::GetName() const { return name_; }

int Character::GetHP() const { return hp_; }

void Character::TakeDamage(int damage) {
    hp_ -= damage;
    if (hp_ < 0) hp_ = 0;
}

bool Character::IsAlive() const { return hp_ > 0; }
