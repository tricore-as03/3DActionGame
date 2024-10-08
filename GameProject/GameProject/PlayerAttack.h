﻿#pragma once
#include"StateBase.h"


class InputManager;

/// <summary>
/// プレイヤーの攻撃に関するステート
/// </summary>
class PlayerAttack :public StateBase
{
public:

    // コンボ攻撃に必要な定数のデータ型
    struct AttackData
    {
        const float ComboMoveSpeed;             // コンボ攻撃中の移動速度
        const float AttackCollisionStartTime;   // コンボ攻撃での当たり判定の作成を開始する時間
        const float AttackCollisionEndTime;     // コンボ攻撃での当たり判定の削除を開始する時間
    };

    //コンストラクタ
    PlayerAttack(int modelHandle, int beforeAnimationIndex,Player::AnimationState animationState);
    //デストラクタ
    ~PlayerAttack();

    ///////   メンバ関数   //////

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="modelDirection">モデルの向き</param>
    /// <param name="characterPosition">キャラクターの座標</param>
    void Update(VECTOR& modelDirection, VECTOR& position,const VECTOR playerTargetPosition, VECTOR cameraPosition)override;

    /// <summary>
    /// ステートの切り替え処理をまとめたもの
    /// </summary>
    void ChangeState()override;



private:

    ///////     enum     ////////

    /// <summary>
    /// 連続攻撃の状態
    /// </summary>
    enum ComboState
    {
        First  = 0,  // 一撃目
        Second = 1,  // 二撃目
        Third  = 2,  // 三撃目
        End    = 3,  // コンボ終了
    };

    enum ComboCollisionState
    {
        FirstStart  = 0,
        FirstEnd    = 1,
        SecondStart = 2,
        SecondEnd   = 3,
        ThirdStart  = 4,
        ThirdEnd    = 5,
    };


    ///////  定数  ///////

    static constexpr float  NormalAttackCollisionCapsuleLineLength   = 15.0f;  // 通常攻撃の当たり判定のカプセルの半分の長さ
    static constexpr float  NormalAttackCollisionRadius              = 12.0f;  // 通常攻撃の当たり判定のカプセルの半径
    static const     VECTOR NormalAttackOffsetPositionY;                       // 通常攻撃のプレイヤーと攻撃の当たり判定座標がどれだけずれているか
    static constexpr float  NormalAttackOffsetPositionScale          = 18.0f;  // 通常攻撃のプレイヤーとどれだけ離すかの大きさ
    static constexpr int    NormalAttackCollisionCapsuleAngle        = -30;    // 通常攻撃の当たり判定用カプセルの回転角度
    static constexpr float  NormalAttackCollisionStartAnimationRatio = 0.3;    // 当たり判定を始めるアニメーションの再生率
    static constexpr int    NormalAttackDamageAmount                 = 2;      // 通常攻撃の与えるダメージ量
    static constexpr float  StrongAttackCollisionCapsuleLineLength   = 15.0f;  // 強攻撃の当たり判定のカプセルの半分の長さ
    static constexpr float  StrongAttackCollisionRadius              = 15.0f;  // 強攻撃の当たり判定のカプセルの半径
    static const     VECTOR StrongAttackOffsetPositionY;                       // 強攻撃のプレイヤーと攻撃の当たり判定座標がどれだけずれているか
    static constexpr float  StrongAttackOffsetPositionScale          = 18.0f;  // 強攻撃のプレイヤーとどれだけ離すかの大きさ
    static constexpr int    StrongAttackCollisionCapsuleAngle        = 0;      // 強攻撃の当たり判定用カプセルの回転角度
    static constexpr float  StrongAttackCollisionStartAnimationRatio = 0.3;    // 強攻撃の当たり判定を始めるアニメーションの再生率
    static constexpr int    StrongAttackDamageAmount                 = 1;      // 強攻撃の与えるダメージ量
    static constexpr int    MaxComboCount                            = 3;      // コンボ攻撃の最大回数 
    static constexpr float  InputTimeLimit                           = 0.1f;   // コンボ中の入力可能な時間
    static constexpr float  SecondAttackInputStartTime               = 0.2f;   // ２撃目の入力を開始する時間
    static constexpr float  ThirdAttackInputStartTime                = 0.53f;  // ３撃目の入力を開始する時間
    static constexpr AttackData ComboAttackData[MaxComboCount]       = { { 0.15f ,0.2f  ,0.2f },    // コンボ攻撃に必要なデータの初期化
                                                                         { 0.4f  ,0.49f ,0.55f},
                                                                         { 0.5f  ,0.75f ,0.84f}};




    //////           変数            ///////

    float  collisionCapsuleLineLength;       // 当たり判定カプセルの長さ
    float  collisionRadius;                  // 当たり判定のカプセルの半径
    float  collisionCapsuleAngle;            // 当たり判定の回転角度
    float  collisionStratAnimationRatio;     // 当たり判定を設定するアニメーションの再生率
    VECTOR offsetPosition;                   // 当たり判定をプレイヤーの座標からどれだけ動かすか
    float  offsetPositionScale;              // 当たり判定をモデルの向きにどれだけ進めるか
    int    damageAmount;
    float  moveSpeed;                        // 移動速度
    


    ///////         変数         ///////

    VECTOR                 position;                      // 攻撃の当たり判定の座標
    CollisionData          collisionData;                 // 当たり判定に必要な情報をまとめたもの
    CollisionManager*      collisionManager;              // 当たり判定の管理クラスのポインタ
    InputManager*          inputManager;                  // インプットマネージャーのポインタ
    Player::AnimationState currentAttackState;            // プレイヤーの攻撃の種類
    ComboState             currentComboState;             // コンボ攻撃の状態
    ComboCollisionState    currentComboCollisionState;    // コンボ中の当たり判定の状態


    //////  メンバ関数  //////

    /// <summary>
    /// 座標などを当たり判定に必要なデータに変換
    /// </summary>
    void UpdateCollisionData(const VECTOR& modelDirection, const VECTOR characterPosition);

    /// <summary>
    /// 当たった時の処理
    /// </summary>
    void OnHit(CollisionData collisionData);

    /// <summary>
    /// コンボ攻撃を続けるか調べて実行する
    /// </summary>
    void IsComboAttackActive();

    /// <summary>
    /// 移動する量の計算
    /// </summary>
    /// <param name="modelDirection">モデルの向いている方向</param>
    void CalculateVelocity(const VECTOR modelDirection);

    /// <summary>
    /// アニメーションの再生率に合わせて当たり判定の状態を更新する
    /// </summary>
    void UpdateCollisionStateByAnimationRatio();

#ifdef _DEBUG
    /// <summary>
    /// 当たり判定を描画する(デバッグ用)
    /// </summary>
    void DrawCollision() override;
#endif 




};
