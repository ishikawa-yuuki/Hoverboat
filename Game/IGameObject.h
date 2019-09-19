#pragma once
class IGameObject
{
public:
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Render() = 0;
	/// <summary>
	/// �r�����N�G�X�g
	/// </summary>
	void RequestDelete()
	{
		isRequestDead = true;
	}
	/// <summary>
	/// �r�����N�G�X�g���󂯂������ׂ�B
	/// </summary>
	/// <returns>
	/// true���A���Ă�����A���N�G�X�g���󂯂Ă���B
	/// </returns>
	bool isRequestDelete()
	{
		return isRequestDead;
	}
private:
	bool isRequestDead = false;   //�r�����N�G�X�g����p
};

