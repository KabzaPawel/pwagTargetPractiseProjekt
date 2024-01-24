#pragma once
#include "../Rendering system/Model/gameObject.h"
#include "../Rendering system/Player/player.h"
#include "../Rendering system/Player/PlayerStats.h"
#include "../Rendering system/Lighting/point.h"
#include "../Rendering system/Entity/entity.h"
#include "../Rendering system/Entity/bullet.h"
#include "../Rendering system/Model/indexedDataOBJ.h"
#include "../State machine/gameState.h"

#include "../Rendering system/Skybox/skybox.h"
#include "../Entity/target.h"


class MainLevel
{
public:
	int targetsInstances = 20;
	float worldRadius = 10;
	glm::vec3 startPosition = glm::vec3(5, 3, 15);

	std::string facesCubemap[6] =
	{
		"res/Textures/Skybox/right.png",
		"res/Textures/Skybox/left.png",
		"res/Textures/Skybox/top.png",
		"res/Textures/Skybox/bottom.png",
		"res/Textures/Skybox/front.png",
		"res/Textures/Skybox/back.png"
	};

	MainLevel(GameState* gameState);
	~MainLevel();

	void input(float deltaTime, GameReference gameReference, Keyboard& keyboard, Mouse& mouse);

	void update(float deltaTime);

	void draw(float deltaTime, bool wireframe);

	Light::Point* getLight();



private:
	void _initLevel();
	void _initMatrixMVP();
	void _initLevelShaders();
	void _initLevelMaterials();
	void _initObjModels();
	void _initText();
	void _initLevelight();

	void _updatePlayer(float deltaTime);
	void _updateTargets(float deltaTime);
	void _updateBullet(float deltaTime);
	void _updateLightShaders();
	void _updateGuiTexts();
	void _updateOutcomes();

	void _collideTarget(std::vector<Target*>::iterator& target);

	void _setLightUniforms(ShaderLightProgram& shader);

	void _drawGui();
	void _toggleHUD();

	void _shootBullet();
	Bullet* _spawnBullet();

	GameState* _gameState;
	Skybox* _skybox;
	Player* _player;
	std::vector<Target*> _targets;
	Bullet* _bullet;
	Entity* _ground;
	Light::Point* _Levelight;

	ShaderLightProgram* _shaderProgram;
	Shader _vertexShader;
	Shader _fragmentShader;

	std::vector<Texture*> _textures;

	Material* _targetMaterialPrefab;
	Material* _bulletMaterialPrefab;
	Material* _groundMaterialPrefab;

	Mesh* _targetMeshPrefab;
	Mesh* _bulletMeshPrefab;
	Mesh* _groundMeshPrefab;

	Font _tmpDefaultFont;
	ShaderProgram* _textShader;

	Text _timeLabel;
	Text _timeValueText;
	Text _pointsLabel;
	Text _pointsValueText;
	Text _bulletLabel;
	Text _bulletValueText;

	Sprite _HUD;
	bool _hudActivated = true;
	int _hudChangeLatch = 0;
};