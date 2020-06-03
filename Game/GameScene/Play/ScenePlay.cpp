#include "ScenePlay.h"

#include "Game\Common\CSVLoader.h"
#include "Game\Common\TextManager.h"
#include "Game\Common\MyKeyBoard.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "game\GameObject\GameObjects.h"
#include "Game\GameObject\Manager\GameObjectManager.h"
#include "Game\GameObject\Enemy\Factory\EnemyFactory.h"

#include "Game\GameScene\Manager\SceneManager.h"


Scene * ScenePlay::Create()
{
	ScenePlay* scene = new ScenePlay();

	return scene;
}

ScenePlay::ScenePlay(): Scene()
{
	SetSceneName(L"ScenePlay");

	//メンバ変数の初期化
	is_drawDebugValue = false;
}

ScenePlay::~ScenePlay()
{
	Final();
}

void ScenePlay::Init()
{
	//オブジェクトの生成
	CreateObject();

	//当たり判定のグループを設定
	SetCollisionGroup();
}

void ScenePlay::Update()
{
	//カメラの更新
	FollowCamera* camera = FollowCamera::GetInstance();
	camera->Update();

	//マネージャーの更新
	GameObjectManager::GetInstance()->Update();
	CollisionManager::GetInstance()->DetectCollision();

	//キーボード
	MyKeyBoard* keyboard = MyKeyBoard::GetInstance();
	
	//Eキーが押されたらデバッグ用の値の描画フラグを反転
	if (keyboard->IsKeyMomentDown(DirectX::Keyboard::E))
	{
		is_drawDebugValue = !is_drawDebugValue;
	}

	//Escキーが押されたらゲームを終了
	if (keyboard->IsKeyMomentDown(DirectX::Keyboard::Escape))
	{
		exit(1);
	}
}

void ScenePlay::Render()
{
	//モデルの描画
	GameObjectManager::GetInstance()->Render();
}

void ScenePlay::Final()
{
	//管理しているオブジェクトの削除
	GameObjectManager::GetInstance()->DeleteAllObject();
}

void ScenePlay::SetCollisionGroup()
{
	//マネージャーに当たり判定のグループを登録
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "HITENEMY");
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "HURTENEMY");
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "CORE");
	CollisionManager::GetInstance()->AllowCollision("PLAYER", "DEFAULT");
	CollisionManager::GetInstance()->AllowCollision("WEAPON", "HURTENEMY");
	CollisionManager::GetInstance()->AllowCollision("WEAPON", "CORE");
	CollisionManager::GetInstance()->AllowCollision("HURTENEMY", "HURTENEMY");
	CollisionManager::GetInstance()->AllowCollision("HURTENEMY", "CORE");
	CollisionManager::GetInstance()->AllowCollision("HURTENEMY", "DEFAULT");
}

void ScenePlay::CreateObject()
{
	//モデル作成
	//プレイヤー
	std::unique_ptr<Player> player = std::make_unique<Player>();
	player->Initialize();
	//パーツ
	std::unique_ptr<ArmR> armR = std::make_unique<ArmR>();
	armR->Initialize();
	player->SetArmR(armR.get());
	//ライフの作成	
	std::unique_ptr<Life> life = std::make_unique<Life>(player.get());
	life->Initialize();
	//武器
	std::unique_ptr<Sword> sword = std::make_unique<Sword>(player.get());
	sword->Initialize();
	player->SetWeapon(sword.get());
	//床
	std::unique_ptr<Floor> floor = std::make_unique<Floor>();
	floor->Initialize();
	//コア
	std::unique_ptr<Core> core = std::make_unique<Core>();
	core->Initialize();
	//敵
	CSVLoader::GetInstance()->LoadEnemyData(L"Game\\Resources\\MapData\\EnemyData2.csv");
	EnemyFactory::GetInstance()->Create(player.get(),CSVLoader::GetInstance()->GetEnemyData());
	//天球
	std::unique_ptr<Skydome> skydome = std::make_unique<Skydome>();
	skydome->Initialize();


	//カメラの初期化
	//ウィンドウサイズからアスペクト比を算出する
	RECT size = ResourceManager::GetInstance()->GetDeviceResources()->GetOutputSize();

	//ビュー行列作成
	DirectX::SimpleMath::Vector3 eye(player->GetPos() + FollowCamera::GetInstance()->TARGET_TO_EYE_VEC * 4);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	//カメラの作成
	//画角
	float angle = 45.0f;
	FollowCamera::GetInstance()->Init(player.get(), angle, up);

	//マネージャーに追加
	GameObjectManager* gameObjectManager = GameObjectManager::GetInstance();
	gameObjectManager->Add(std::move(player));
	gameObjectManager->Add(std::move(life));
	gameObjectManager->Add(std::move(armR));
	gameObjectManager->Add(std::move(sword));
	gameObjectManager->Add(std::move(floor));
	gameObjectManager->Add(std::move(core));
	gameObjectManager->Add(std::move(skydome));
}