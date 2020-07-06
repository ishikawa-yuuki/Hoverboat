#pragma once
#include <stack>

/// <summary>
/// �����_�����O���[�h�B
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
	enRenderMode_Silhouette,		//�V���G�b�g�����_�����O�B
	enRenderMode_Normal,			//�ʏ탌���_�����O�B
	enRenderMode_Num,				//�����_�����O���[�h�̐��B
};
class RenderTarget;
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();

	/// <summary>
		/// �t���[���o�b�t�@�̕����擾�B
		/// </summary>
	int GetFrameBufferWidth() const
	{
		return m_2dSpaceScreenWidth;
	}
	/// <summary>
	/// �t���[���o�b�t�@�̍������擾�B
	/// </summary>
	int GetFrameBufferHeight() const
	{
		return m_2dSpaceScreenHeight;
	}

	/// <summary>
		/// 2D��Ԃ̃X�N���[���̕����擾�B
		/// </summary>
	int Get2DSpaceScreenWidth() const
	{
		return m_2dSpaceScreenWidth;
	}
	/// <summary>
	/// 2D��Ԃ̃X�N���[���̍������擾�B
	/// </summary>
	int Get2DSpaceScreenHeight() const
	{
		return m_2dSpaceScreenHeight;
	}

	/// <summary>
		/// ���݂̃����_�����O�X�e�[�g���X�^�b�N�Ƀv�b�V���B
		/// </summary>
	void PushRenderState()
	{
		m_renderStateStack.push(m_currentRenderState);
	}
	/// <summary>
	/// �X�^�b�N�ɑޔ����������_�����O�X�e�[�g���|�b�v�B
	/// </summary>
	/// <param name="isApplyRenderState">
	/// �|�b�v���������_�����O�X�e�[�g�������_�����O�p�C�v���C���ɐݒ肷�邩�ǂ����̃t���O�B
	/// </param>
	void PopRenderState(bool isSetRenderStateToRenderPipeline)
	{
		m_currentRenderState = m_renderStateStack.top();
		m_renderStateStack.pop();
		if (isSetRenderStateToRenderPipeline == true) {
			m_pd3dDeviceContext->OMSetBlendState(m_currentRenderState.blendState, 0, 0xFFFFFFFF);
			m_pd3dDeviceContext->RSSetState(m_currentRenderState.rasterrizerState);
			m_pd3dDeviceContext->OMSetDepthStencilState(m_currentRenderState.depthStencilState, 0);
		}
	}
	//Sprite�擾
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}

	//�f�t�H���g�t�H���g�擾
	DirectX::SpriteFont* GetSpriteFont() const
	{
		return m_spriteFont.get();
	}
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ��B
	/// </summary>
	/// <param name="d3dDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
private:
	/// <summary>
		/// �e�탌���_�����O�X�e�[�g�B
		/// </summary>
	struct SRenderState {
		ID3D11DepthStencilState* depthStencilState = nullptr;	//!<���݂̃f�v�X�X�e���V���X�e�[�g�B
		ID3D11RasterizerState* rasterrizerState = nullptr;		//!<���݂̃��X�^���C�U�X�e�[�g�B
		ID3D11BlendState* blendState = nullptr;			//!<���݂̃u�����h�X�e�[�g�B

	};

	SRenderState m_currentRenderState;	//���݂̃����_�����O�X�e�[�g�B
	std::stack< SRenderState> m_renderStateStack;	//�����_�����O�X�e�[�g�̃X�^�b�N�B

	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B

	const int				m_2dSpaceScreenWidth = 1280;				//!<2D��Ԃ̃X�N���[���̕��B2D�͂��̍��W�n��O��ɕ\������Ă���΁A�𑜓x���ς���Ă����v�B
	const int				m_2dSpaceScreenHeight = 720;				//!<2D��Ԃ̃X�N���[���̍����B2D�͂��̍��W�n��O��ɕ\������Ă���΁A�𑜓x���ς���Ă����v�B
	//Sprite
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��