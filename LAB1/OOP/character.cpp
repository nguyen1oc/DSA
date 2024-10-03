Character::Character() {
    // STUDENT ANSWER
    x = 0;
    y = 0;
    hp = 0;
}

Character::Character(int hp, int x, int y): hp(hp), x(x), y(y) {
    // STUDENT ANSWER
}

int Character::getHp() {
    // STUDENT ANSWER
    return hp;
}

void Character::setHp(int hp) {
    // STUDENT ANSWER
    this -> hp = hp;
}

int Character::getX() {
    // STUDENT ANSWER
    return x;
}

void Character::setX(int x) {
    // STUDENT ANSWER
    this -> x = x;
}

int Character::getY() {
    // STUDENT ANSWER
    return y;
}

void Character::setY(int y) {
    // STUDENT ANSWER
    this -> y = y;
}

int Character::getManhattanDistTo(Character* other) {
    // STUDENT ANSWER
    int deltaX = this -> x  - other -> x;
    int deltaY = this -> y - other -> y;
    return abs(deltaX) + abs(deltaY);
}
