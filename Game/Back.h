#include "GameObjectManager.h"
class Back : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Back();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Back();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render();

	void Release() {};
private:
	SkinModel m_model;									//�X�L�����f���B
};

