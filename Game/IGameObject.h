#pragma once
class IGameObject
{
public:
	/// <summary>
	/// 更新関数
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Render() = 0;
	/// <summary>
	/// 排除リクエスト
	/// </summary>
	void RequestDelete()
	{
		isRequestDead = true;
	}
	/// <summary>
	/// 排除リクエストを受けたか調べる。
	/// </summary>
	/// <returns>
	/// trueが帰ってきたら、リクエストを受けている。
	/// </returns>
	bool isRequestDelete()
	{
		return isRequestDead;
	}
private:
	bool isRequestDead = false;   //排除リクエスト判定用
};

