#include "ArmR.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\GameObject\Weapon\Sword\Sword.h"


//コンストラクタ
ArmR::ArmR()
{
}

//デストラクタ
ArmR::~ArmR()
{
}

//初期化
void ArmR::Initialize()
{
	//モデルの作成
	CreateModel();
}

//更新
void ArmR::Update()
{
	//武器の座標の更新
	if (m_weapon)
	{
		m_weapon->SetPos(m_pos);
		m_weapon->SetWorld(m_world);
	}
}

//描画
void ArmR::Render()
{
	//変数の準備
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	FollowCamera* camera = FollowCamera::GetInstance();

	//描画
	m_model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(),
		m_world,
		camera->GetViewMatrix(), 
		camera->GetProjMatrix());
}

//終了処理
void ArmR::Finalize()
{
}

//Jsonファイルを開く
void ArmR::ReadFile()
{
}

//衝突判定
void ArmR::OnCollision(GameObject * gameObject, Collider* designation)
{
	gameObject;
	designation;
}

//モデルの作成
void ArmR::CreateModel()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//作成
	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("ArmR"),
		*resourceManager->GetModelPath());
}
