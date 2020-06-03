#include "Sword.h"

#include <fstream>
#include <istream>

#include "3rdParty\Picojson\picojson.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\Common\MyKeyBoard.h"

#include "Game\GameObject\Player\Player.h"

#include "Game\GameObjectState\Sword\SwordState.h"
#include "Game\GameObjectState\Sword\SwordStateList.h"


//定数の初期化
const DirectX::SimpleMath::Vector3 Sword::COLLIDER_ADJUSTMENT = { 0.0f, 0.0f, -1.0f };

//コンストラクタ
Sword::Sword(Player* user) : m_user(user),m_color(DirectX::Colors::Yellow)
{
}

//初期化
void Sword::Initialize()
{
	//Jsonファイルを開く
	ReadFile();

	//変数の初期化
	is_drawPrimitive = false;

	//当たり判定の作成
	m_collider = std::make_unique<Capsule>(this, 2.0f, 1.0f, false);
	m_collider->SetPos(m_user->GetPos() + COLLIDER_ADJUSTMENT);
	m_collider->SetTag(Collider::COLLIDER_TAG::SWORD);
	m_collider->SetCollide(false);

	//当たり判定の色のリセット
	m_color = DirectX::Colors::Yellow;

	//Stateをセット
	SwordState* swordState = SwordState::GetInstance();
	swordState->Add(WAIT, std::make_unique<WaitSword>(this));
	swordState->Add(ATTACK, std::make_unique<AttackSword>(this));

	//初期Stateの設定
	ChangeState(swordState->GetState(WAIT));

	//武器の作成
	CreateModel();
}

//更新
void Sword::Update()
{
	//現在の状態の更新
	m_state->Update();

	//当たり判定のマネージャーに登録
	CollisionManager::GetInstance()->Add("WEAPON", m_collider.get());

	//Eキーでプリミティブ描画フラグを反転
	if (MyKeyBoard::GetInstance()->IsKeyMomentDown(DirectX::Keyboard::E))
	{
		is_drawPrimitive = !is_drawPrimitive;
	}

	//当たり判定の更新
	m_collider->SetPos(m_user->GetPos() + COLLIDER_ADJUSTMENT);
}

//描画
void Sword::Render()
{
	//情報の取得
	FollowCamera* camera = FollowCamera::GetInstance();

	//現在の状態を描画
	m_state->Render(m_model.get());

	//当たり判定の描画
	if (is_drawPrimitive)
	{
		DirectX::SimpleMath::Matrix mat = DirectX::SimpleMath::Matrix::CreateTranslation(m_collider->GetPos());
		m_collider->Draw(mat, camera->GetViewMatrix(), camera->GetProjMatrix(), m_color);
	}
}

//終了処理
void Sword::Finalize()
{
	//現在の状態の破棄
	SwordState::GetInstance()->AllDelete();
}

//Jsonファイルを開く
void Sword::ReadFile()
{
	//ファイルの読み込み
	std::ifstream ifs("Game\\Resources\\Json\\Weapon.json");

	//失敗処理
	//assert(ifs.is_open && "file is not open");

	//変数宣言
	picojson::value value;

	//ファイルを開く
	ifs >> value;

	//データの使用
	picojson::object& root = value.get<picojson::object>();

	//情報の取得
	picojson::object sword = root["Sword"].get<picojson::object>();
	std::string parent = sword["parent"].get<std::string>();
	picojson::array pos = sword["displacement"].get<picojson::array>();
	SetSize((float)sword["size"].get<double>());
	picojson::array color = sword["color"].get<picojson::array>();
	
	//ファイルを閉じる
	ifs.close();
}

//衝突判定
void Sword::OnCollision(GameObject* gameObject, Collider* designation)
{
	//コライダーの色を変える
	if (designation->GetTag() == Collider::COLLIDER_TAG::HURTENEMY)
	{
		m_color = DirectX::Colors::Red;
	}
	gameObject;
}

//状態の切り替え
void Sword::ChangeState(IState * state)
{
	//状態の切り替え
	m_state = state;
	m_state->Initialize();
}

//攻撃
void Sword::Attack()
{
	//当たり判定を取る状態にする
	m_collider->SetCollide(true);

	//剣を振る
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
}

//攻撃状態へ
void Sword::ToAttack()
{
	//攻撃状態に
	ToAttackState();
	//当たり判定を取る状態に
	m_collider->SetCollide(true);
	//色を変える
	m_color = DirectX::Colors::Red;
	//ステートの切り替え
	ChangeState(SwordState::GetInstance()->GetState(ATTACK));
}

//待機状態へ
void Sword::ToStay()
{
	//待機状態に
	ToStayState();
	//当たり判定をとらない状態に
	m_collider->SetCollide(false);
	//色を変える
	m_color = DirectX::Colors::Blue;
	//ステートの切り替え
	ChangeState(SwordState::GetInstance()->GetState(WAIT));
}

//モデルの作成
void Sword::CreateModel()
{
	//変数の準備
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	m_model = std::make_unique<DirectX::Model>();
	
	//モデルの作成
	m_model = DirectX::Model::CreateFromCMO(
		resourceManager->GetDevice(),
		resourceManager->GetModelData("Sword"),
		*resourceManager->GetModelPath());
}