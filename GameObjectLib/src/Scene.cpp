#include "Scene.h"
#include "SceneManager.h"
#include "Components/Button.h"
#include "Components/SquareCollider.h"
#include "Components/SpriteRenderer.h"
#include "Components/Gravity.h"
#include "Components/Platforme.h"
#include "Components/Enemy/Grunt.h"
#include "Components/FireBullet.h"
#include "Components/Rectangle.h"

sf::RenderWindow* Scene::window = nullptr;

Scene::Scene(sf::RenderWindow* _window) {
	window = _window;
	this->balleTiree = false;
	this->inputHandlerPlayer = nullptr;
}

void Scene::Create() {
	balleTiree = false;
	interval = sf::seconds(0.1f);
}

void Scene::Awake() {
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(sf::Time _delta)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			/*if (event.key.code == sf::Keyboard::Escape) window->close();*/
			if (event.key.code == sf::Keyboard::LAlt) if (event.key.code == sf::Keyboard::F4) window->close();
		}

	}

	Command* commandMoves = inputHandlerPlayer->HandleInput();
	if (commandMoves) {
		commandMoves->Execute();
	}
	Command* fireBullet = inputHandlerPlayer->FireInput();
	if (fireBullet && !balleTiree) {
		fireBullet->Execute(_delta);
		balleTiree = true;
		clock.restart();
	}
	if (clock.getElapsedTime() >= interval) {
		balleTiree = false;
	}

	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update(_delta);
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

//PLAYER 

GameObject* Scene::CreateCharacterGameObject(const std::string& name, float positionx, float positiony, const sf::Texture texture, float scalex, float scaley)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(60.f);
	squareCollider->SetHeight(60.f);

	Player* playerController = gameObject->CreateComponent<Player>();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);

	Gravity* gravity = gameObject->CreateComponent<Gravity>();

	InputPlayer* inputPlayer = gameObject->CreateComponent<InputPlayer>();
	inputHandlerPlayer = inputPlayer;

	return gameObject;
}

//ENEMY
GameObject* Scene::CreateGruntGameObject(const std::string& name, float positionx, float positiony, float scalex, float scaley, sf::Texture _texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(60.f);
	squareCollider->SetHeight(60.f);

	Sprite* spriteBullet = gameObject->CreateComponent<Sprite>();
	spriteBullet->SetTexture(_texture);
	spriteBullet->SetScale(scalex, scaley);

	Gravity* gravity = gameObject->CreateComponent<Gravity>();


	return gameObject;

}

GameObject* Scene::CreateBulletGameObject(const std::string& name, const sf::Texture textureBullet, float scalex, float scaley, GameObject* _player)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()));

	Sprite* spriteBullet = gameObject->CreateComponent<Sprite>();
	spriteBullet->SetTexture(textureBullet);
	spriteBullet->SetScale(scalex, scaley);

	FireBullet* fireBullet = gameObject->CreateComponent<FireBullet>();


	return gameObject;

}

//GAME ELEMENT

GameObject* Scene::CreateButtonGameObject(const std::string& name, float x, float y, unsigned int fontSize)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	gameObject->SetActive(true);
	Button* button = gameObject->CreateComponent<Button>();
	button->SetPosition(x, y);
	button->SetButton(fontSize);
	button->SetOrigin();

	return gameObject;
}


GameObject* Scene::CreatePlatformObject(const std::string& name, float x, float y, float scaleX, float scaleY) {

	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(scaleX);
	squareCollider->SetHeight(scaleY);

	Platforme* platform = gameObject->CreateComponent<Platforme>();
	platform->SetPosition(x, y);
	platform->SetPlatforme();
	platform->SetSize(scaleX, scaleY);

	return gameObject;
}

GameObject* Scene::CreateBackgroundGameObject(const std::string& name, float x, float y, sf::Color _color) {

	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	Rectangle* background = gameObject->CreateComponent<Rectangle>();
	background->Create(SceneManager::GetWindow()->getSize().x, SceneManager::GetWindow()->getSize().y, _color);
	
	return gameObject;
}

GameObject* Scene::CreateBackgroundGameObject(const std::string& name, float x, float y, const sf::Texture texture) {
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	Sprite* background = gameObject->CreateComponent<Sprite>();
	background->SetTexture(texture);
	float scalerX = (float)SceneManager::GetWindow()->getSize().x / texture.getSize().x;
	float scalerY = (float)SceneManager::GetWindow()->getSize().y / texture.getSize().y;
	background->SetScale(scalerX, scalerY);

	return gameObject;
}
