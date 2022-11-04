#pragma once
#include<GLLibrary.h>
// 重力加速度
#define GRAVITY (9.8f/20)

enum {	// 列挙型
	eType_Field,
	eType_Player,
	eType_Enemy,
	eType_Boy,
	eType_RBoy,
	eType_Boss,
	eType_Bullet,
	eType_Goal,
	eType_Player_Attack,
	eType_Enemy_Attack,
	eType_Effect,
	eType_UI,
	eType_Scene,
	eType_Hametu,
};

class Base {
public:
	// リスト構造
	static std::list<Base*> m_list;
	// 座標データ
	CVector2D m_pos;
	// 前にいた位置
	CVector2D m_pos_old;
	// 移動ベクトル
	CVector2D m_vec;
	// スクロール値
	static CVector2D m_scroll;
	// オブジェクトの種類
	int m_type;
	// キル判定
	bool m_kill;


	bool m_hit;
	// 半径
	float m_rad;
	// 短形
	CRect m_rect;
	
	
public:
	//×Base;　←タイプを設定しているのに入力しないとエラーの原因になる
	Base(int type);		// (引数付きの)コンストラクタ
	virtual ~Base();	// デストラクタ
	Base* Base::FindObject(int type);

	virtual void Update();		
	virtual void Draw();
	virtual void Collision(Base* b);	// 当たり判定
	void SetKill() { m_kill = true; }

	static void UpdateAll();
	static void DrawAll();
	static void CheckKillAll();
	// 全てのオブジェクトの当たり判定
	static void CollisionAll();
	// 短形同士の判定
	static bool CollisionRect(Base * b1, Base * b2);
	// 短形の表示
	void DrawRect();
	// オブジェクトの追加
	static void Add(Base* b);
	// 全オブジェクトの削除
	static void KillAll();
	// 円同士の衝突
	static bool CollisionCircle(Base* b1,Base* b2);
	static std::list<Base*>FindObjects(int type);
	static CVector2D GetScreenPos(const CVector2D& pos);
};
