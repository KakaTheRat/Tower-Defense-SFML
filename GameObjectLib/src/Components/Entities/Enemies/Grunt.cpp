#include "Components/Entities/Enemies/Grunt.h"
#include "AssetManager.h"


Grunt::Grunt() : EnemyAbstract(200, 10, 20.f,1.f,10.f, 10.f) {}
Grunt::Grunt(int _hp, int _damage, int _lane, float _speed, float _attackspeed, float _range) : EnemyAbstract(_hp, _damage, _lane, _speed, _attackspeed, _range) {}

void Grunt::setDirection(Direction newDirection) {
    direction = newDirection;

}

void Grunt::MouvementGrunt() {
    srand(time(nullptr));
    //int rand_attack = rand() % 3 + 1;
    //int rand_mouve = rand() % 2 + 1;
    int rand_mouve = 2;
    if (rand_mouve == 1) {
        GetOwner()->GetComponent<Sprite>()->GruntPlayAnimation();

        /*grunt.SetPosition(grunt.SetPosition()) */
            /*if (rand_attack == 1) {
                enemy.loadFromFile("Sprite/enemy/grunt_shoot.png");
            }*/
    }
    else if (rand_mouve == 2) {
        GetOwner()->SetPosition(GetOwner()->GetPosition() + Maths::Vector2f::Right + Maths::Vector2f(3, 0));
        GetOwner()->GetComponent<Grunt>()->setDirection(Grunt::Direction::Right);
        GetOwner()->GetComponent<Sprite>()->GruntPlayAnimationRun();
    }
    else if (healthPoint == 0) {
        //enemy.loadFromFile("Sprite/enemy/grunt_death.png");
    }
}