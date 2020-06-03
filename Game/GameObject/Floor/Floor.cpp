#include "Floor.h"

#include "Game\Common\ResourcesManager.h"

#include "Game\Camera\FollowCameraClass.h"


Floor::Floor()
{
}

Floor::~Floor()
{
}

void Floor::Initialize()
{
	//モデルの作成
	CreateModel();

	//位置の調整
	m_pos.y = -0.1f;
}

void Floor::Update()
{
}

void Floor::Render()
{
	//変数の準備
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	//ID3D11DeviceContext* deviceContext = resourceManager->GetContext();
	const DirectX::CommonStates* commonState = resourceManager->GetCommonStates();
	//視点
	DirectX::SimpleMath::Matrix view = FollowCamera::GetInstance()->GetViewMatrix();
	//プロジェクション
	DirectX::SimpleMath::Matrix proj = FollowCamera::GetInstance()->GetProjMatrix();
	// 位置
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;
	// 移動行列
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::Identity;

	//for (int row = 0; row < MAP_ROW; row++)
	//{
	//	for (int column = 0; column < MAP_COLUMN; column++)
	//	{
	//		// 位置を計算する
	//		position = DirectX::SimpleMath::Vector3(float(column - MAP_COLUMN / 2) * FLOOR_SIZE,
	//												0.0f, float(row - MAP_ROW / 2) * FLOOR_SIZE);
	//		// 移動行列を作成する
	//		translation = DirectX::SimpleMath::Matrix::CreateTranslation(position);
	//		//モデルの描画
	//		m_model->Draw(deviceContext,
	//			*commonState,
	//			translation,
	//			view, 
	//			proj);
	//	}
	//}
	//モデルの描画
	m_model->Draw(resourceManager->GetContext(),
		*commonState, translation,
		FollowCamera::GetInstance()->GetViewMatrix(), FollowCamera::GetInstance()->GetProjMatrix());
}

void Floor::Finalize()
{

}

void Floor::ReadFile()
{

}

void Floor::OnCollision(GameObject* gameObject, Collider* designation)
{
	gameObject;
	designation;
}

void Floor::CreateModel()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Floor"),
		*resourceManager->GetModelPath());
}