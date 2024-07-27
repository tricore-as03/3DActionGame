﻿#include"PlayerShotMagic.h"
#include"PlayerIdle.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="InitalModelHandle">モデルハンドル</param>
PlayerShotMagic::PlayerShotMagic(int InitalModelHandle, int beforeAnimationIndex)
    :StateBase(InitalModelHandle, Player::Spell, beforeAnimationIndex)
{
    //アニメーション速度の初期化
    animationSpeed = 1.0f;
}


/// <summary>
/// デストラクタ
/// </summary>
PlayerShotMagic::~PlayerShotMagic()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="position">プレイヤーモデルの向き</param>
void PlayerShotMagic::Update(VECTOR& modelDirection)
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
void PlayerShotMagic::ChangeState()
{
    //アニメーションの再生が終了したらステートを切り替える
    if (currentPlayAnimationState == FirstRoopEnd)
    {
        nextState = new PlayerIdle(modelhandle, animationIndex);
    }
    else
    {
        nextState = this;
    }
}
