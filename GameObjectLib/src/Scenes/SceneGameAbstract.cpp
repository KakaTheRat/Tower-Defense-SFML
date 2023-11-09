#include "Scenes/SceneGameAbstract.h"

#include "SceneManager.h"
#include "AssetManager.h"
#include "WindowManager.h"

#include "Components/Button.h"
#include "Components/Carre.h"
#include "Components/SquareCollider.h"
#include "Components/SpriteRenderer.h"
#include "Components/Ressource.h"
#include "Components/Entities/Enemies/Grunt.h"
#include "Components/Entities/Enemies/Turret.h"
#include "Components/FireBullet.h"
#include "Components/HealthPointBar.h"
#include "Components/Inputs/InputPlayer.h"
#include "Components/Entities/Enemies/EnemyA.h"
#include "Components/Entities/Enemies/EnemyB.h"
#include "Components/Entities/Enemies/EnemyC.h"
#include "Components/Entities/Towers/Nexus.h"


SceneGameAbstract::SceneGameAbstract(sf::RenderWindow* _window) : Scene(_window) {
	this->Awake();
	srand(time(nullptr));
}


SceneGameAbstract::~SceneGameAbstract() {
	this->Delete();
}

void SceneGameAbstract::Create() {
	Scene::Create();
	this->CreatePauseMenuButtons();
}

void SceneGameAbstract::Delete() {
	this->enemies.clear();
	delete texture;
	Scene::Delete();
}


void SceneGameAbstract::CreatePauseMenuButtons() {
	pausePlayButton = CreateButtonGameObject("Continue", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 4.0, 50);
	pauseMenuPrincipalButton = CreateButtonGameObject("Menu Principal", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2.5, 50);
	pauseOptionsButton = CreateButtonGameObject("Options", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.8, 50);
	pauseQuitButton = CreateButtonGameObject("Quit", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.4, 50);
	this->ManageSceneGameButtonsPause(false);
}

void SceneGameAbstract::Awake() {
	Scene::Awake();
}

void SceneGameAbstract::CreatePlayer() {
}

void SceneGameAbstract::CreateTower()
{

	varus = this->CreateBatimantGameObject("Varus", 0.f, 0.f, *AssetManager::GetAsset("Varus"), 2.5f, 2.5f, 300.f, 30.f);
	varus->SetActive(false);
	lulu = this->CreateBatimantGameObject("Lulu", 0.f, 0.f, *AssetManager::GetAsset("Lulu"), 2.5f, 2.5f,300.f, 30.f);
	lulu->SetActive(false);
	malphite = this->CreateBatimantGameObject("Malphite", 0.f, 0.f, *AssetManager::GetAsset("Malphite"), 2.5f, 2.5f,300.f, 30.f);
	malphite->SetActive(false);
	xinZhao = this->CreateBatimantGameObject("XinZhao", 0.f, 0.f, *AssetManager::GetAsset("XinZhao"), 2.5f, 2.5f,300.f, 30.f);
	xinZhao->SetActive(false);
	//bat2 = this->CreateBatimantGameObject("Bat2", 0.f, 0.f, *texture, 2.5f, 2.5f,300.f, 0.f);
	//bat3 = this->CreateBatimantGameObject("Bat3", 0.f, 0.f, *texture, 2.5f, 2.5f,300.f, 5.f);

};

void SceneGameAbstract::CreateRessource()
{
	ressource = this->CreatePlayerRessourceGameObject("Ressources", 0.f, 0.f, *AssetManager::GetAsset("Gold"), 2.5f, 2.5f, 300.f, 300.f);
};

void SceneGameAbstract::RemoveEnemy(GameObject* _enemyToRemove) {
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[_enemyToRemove](GameObject* obj) {
			return obj == _enemyToRemove;
		}), enemies.end());
}

void SceneGameAbstract::RemoveTower(GameObject* _towerToRemove) {
	towers.erase(std::remove_if(towers.begin(), towers.end(),
		[_towerToRemove](GameObject* obj) {
			return obj == _towerToRemove;
		}), enemies.end());
}



void SceneGameAbstract::ManageSceneGameButtonsPause(bool _state) {
	this->pauseMenuPrincipalButton->SetActive(_state);
	this->pausePlayButton->SetActive(_state);
	this->pauseOptionsButton->SetActive(_state);
	this->pauseQuitButton->SetActive(_state);
}

void SceneGameAbstract::ManagePause()
{
	this->ManageSceneGameButtonsPause(!isActive);
	for (GameObject* enemy : this->enemies)
	{
		enemy->SetActive(isActive);
	}
}

void SceneGameAbstract::Update(sf::Time _delta) {
	this->inputGame->Update(_delta);
	this->ManagePause();
	if (isActive)
	{
		Scene::Update(_delta);

	}
	else
	{
		if (pausePlayButton->GetComponent<Button>()->IsClicked()) {
			this->ManagePause();
		}
		else if (pauseMenuPrincipalButton->GetComponent<Button>()->IsClicked()) {
			SceneManager::RunScene("SceneMainMenu");
		}
		else if (pauseOptionsButton->GetComponent<Button>()->IsClicked()) {
			std::cout << "Options" << std::endl;
		}
		else if (pauseQuitButton->GetComponent<Button>()->IsClicked()) {
			WindowManager::GetWindow()->close();
		}
	}
}

void SceneGameAbstract::CreatePlatform(sf::Texture textureplatforme) {
}

void SceneGameAbstract::CreateBackground()
{
	sf::Texture backgroundTexture1;

	if (!backgroundTexture1.loadFromFile("../assets/Sprite/background/background_color.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background1 = CreateBackgroundGameObject("Background1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture1);
};

void SceneGameAbstract::Render(sf::RenderWindow* _window) {
	Scene::Render(_window);
}


GameObject* SceneGameAbstract::CreateTowerGameObject(const std::string& name, float positionx, float positiony, const sf::Texture texture, float scalex, float scaley)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));


	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	InputPlayer* inputPlayer = gameObject->CreateComponent<InputPlayer>();

	

	return gameObject;
}
GameObject* SceneGameAbstract::CreateBatimantGameObject(const std::string& name, float _x, float _y, const sf::Texture texture, float scalex, float scaley, float prixGold, float prixMana)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Ressource* ressource = gameObject->CreateComponent<Ressource>();
	ressource->SetGold(prixGold);
	ressource->SetMana(prixMana);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	InputPlayer* inputPlayer = gameObject->CreateComponent<InputPlayer>();

	/*HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(player->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(player->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();*/

	return gameObject;
}
GameObject* SceneGameAbstract::CreatePlayerRessourceGameObject(const std::string& name, float _x, float _y, const sf::Texture texture, float scalex, float scaley, float ressourceGold, float ressourceMana)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Ressource* ressource = gameObject->CreateComponent<Ressource>();
	ressource->SetGold(ressourceGold);
	ressource->SetMana(ressourceMana);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	InputPlayer* inputPlayer = gameObject->CreateComponent<InputPlayer>();

	return gameObject;

}
//ENEMY
GameObject* SceneGameAbstract::CreateGruntGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	Grunt* enemy = gameObject->CreateComponent<Grunt>();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetPosition(_x, _y);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();


	return gameObject;

}

GameObject* SceneGameAbstract::CreateTurretGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateCarreGameObject(const std::string& name, float x, float y)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));
	gameObject->SetActive(true);

	Carre* carre = gameObject->CreateComponent<Carre>();
	carre->SetPosition(x, y);
	carre->SetSize(100, 100);
	carre->SetOrigin();
	carre->SetCarre();

	return gameObject;
};

GameObject* SceneGameAbstract::CreateBulletGameObject(const std::string& name, const sf::Texture textureBullet, float scalex, float scaley, GameObject* _player)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(textureBullet);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(0.5, 0.5);

	FireBullet* fireBullet = gameObject->CreateComponent<FireBullet>();
	fireBullet->setDirection(_player);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateEnemyAGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, int lane, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	EnemyA* enemy = gameObject->CreateComponent<EnemyA>();
	enemy->SetLane(lane);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetPosition(_x, _y);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();

	enemies.push_back(gameObject);

	return gameObject;
}

GameObject* SceneGameAbstract::CreateEnemyBGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, int lane, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	EnemyB* enemy = gameObject->CreateComponent<EnemyB>();
	enemy->SetLane(lane);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetPosition(_x, _y);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();

	enemies.push_back(gameObject);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateEnemyCGameObject(const std::string& name, float _x, float _y, float scalex, float scaley, int lane, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));

	EnemyC* enemy = gameObject->CreateComponent<EnemyC>();
	enemy->SetLane(lane);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(scalex, scaley);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetPosition(_x, _y);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();

	enemies.push_back(gameObject);

	return gameObject;

}

GameObject* SceneGameAbstract::CreateNexusGameObject()
{
	GameObject* gameObject = CreateGameObject("nexus");
	gameObject->SetPosition(Maths::Vector2f(482.f, 838.f));

	Nexus* nexus = gameObject->CreateComponent<Nexus>();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(*AssetManager::GetAsset("Nexus"));
	sprite->SetScale(1.f, 1.f);
	sprite->SetSprite();

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	squareCollider->SetScale(1.f, 1.f);

	this->nexus = gameObject;

	return gameObject;

}


