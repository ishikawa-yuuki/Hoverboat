/*!
 * @brief	�T�E���h�G���W��
 */

#include "stdafx.h"
#include "SoundEngine.h"
#include "WaveFile.h"
#include "SoundSource.h"

CSoundEngine* g_soundEngine = nullptr;

#define NUM_PRESETS 30

namespace {
	//�}�C�N���\�t�g�̃T���v��������������Ă����T�E���h�R�[���B
	// Specify sound cone to add directionality to listener for artistic effect:
	// Emitters behind the listener are defined here to be more attenuated,
	// have a lower LPF cutoff frequency,
	// yet have a slightly higher reverb send level.
	static const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI * 5.0f / 6.0f, X3DAUDIO_PI * 11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };

	// Specify LFE level distance curve such that it rolls off much sooner than
	// all non-LFE channels, making use of the subwoofer more dramatic.
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)& Emitter_LFE_CurvePoints[0], 3 };

	// Specify reverb send level distance curve such that reverb send increases
	// slightly with distance before rolling off to silence.
	// With the direct channels being increasingly attenuated with distance,
	// this has the effect of increasing the reverb-to-direct sound ratio,
	// reinforcing the perception of distance.
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)& Emitter_Reverb_CurvePoints[0], 3 };

	XAUDIO2FX_REVERB_I3DL2_PARAMETERS PRESET_PARAMS[NUM_PRESETS] =
	{
		XAUDIO2FX_I3DL2_PRESET_FOREST,
		XAUDIO2FX_I3DL2_PRESET_DEFAULT,
		XAUDIO2FX_I3DL2_PRESET_GENERIC,
		XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
		XAUDIO2FX_I3DL2_PRESET_ROOM,
		XAUDIO2FX_I3DL2_PRESET_BATHROOM,
		XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
		XAUDIO2FX_I3DL2_PRESET_STONEROOM,
		XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
		XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
		XAUDIO2FX_I3DL2_PRESET_CAVE,
		XAUDIO2FX_I3DL2_PRESET_ARENA,
		XAUDIO2FX_I3DL2_PRESET_HANGAR,
		XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
		XAUDIO2FX_I3DL2_PRESET_HALLWAY,
		XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
		XAUDIO2FX_I3DL2_PRESET_ALLEY,
		XAUDIO2FX_I3DL2_PRESET_CITY,
		XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
		XAUDIO2FX_I3DL2_PRESET_QUARRY,
		XAUDIO2FX_I3DL2_PRESET_PLAIN,
		XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
		XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
		XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
		XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
		XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
		XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
		XAUDIO2FX_I3DL2_PRESET_PLATE,
	};
}
/*!
	* @brief	�R���X�g���N�^�B
	*/
CSoundEngine::CSoundEngine()
{
	g_soundEngine = this;
}
/*!
	* @brief	�f�X�g���N�^�B
	*/
CSoundEngine::~CSoundEngine()
{
	Release();
}
/*!
	* @brief	�������B
	*/
void CSoundEngine::Init()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	unsigned int flags = 0;

	//XAUDIO2���������B
	HRESULT hr;
	if (FAILED(hr = XAudio2Create(&m_xAudio2, flags)))
	{
		return;
	}
	//�}�X�^�[�{�����[���̍쐬�B
	if (FAILED(hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice)))
	{
		Release();
		return;
	}

	XAUDIO2_VOICE_DETAILS voiceDetails;
	m_masteringVoice->GetVoiceDetails(&voiceDetails);
	m_masteringVoice->GetChannelMask(&m_channelMask);

	m_nChannels = voiceDetails.InputChannels;

	//���o�[�u�G�t�F�N�g���쐬�B
	flags = 0;

	if (FAILED(hr = XAudio2CreateReverb(&m_reverbEffect, flags))) {
		Release();
		return;
	}
	//�T�u�~�b�N�X�{�C�X���쐬�B
	XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { m_reverbEffect, TRUE, 1 } };
	XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

	if (FAILED(hr = m_xAudio2->CreateSubmixVoice(&m_submixVoice, voiceDetails.InputChannels,
		voiceDetails.InputSampleRate, 0, 0,
		NULL, &effectChain)))
	{
		Release();
		return;
	}
	//�f�t�H���g��FX�p�����[�^��ݒ�B
	XAUDIO2FX_REVERB_PARAMETERS native;
	ReverbConvertI3DL2ToNative(&PRESET_PARAMS[0], &native);
	m_submixVoice->SetEffectParameters(0, &native, sizeof(native));


	//�����������B
	m_isInited = true;
}
/*!
	* @brief	�J���B
	*/
void CSoundEngine::Release()
{
	//�g�`�f�[�^�o���N������B
	m_waveFileBank.ReleaseAll();

	if (m_submixVoice != nullptr) {
		m_submixVoice->DestroyVoice();
		m_submixVoice = nullptr;
	}
	if (m_reverbEffect != nullptr) {
		m_reverbEffect->Release();
		m_reverbEffect = nullptr;
	}
	if (m_masteringVoice != nullptr) {
		m_masteringVoice->DestroyVoice();
		m_masteringVoice = nullptr;
	}
	if (m_xAudio2 != nullptr) {
		m_xAudio2->Release();
		m_xAudio2 = nullptr;
	}


	CoUninitialize();
}
/*!
* @brief	XAudio2�̃\�[�X�{�C�X���쐬�B
*/
IXAudio2SourceVoice* CSoundEngine::CreateXAudio2SourceVoice(CWaveFile* waveFile, bool is3DSound)
{
	IXAudio2SourceVoice* pSourceVoice;

	//�\�[�X�{�C�X�̑����B
	if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat())))
	{
		return nullptr;
	}
	return pSourceVoice;
}

void CSoundEngine::Update()
{
	if (!m_isInited) {
		return;
	}

	//�T�E���h�\�[�X�̍X�V�B
	auto it = m_soundSources.begin();
	while (it != m_soundSources.end()) {

		auto soundSource = *it;
		soundSource->Update();
		if (soundSource->IsPlaying() == false) {
			//�Đ��I���B
			it = RemoveSoundSource(*it);
		}
		else {
			it++;
		}
	}
}