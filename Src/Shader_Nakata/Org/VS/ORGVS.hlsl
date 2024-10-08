// VS/PS共通
#include "../../Common/VertexToPixelHeader.hlsli"

//VS
#include "../../Common/Vertex/VertexShader3DHeader.hlsli"
#include "../../Common/Vertex/VertexInputType.hlsli"


// IN
#define VERTEX_INPUT DX_MV1_VERTEX_TYPE_NMAP_1FRAME

// OUT
#define VS_OUTPUT VertexToPixelLit

cbuffer cbParam : register(b7)
{
	float4 g_light_pos[16];
}

VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT ret;
	
	// 頂点座標変換 +++++++++++++++++++++++++++++++++++++( 開始 )
	float4 lLocalPosition;
	float4 lWorldPosition;
	float4 lViewPosition;
	// float3 → float4
	lLocalPosition.xyz = VSInput.pos;
	lLocalPosition.w = 1.0f;

	// ローカル座標をワールド座標に変換(剛体)
	lWorldPosition.w = 1.0f;
	lWorldPosition.xyz = mul(lLocalPosition, g_base.localWorldMatrix);
	// ワールド座標をビュー座標に変換
	lViewPosition.w = 1.0f;
	lViewPosition.xyz = mul(lWorldPosition, g_base.viewMatrix);
	ret.vwPos.xyz = lViewPosition.xyz;
	// ビュー座標を射影座標に変換
	ret.svPos = mul(lViewPosition, g_base.projectionMatrix);
	// 頂点座標変換 +++++++++++++++++++++++++++++++++++++( 終了 )
	
	// その他、ピクセルシェーダへ引継&初期化 ++++++++++++( 開始 )
	
  // ポイントライトの強度計算
	float3 lightEffect = float3(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < 12; i++)
	{
		float3 lightPos = g_light_pos[i].xyz;
		float3 lightVec = lightPos - lWorldPosition.xyz;
		float distance = length(lightVec);
		lightVec = normalize(lightVec);

		float NdotL = max(dot(normalize(VSInput.norm), lightVec), 0.0f);
		float attenuation = 1.0f / (distance * distance);
		lightEffect += NdotL * attenuation;
	}
	
	lightEffect *= 50000.0f;

	lightEffect.x *= 0.05f;
	lightEffect.y *= 0.001f;
	
	float4 localCol = float4(0.0f, 0.0f, 0.0f, 0.0f);
	localCol = saturate(lLocalPosition.y * float4(0.0f, 0.7f, 1.0f, 1.0f));

// UV座標
	ret.uv = VSInput.uv0;

// 法線
// 法線をローカル空間からワールド空間へ変換
	ret.normal = normalize(
        mul(VSInput.norm, (float3x3) g_base.localWorldMatrix));
    	
	
	
	
  // ディフューズカラー
	ret.diffuse = float4(VSInput.diffuse.xyz / 4.0f + localCol/10.0f + lightEffect, 1.0f);
	
// ライト方向(ローカル)
	ret.lightDir = float3(0.0f, -0.0f, 0.0f);

// ライトから見た座標
	ret.lightAtPos = float3(0.0f, 0.0f, 0.0f);

// その他、ピクセルシェーダへ引継&初期化 ++++++++++++( 終了 )
    
	// 出力パラメータを返す
	return ret;
}

	//	制作者：中田
	//	他プロジェクトに持ち出し禁止！
