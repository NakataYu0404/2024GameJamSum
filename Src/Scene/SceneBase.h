#pragma once
class ResourceManager;

class SceneBase
{

public:

	//	�R���X�g���N�^
	SceneBase(void);

	//	�f�X�g���N�^
	virtual ~SceneBase(void) = 0;

	//	����������
	virtual void Init(void) = 0;

	//	�X�V�X�e�b�v
	virtual void Update(void) = 0;

	//	�`�揈��
	virtual void Draw(void);

protected:

	virtual void Draw3D(void) = 0;
	virtual void Draw2D(void) = 0;
	virtual void DrawUI(void) = 0;

	//	���\�[�X�Ǘ�
	ResourceManager& resMng_;

};
