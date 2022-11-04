#pragma once
#include "../Base/Base.h"

class Slash :public Base {
private:
	// �摜�I�u�W�F�N�g
	CImage m_img;
	// ���]�t���O
	bool m_flip;
	// �U���ԍ�
	int m_attack_no;
public:
	//�@�R���X�g���N�^(�U�������ʒu,�U���̌���,�ǂ���̍U��������,�U�����̃��j�[�N�ԍ�)
	Slash(const CVector2D& pos, bool flip, int type, int attack_no);
	void Update();
	void Draw();
	int GetAttackNo() {
		return m_attack_no;
	}
};