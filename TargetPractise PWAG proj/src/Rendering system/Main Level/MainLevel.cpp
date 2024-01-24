#include "pch.h"
#include "mainLevel.h"
#include <set>
#include <ctime>

#include "../Rendering system/Model/objReader.h"
#include "../Rendering system/Model/vboIndexer.h"
#include "../SourceDep/stb_image.h"

MainLevel::MainLevel(GameState* gameState) :
	_tmpDefaultFont(std::move(Font("res/Fonts/Segan.ttf", 32))),
	_timeLabel(20, 50, "Time:", _tmpDefaultFont), _timeValueText(140, 53, "0", _tmpDefaultFont),
	_pointsLabel(20, 90, "Points:", _tmpDefaultFont), _pointsValueText(140, 93, "0", _tmpDefaultFont),
	_bulletLabel(20, 130, "Bullet:", _tmpDefaultFont), _bulletValueText(140, 130, "0", _tmpDefaultFont),
	_HUD("res/Textures/HUD.png", 100, 100, 800, 450, true)
{
	_gameState = gameState;
	_initLevel();
}

MainLevel::~MainLevel()
{
	delete _player;
	delete _shaderProgram;
	delete _textShader;
	delete _skybox;

	delete _targetMaterialPrefab;
	delete _bulletMaterialPrefab;

	for (size_t i = 0; i < _textures.size(); i++)
	{
		delete _textures[i];
	}

	for (size_t i = 0; i < _targets.size(); i++)
	{
		_targets[i]->destroy();
	}

	if (_bullet)
	{
		_bullet->destroy();
	}
}

void MainLevel::input(float deltaTime, GameReference gameReference, Keyboard& keyboard, Mouse& mouse)
{
	_player->input(gameReference, keyboard, deltaTime);

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyF)])
	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyF)])
	{
		_shootBullet();
	}

	if (keyboard.keyState[static_cast<int>(Keyboard::Key::eKeyH)])
	{
		_toggleHUD();
	}
}

void MainLevel::_initLevel()
{
	
	_initLevelMaterials();
	_initObjModels();
	_initLevelight();
	_initLevelShaders();
	_initMatrixMVP();
	_initText();
	
}

void MainLevel::_initLevelMaterials()
{
	Texture* targetTexture = new Texture(Texture::createTextureFromFile("res/Textures/target.png", Texture::Type::PNG));
	Texture* bulletTexture = new Texture(Texture::createTextureFromFile("res/Textures/sphere.png", Texture::Type::PNG));

	Texture* groundTexture_main = new Texture(Texture::createTextureFromFile("res/Textures/Ground/ground_8k.png", Texture::Type::PNG));
	Texture* groundTexture_normal = new Texture(Texture::createTextureFromFile("res/Textures/Ground/ground_nor8k.png", Texture::Type::NORMAL_MAP));

	_textures.push_back(targetTexture);
	_textures.push_back(bulletTexture);
	_textures.push_back(groundTexture_main);
	_textures.push_back(groundTexture_normal);

	_targetMaterialPrefab = new Material(targetTexture, nullptr, nullptr, 0, 1, glm::vec3(0.1));
	_bulletMaterialPrefab = new Material(bulletTexture, nullptr, nullptr, 0, 1, glm::vec3(0.25));
	_groundMaterialPrefab = new Material(groundTexture_main, nullptr, groundTexture_normal, 0, 1, glm::vec3(0.1));
}

void MainLevel::_initObjModels()
{
	DataOBJ targetMeshData = readObj("res/Models/target.obj");
	DataOBJ bulletMeshData = readObj("res/Models/sphere.obj");
	DataOBJ groundMeshData = readObj("res/Models/ground.obj");

	_targetMeshPrefab = new Mesh(targetMeshData, Mathf::zeroVec());
	_bulletMeshPrefab = new Mesh(bulletMeshData, Mathf::zeroVec());
	_groundMeshPrefab = new Mesh(groundMeshData, Mathf::zeroVec());

	_player = new Player(startPosition);

	GameObject* groundModel = new GameObject(new Material(*_groundMaterialPrefab), new Mesh(*_groundMeshPrefab));
	Entity* ground = new Entity(groundModel, "ground");
	ground->setScale(glm::vec3(0.2, 0.2, 0.2));
	ground->setPosition(glm::vec3(0, -4, -15));
	_ground = ground;
	
	for (int i = 0; i < targetsInstances; i++)
	{
		GameObject* model = new GameObject(new Material(*_targetMaterialPrefab), new Mesh(*_targetMeshPrefab));
		Target* entity = new Target(model, "Target " + std::to_string(i), worldRadius);
		_targets.push_back(entity);
	}
}

void MainLevel::_initLevelShaders()
{
	_fragmentShader = Shader::createShaderFromFile("shaders/map.frag", Shader::Type::eFragment);
	_vertexShader = Shader::createShaderFromFile("shaders/map.vert", Shader::Type::eVertex);

	_shaderProgram = new ShaderLightProgram();
	_shaderProgram->attachShader(_fragmentShader);
	_shaderProgram->attachShader(_vertexShader);
	_shaderProgram->linkShaderProgram();

	_updateLightShaders();


	_skybox = new Skybox(facesCubemap);

	Shader textVert = Shader::createShaderFromFile("shaders/text.vert", Shader::Type::eVertex);
	Shader textFrag = Shader::createShaderFromFile("shaders/text.frag", Shader::Type::eFragment);

	_textShader = new ShaderProgram();
	_textShader->attachShader(textVert);
	_textShader->attachShader(textFrag);
	_textShader->linkShaderProgram();
}

void MainLevel::_initMatrixMVP()
{
	_shaderProgram->useShader();
	_player->setCameraUniforms(_shaderProgram);
}

void MainLevel::_initText()
{
	_timeLabel.setColor(glm::vec3(0, 0, 0));
	_timeValueText.setColor(glm::vec3(0, 0, 0));

	_pointsLabel.setColor(glm::vec3(1, 1, 1));
	_pointsValueText.setColor(glm::vec3(1, 1, 1));

	_bulletLabel.setColor(glm::vec3(0, 1, 0));
	_bulletValueText.setColor(glm::vec3(0, 1, 0));
}

void MainLevel::_initLevelight()
{
	_Levelight = new Light::Point({ -9, 40, -25 }, { 1,1,1 });
	_Levelight->setColorLevelight({ 1,1,1 });
	_Levelight->setRange(1000);
}


void MainLevel::update(float deltaTime)
{
	_updatePlayer(deltaTime);
	_updateTargets(deltaTime);

	_updateBullet(deltaTime);

	_updateLightShaders();
	_updateGuiTexts();

	_updateOutcomes();
}

void MainLevel::_updatePlayer(float deltaTime)
{
	_player->update(deltaTime);
	_player->getStats()->reloadBullet(deltaTime);
	_player->getStats()->updateGameTime(deltaTime);
}

void MainLevel::_updateTargets(float deltaTime)
{
	for (auto target = _targets.begin(); target != _targets.end();)
	{
		(*target)->update(deltaTime);

		_collideTarget(target);
	}
}


void MainLevel::_updateBullet(float deltaTime)
{
	if (_bullet)
	{
		if (_bullet->isDead())
		{
			delete _bullet;
			_bullet = nullptr;
		}
		else
		{
			_bullet->update(deltaTime);
		}
	}
}

void MainLevel::_updateLightShaders()
{
	_shaderProgram->useShader();
	_setLightUniforms(*_shaderProgram);
}

void MainLevel::_updateGuiTexts()
{
#ifndef DIST
	PlayerStats* stats = _player->getStats();

	std::stringstream streamForTime;
	streamForTime << std::fixed << std::setprecision(2);
	streamForTime << stats->getGameTime();
	_timeValueText.setText(streamForTime.str());

	std::stringstream streamForPoints;
	streamForPoints << std::fixed << std::setprecision(4);
	streamForPoints << stats->getPoints() << "/" << targetsInstances;
	_pointsValueText.setText(streamForPoints.str());

	if (stats->canIShoot())
	{
		_bulletLabel.setText("Shoot:");
		_bulletValueText.setText("Ready");
	}
	else
	{
		std::stringstream streamForBullet;
		streamForBullet << std::fixed << std::setprecision(2);
		_bulletLabel.setText("Reloading");
		_bulletValueText.setText("");
	}
#endif
}

void MainLevel::_updateOutcomes()
{
	if (_player->getStats()->getPoints() == targetsInstances)
	{
		PlayerStats* stats = _player->getStats();
		std::stringstream streamForTime;
		streamForTime << std::fixed << std::setprecision(2);
		streamForTime << stats->getGameTime();
		_gameState->winLevel(streamForTime.str());
	}
}


void MainLevel::_collideTarget(std::vector<Target*>::iterator& target)
{
	if (glm::distance((*target)->getPosition(), Mathf::zeroVec()) > worldRadius)
	{
		(*target)->changeDirectionOnCollision();
	}

	PlayerStats* stats = _player->getStats();

	if (_bullet && !_bullet->isDead() && Mathf::areSpheresCollided(_bullet->getPosition(), _bullet->getColliderRadius(), (*target)->getPosition(), (*target)->getColliderRadius()))
	{
		Debug::Log("Collision: Bullet and " + (*target)->getName());

		(*target)->destroy();
		_bullet->destroy();

		stats->addPoint();

		target = _targets.erase(target);
		_bullet = nullptr;
	}
	else { ++target; }
}



void MainLevel::_setLightUniforms(ShaderLightProgram& shaderProgram)
{
	int playerLights = 1;
	int levelight = 1;
	int bulletLights = 0;
	if (_bullet) { bulletLights = 1; }

	shaderProgram.setNumberOfLights(levelight + playerLights + bulletLights);
	char lightIndex[20];

	sprintf_s(lightIndex, 20, "pointLights[%d].", 0);
	std::string index { lightIndex };
	shaderProgram.setLightUniforms(*(_player->getLight()), index);

	sprintf_s(lightIndex, 20, "pointLights[%d].", 1);
	std::string index2 { lightIndex };
	shaderProgram.setLightUniforms(*(this->getLight()), index2);


	if (_bullet && !_bullet->isDead())
	{
		sprintf_s(lightIndex, 20, "pointLights[%d].", 2);
		std::string index{ lightIndex };
		shaderProgram.setLightUniforms(*(_bullet->getLight()), index);
	}
}

void MainLevel::draw(float deltaTime, bool wireframe)
{
	_shaderProgram->useShader();
	_player->setCameraUniforms(_shaderProgram);

	for (int i = 0; i < _targets.size(); i++)
	{
		_targets[i]->draw(_shaderProgram);
	}

	if (_bullet && !_bullet->isDead())
	{
		_bullet->draw(_shaderProgram);
	}

	if (_ground)
	{
		_ground->draw(_shaderProgram);
	}

	_skybox->draw(_player->getCameraPosition(), _player->getDirection(), _player->getUp());
	_drawGui();
}

Light::Point* MainLevel::getLight()
{
	return _Levelight;
}

void MainLevel::_drawGui()
{
	if (_hudActivated)
	{
		_HUD.draw();
	}

#ifndef DIST
	_textShader->useShader();
	auto projection = glm::ortho(0.0f, static_cast<float>(Config::g_defaultWidth), 0.0f, static_cast<float>(Config::g_defaultHeight));
	_textShader->setMat4("MVP", projection);

	_timeLabel.render(*_textShader);
	_timeValueText.render(*_textShader);

	_pointsLabel.render(*_textShader);
	_pointsValueText.render(*_textShader);

	_bulletLabel.render(*_textShader);
	_bulletValueText.render(*_textShader);
#endif

	if (_hudChangeLatch > 0)
		_hudChangeLatch--;
}

void MainLevel::_toggleHUD()
{
	if (!(_hudChangeLatch > 0))
	{
		_hudActivated = !_hudActivated;
		_hudChangeLatch = 10;
	}
}

void MainLevel::_shootBullet()
{
	PlayerStats* stats = _player->getStats();
	if (stats->canIShoot())
	{
		_bullet = _spawnBullet();
		stats->shoot();
	}
	else
	{
		Debug::LogWarning("Bullet not ready");
	}
}

Bullet* MainLevel::_spawnBullet()
{
	GameObject* model = new GameObject(new Material(*_bulletMaterialPrefab), new Mesh(*_bulletMeshPrefab));
	Bullet* bullet = new Bullet(model, "Bullet", 7, _player);
	return bullet;
}