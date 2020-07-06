#pragma once

#include "Skeleton.h"

/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	�X�L�����f���N���X�B
*/
class SkinModel
{
public:
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/

	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);

	/*!
	*@brief	�{�[���������B
	*@param[in]		boneName	�{�[���̖��O�B
	*@return	���������{�[���B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}

	/*!
	*@brief	���f����`��B
	*@param[in]	viewMatrix		�J�����s��B
	*  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix ,EnRenderMode renderMode);

	/*!
	*@brief	�X�P���g���̎擾�B
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}

	/*!
	*@brief	���b�V������������B
	*@param[in] onFindMesh		���b�V�������������Ƃ��̃R�[���o�b�N�֐�
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}

	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};

	/// <summary>
/// �V���h�E���V�[�o�[�̃t���O��ݒ肷��B
/// </summary>
/// <param name="flag">true��n���ƃV���h�E���V�[�o�[�ɂȂ�</param>
/// <remarks>
/// �V���h�E���V�[�o�[�Ƃ͉e�𗎂Ƃ����I�u�W�F�N�g�̂��Ƃł��B
/// �V���h�E�L���X�^�[�ɂ���Đ������ꂽ�A�V���h�E�}�b�v�𗘗p����
/// ���g�ɉe�𗎂Ƃ��܂��B
/// �I�u�W�F�N�g���V���h�E���V�[�o�[���V���h�E�L���X�^�[�ɂȂ��Ă���ꍇ��
/// �Z���t�V���h�E(�����̉e�������ɗ�����)���s�����Ƃ��ł��܂��B
/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}

	/// <summary>
	/// �@���}�b�v�̐ݒ�B
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* srv)
	{
		m_normalMapSRV = srv;
	}

	/// <summary>
	/// �X�y�L�����}�b�v��ݒ�B
	/// </summary>
	/// <param name="srv"></param>
	void SetSpecularMap(ID3D11ShaderResourceView* srv)
	{
		m_specularMapSRV = srv;
	}
	/// <summary>
	/// ���f�����̃��C�g�̐ݒ�
	/// </summary>
	void SetLight(int i,CVector4 color)
	{
		m_light.dirLight.color[i] = color;
	}
private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�f�B���N�V�������C�g�̍쐬�B
	*/
	void InitDirectionLight();

	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);
	int R(int n) {
		return(((n - 1) / 16) + 1) * 16;
	}
private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//todo ���C�g�r���[�s��B
		CMatrix mLightProj;		//todo ���C�g�v���W�F�N�V�����s��B
		int isShadowReciever;	//todo �V���h�E���V�[�o�[�̃t���O�B
		int isHasSpecularMap;	//�X�y�L�����}�b�v����H
		int isHasNormalMap;		//�@���}�b�v��ێ����Ă���H
	};
	bool m_isShadowReciever = false;						//�V���h�E���V�[�o�[�̃t���O�B
/*!
 * @brief �f�B���N�V�������C�g
 */
	static const int LIGHT = 4;
	struct SDirectionLight {
		CVector4 direction[LIGHT];    //���C�g�̕����B
		CVector4 color[LIGHT];        //���C�g�̃J���[�B
	};
/*!
 * @brief ���C�g�p�̒萔�o�b�t�@
 */
	struct LightCb {
		SDirectionLight dirLight; //�f�B���N�V�������C�g
		CVector3		eyePos;				//�J�����̎��_�B
		float		    specPow;            //�X�y�L�������C�g�̍i��B
		CVector3        ambientLight;       //�A���r�G���g���C�g
	};
	float m_specPow = 0.5f;
	CVector4 m_color = { 1.0f,1.0f,1.0f,0.5f };
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	ID3D11Buffer*       m_lightCb = nullptr;            //!<���C�g�p�̒萔�o�b�t�@�B
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	LightCb				m_light;						//!<���C�g�\����
	SVSConstantBuffer  m_vsCb;							//!<�萔�o�b�t�@�B
	ID3D11ShaderResourceView* m_specularMapSRV = nullptr;	//�X�y�L�����}�b�v��SRV
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;		//�@���}�b�v��SRV
};