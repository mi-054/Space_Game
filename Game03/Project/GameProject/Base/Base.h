#pragma once
#include<GLLibrary.h>
// �d�͉����x
#define GRAVITY (9.8f/20)

enum {	// �񋓌^
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
	// ���X�g�\��
	static std::list<Base*> m_list;
	// ���W�f�[�^
	CVector2D m_pos;
	// �O�ɂ����ʒu
	CVector2D m_pos_old;
	// �ړ��x�N�g��
	CVector2D m_vec;
	// �X�N���[���l
	static CVector2D m_scroll;
	// �I�u�W�F�N�g�̎��
	int m_type;
	// �L������
	bool m_kill;


	bool m_hit;
	// ���a
	float m_rad;
	// �Z�`
	CRect m_rect;
	
	
public:
	//�~Base;�@���^�C�v��ݒ肵�Ă���̂ɓ��͂��Ȃ��ƃG���[�̌����ɂȂ�
	Base(int type);		// (�����t����)�R���X�g���N�^
	virtual ~Base();	// �f�X�g���N�^
	Base* Base::FindObject(int type);

	virtual void Update();		
	virtual void Draw();
	virtual void Collision(Base* b);	// �����蔻��
	void SetKill() { m_kill = true; }

	static void UpdateAll();
	static void DrawAll();
	static void CheckKillAll();
	// �S�ẴI�u�W�F�N�g�̓����蔻��
	static void CollisionAll();
	// �Z�`���m�̔���
	static bool CollisionRect(Base * b1, Base * b2);
	// �Z�`�̕\��
	void DrawRect();
	// �I�u�W�F�N�g�̒ǉ�
	static void Add(Base* b);
	// �S�I�u�W�F�N�g�̍폜
	static void KillAll();
	// �~���m�̏Փ�
	static bool CollisionCircle(Base* b1,Base* b2);
	static std::list<Base*>FindObjects(int type);
	static CVector2D GetScreenPos(const CVector2D& pos);
};
