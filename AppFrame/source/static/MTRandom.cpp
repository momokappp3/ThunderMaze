#include "MTRandom.h"

namespace {                        //�v���O�����̎��s���邽�ѓ����l���\�������̂�h�����߂� speed_gen
	std::random_device seed_gen;   //�����V�[�h�@�����@������CPU�̉��x�Ń����_������������̂Ɠ���
	std::mt19937_64 random(seed_gen());   //�����_�����@�����Z���k�c�C�X�^�[
}

MTRandom::MTRandom(){
}

MTRandom::~MTRandom(){
}

int MTRandom::Get(int min, int max) {

	//����a����я��b���󂯎��R���X�g���N�^�Ba�ȏ�b�ȉ�(�͈�[a, b])�̒l�����������
	std::uniform_int_distribution<int>  distr(min,max);

	return distr(random);   //min����max�܂ł̃����_��������
}

std::mt19937_64 MTRandom::GetRandom() {

	return random;
}

