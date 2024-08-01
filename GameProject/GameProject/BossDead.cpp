﻿#include"BossDead.h"
#include"BossIdle.h"


///<summary>
///コンストラクタ
///</summary>
BossDead::BossDead(int& InitializeModelHandle, const int beforeAnimationIndex)
    :StateBase(InitializeModelHandle, Boss::Dead, beforeAnimationIndex)
{
    //アニメーション速度の初期化
    animationSpeed = InitializeAnimationSpeed;
    //インプットマネージャーのインスタンスをもってくる
    inputManager = InputManager::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
BossDead::~BossDead()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="position">プレイヤーモデルの向き</param>
void BossDead::Update(VECTOR& modelDirection, VECTOR& position)
{
    //ステートの切り替え処理を呼ぶ
    ChangeState();

    //アニメーションの再生時間のセット
    UpdateAnimation();

    //シーンが切り替わっていればアニメーションをデタッチ
    DetachAnimation(this);

}


/// <summary>
/// ステートの切り替え処理をまとめたもの
/// </summary>
void BossDead::ChangeState()
{
    //ToDo
    //BossのAIを作るまではボタンでステートが遷移するようにしている
    if (inputManager->GetKeyPushState(InputManager::LeftStick) == InputManager::JustRelease)
    {
        //ボスの移動ステートに移行
        nextState = new BossIdle(modelhandle, this->GetAnimationIndex());
    }
    else
    {
        nextState = this;
    }
}
