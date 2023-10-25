#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/SpriteRenderer.h"
#include "Components/CharacterControl.h"
#include "Components/SquareCollider.h"

bool booll = false;

void Scene::Update(sf::Time _delta)
{
	if (!booll)
	{
		sf::Texture ImageBongo;
		ImageBongo.loadFromFile("Sprite/player/john_static.png");

		GameObject* player = CreateCharacterGameObject("Player", 200.f, 400.f, ImageBongo, 2.5f, 2.5f);

		booll = true;
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

GameObject* Scene::CreateCharacterGameObject(const std::string& name, float positionx, float positiony, const sf::Texture texture, float scalex, float scaley)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(positionx, positiony));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(20.f);
	squareCollider->SetHeight(20.f);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);

	CharacterControl* characterControl = gameObject->CreateComponent<CharacterControl>();

	return gameObject;
}