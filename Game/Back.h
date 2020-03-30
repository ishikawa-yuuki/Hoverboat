#include "GameObjectManager.h"
class Back : public IGameObject
{
public:
	Back();
	~Back();
	void Update();
	void Render();
	void Release();
private:
	SkinModel m_model;									//スキンモデル。
};

