#include "Skydome.h"

#include "Game\Common\ResourcesManager.h"


//コンストラクタ
Skydome::Skydome()
{
}

//デストラクタ
Skydome::~Skydome()
{
}

//初期化
void Skydome::Initialize()
{
	//モデルの作成
	CreateModel();
}

//更新
void Skydome::Update()
{
}

//描画
void Skydome::Render()
{
	//変数の準備
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	FollowCamera* camera = FollowCamera::GetInstance();

	//モデルの描画
	m_model->Draw(resourceManager->GetContext(),
		*resourceManager->GetCommonStates(), DirectX::SimpleMath::Matrix::Identity,
		camera->GetViewMatrix(), camera->GetProjMatrix());
}

//終了処理
void Skydome::Finalize()
{
}

//Jsonファイルを開く
void Skydome::ReadFile()
{
}

//衝突判定
void Skydome::OnCollision(GameObject * gameObject, Collider* designation)
{
	gameObject;
	designation;
}

//モデルの作成
void Skydome::CreateModel()
{
	//変数の準備
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	//モデルの作成
	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Skydome"),
		*resourceManager->GetModelPath());
}