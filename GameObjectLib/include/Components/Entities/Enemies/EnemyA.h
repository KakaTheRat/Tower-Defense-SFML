#include "Components/Entities/EnemyAbstract.h"
#include "Components/SpriteRenderer.h"

class EnemyA : public EnemyAbstract {
public:
	EnemyA();
private:
	Sprite sprite;
};