#include "Components/Armes.h"
#include "GameObject.h"
#include "Components/FireBullet.h"
#include "SceneManager.h"

Armes::Armes() {
	 fireRate = 0.2f;
	 fireCooldown = 0;
	 mag = 10;
	 maxAmo = 10;
	 reload = 5.f;
	 activeReload = 0.f;
}

Armes::~Armes() {}

void Armes::Update(sf::Time _delta) {
	Component::Update(_delta);

	if (activeReload > 0.f) {
		activeReload -= _delta.asSeconds();
	}
	if (activeReload <= 0 && mag <= 0) {
		mag = maxAmo;
	}
	if (fireCooldown > 0.f) {
		fireCooldown -= _delta.asSeconds();
	}

}

void Armes::Shoot() {
	if (mag > 0 && fireCooldown <= 0 && activeReload <= 0) {
		mag -= 1;
		fireCooldown = fireRate;
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile("../assets/Sprite/player/weaponBullet/weapon_bullet_0.png")) {
			std::cout << "pas d'image" << std::endl;
		}
		std::cout << mag << std::endl;
		GameObject* bullet = SceneManager::GetActiveScene()->CreateBulletGameObject("Bullet", *texture, 2.5f, 2.5f, GetOwner());
		bullet->SetPosition(GetOwner()->GetPosition());
		if (mag == 0) {
			std::cout << "JE RENTRE";
			activeReload = reload;
			fireCooldown = 0.f;
		}
	}
	
}