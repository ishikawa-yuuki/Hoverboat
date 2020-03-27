/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
 */

cbuffer cb : register(b0){
	float4x4 mvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float4 mulColor;    //��Z�J���[
};
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
//�e�N�X�`���J���[�����̂܂ܕԂ��B
	float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
//�Z�s�A��(�Ō�Ɋ����Ē���)
	/*float4 R = 0.393f * color.r + 0.769f * color.b + 0.189f * color.b;
	float4 G = 0.349f * color.r + 0.686f * color.b + 0.168f * color.b;
	float4 B = 0.272f * color.r + 0.534f * color.b + 0.131f * color.b;
	color.r = R;
	color.g = G;
	color.b = B; 
	color /= 1.5f;*/
	return color;
}