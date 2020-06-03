#include "Player.h"

#include "Game\Common\ResourcesManager.h"
#include "Game\Common\MyKeyBoard.h"

#include "Game\Camera\FollowCameraClass.h"

#include "Game\Collider\Manager\CollisionManager.h"

#include "Game\GameObject\Player\Player.h"
#include "Game\GameObject\Weapon\Sword\Sword.h"
#include "Game\GameObject\Manager\GameObjectManager.h"

#include "Game\GameObjectState\Player\PlayerState.h"
#include "Game\GameObjectState\Player\PlayerStateList.h"

#include "Game\GameScene\Manager\SceneManager.h"

const DirectX::SimpleMath::Vector3 Player::ARMR_ADJUSTMENT = { 0.7f, 1.0f,0.0f };


Player::Player() : m_vel{0.0f, 0.0f, 0.0f},m_blowAwayVec{0.0f, 0.0f, 0.0f},
m_angle(0.0f),is_drawPrimitive(false),is_invincibility(false), 
m_invincibilityCount(INVINCIBLE_TIME),m_invincibleTime(INVINCIBLE_TIME)
{
}

Player::~Player()
{
}

//初期化
void Player::Initialize()
{	
	//Jsonファイルの読み込み
	ReadFile();

	//モデルの作成
	m_model = std::make_unique<DirectX::Model>();
	CreateModel();

	//ワールド行列に適用
	ApplyWorld();

	//当たり判定の作成
	m_collider = std::make_unique<Sphere>(this, 0.75f);
	m_collider->SetPos(this->GetPos());
	m_collider->SetCollide(Collider::COLLIDER_TAG::PLAYER);
	m_collider->SetCollide(true);
	m_color = DirectX::Colors::Yellow;

	//タグの設定
	SetTag(GAMEOBJECT_TAG::PLAYER);
	
	//Stateをセット
	PlayerStateClass* playerState = PlayerStateClass::GetInstance();
	playerState->Add(STANDING,std::move(std::make_unique<StandingPlayer>(this)));
	playerState->Add(WALKING, std::move(std::make_unique<WalkingPlayer>(this)));
	playerState->Add(ATTACK,  std::move(std::make_unique<AttackPlayer>(this)));
	playerState->Add(DAMAGE,  std::move(std::make_unique<GetHurtPlayer>(this)));

	//初期Stateの設定
	m_state = playerState->GetState(STANDING);

}

//更新
void Player::Update()
{
	//当たり判定の更新
	m_collider->SetPos(m_pos);

	//当たり判定のマネージャーに登録
	CollisionManager::GetInstance()->Add("PLAYER", m_collider.get());

	//HPが0になったら自壊
	if (!m_life)
	{
		//カメラのターゲットをnullに
		FollowCamera::GetInstance()->SetObject(nullptr);
		//不要状態にする
		ToParaphernalia();
		//シーン遷移
		SceneManager::GetInstance()->RequestScene(SCENE_FAILURE);
	}

	//無敵カウントの更新
	if (is_invincibility)
	{
		//カウントの更新
		m_invincibilityCount--;

		//点滅
		Flash();

		//時間が切れたら無敵と点滅解除
		if (m_invincibilityCount == 0)
		{
			is_invincibility = false;
			is_drawModel = true;
		}
	}

	//パーツの座標の更新
	m_armR->SetPos(m_pos + ARMR_ADJUSTMENT);
	m_armR->SetWorld(DirectX::SimpleMath::Matrix::CreateTranslation(ARMR_ADJUSTMENT) * m_world);

	//現在のStateの実行
	m_state->Update();

	//カメラの方向に向かせる
	FaceCamera();

	//Eキーでプリミティブ描画フラグを反転
	if (MyKeyBoard::GetInstance()->IsKeyMomentDown(DirectX::Keyboard::E))
	{
		is_drawPrimitive = !is_drawPrimitive;
	}
}

//描画
void Player::Render()
{
	//状態の描画
	if(is_drawModel)
		m_state->Render(m_model.get());

	//プリミティブの描画
	if (is_drawPrimitive)
	{
		FollowCamera* camera = FollowCamera::GetInstance();
		DirectX::SimpleMath::Matrix world = m_world * DirectX::SimpleMath::Matrix::CreateTranslation(0.0f, 1.0f, 0.0f);
		m_collider->Draw(world, camera->GetViewMatrix(), camera->GetProjMatrix(), m_color);
	}
}

//終了処理
void Player::Finalize()
{
	//ステート情報を削除
	PlayerStateClass::GetInstance()->AllDelete();
}

//Jsonファイルを開く
void Player::ReadFile()
{
	//ファイルの読み込み
	std::ifstream ifs("Game\\Resources\\Json\\Player.json");

	//失敗処理
	//assert(ifs.is_open && "file is not open");

	//変数宣言
	picojson::value value;

	//ファイルを開く
	ifs >> value;

	//データの使用
	picojson::object& root  = value.get<picojson::object>();
	
	//情報の取得
	picojson::array	 pos	= root["position"].get<picojson::array>();
	m_life					= (int)   root["life"].get<double>();
	m_size					= (float) root["size"].get<double>();
	m_pos.x					= (float) pos[0].get<double>();
	m_pos.y					= (float) pos[1].get<double>();
	m_pos.z					= (float) pos[2].get<double>();

	//ファイルを閉じる
	ifs.close();
}

//衝突時
void Player::OnCollision(GameObject* gameObject, Collider* designation)
{
	if (designation)
	{
		//敵と当たった際の衝突処理(無敵状態でないとき)
		if (designation->GetTag() == Collider::COLLIDER_TAG::HITENEMY && !is_invincibility)
		{
			//ダメージを受ける
			m_color = DirectX::Colors::Red;
			m_life--;
			//ノックバックのベクトルを作成
			KickBack(gameObject->GetPos());
			//ステートの遷移
			ChangeState(PlayerStateClass::GetInstance()->GetState(DAMAGE));
		}
	}
	gameObject;
}

void Player::ToInvincible()
{
	//無敵状態にする
	is_invincibility = true;
	//当たり判定を取らない状態にする
	m_collider->SetCollide(!is_invincibility);
}

//無敵状態解除
void Player::UnlockInvicinble()
{
	//無敵解除
	is_invincibility = false;
	//当たり判定を取る状態にする
	m_collider->SetCollide(!is_invincibility);
}

//動きの更新
void Player::Move()
{
	PlayerStateClass::GetInstance()->GetState(WALKING)->Update();
}

void Player::Flash()
{
	if (m_invincibilityCount % 10 == 0)
	{
		is_drawModel = !is_drawModel;
	}
}

//状態の切り替え
void Player::ChangeState(IState * state)
{
	m_state = state;
	m_state->Initialize();
}

//モデルの作成
void Player::CreateModel()
{
	//作成
	m_model = DirectX::Model::CreateFromCMO(
		ResourceManager::GetInstance()->GetDevice() ,
		ResourceManager::GetInstance()->GetModelData("Player"),
		*ResourceManager::GetInstance()->GetModelPath());
}

//ノックバック
void Player::KickBack(const DirectX::SimpleMath::Vector3& objPos)
{
	//自分と相手の距離を求める
	DirectX::SimpleMath::Vector3 relativePos = m_pos - objPos;
	relativePos.Normalize();

	//メンバ変数に格納
	m_blowAwayVec = relativePos;
}

//カメラの向きをプレイヤーに適用
void Player::FaceCamera()
{
	m_angle = -FollowCamera::GetInstance()->GetYAngle();
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);
}