struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float4 OutColor : COLOR;
  float3 OutWorldPoc : POSITION;
  float3 OutNormal: NORMAL;
  float2 OutTexCoord : TEXCOORD0;
};

Texture2D Texture0 : register(t0);
SamplerState Sampler0 : register(s0);

Texture2D Texture1 : register(t1);
SamplerState Sampler1: register(s1);


cbuffer CommonConstBuf : register(b0)
{
  matrix MatrView;
  matrix MatrProj;
  float3 CamLoc;
  float Time;
};

cbuffer ConstBuffer : register(b2)
{
  /* Illumination coefficients (anbient, diffuse, specular) */
  float3 Ka;
  float Ph;
  float3 Kd;
  float Trans;
  float3 Ks;

  int IsTex0;
  int IsTex1;
};


float3 Shade(float3 P, float3 N, float2 T)
{
  // Resut color
  float3 color = float3(0, 0, 0);

  float3 V = normalize(P - CamLoc);

  //return N;// + float(1.0).xxx;
  // Ambient
  color += Ka;

  // Diffuse
  float3 LightPos = float3(0, 50, 4);
  float3 LightColor = float(1).xxx;// float3(0.8, 1, 0.9);
  float3 L = normalize(LightPos - P);

  float3 Kds = Kd;
  if (IsTex0 == 1)
    Kds = Texture0.Sample(Sampler0, T) + 0.2 * Kd;
  float nl = dot(L, N);
  color += Kds * LightColor * max(nl, 0);

  // Specular
  float3 R = normalize(reflect(V, N));

  float rl = dot(L, R);
  color += Ks * pow(max(rl, 0), Ph + 30);

  color += Ka * 0.5;

  return color;
}


float4 main(PS_INPUT input) : SV_Target
{
  return float4(Shade(input.OutWorldPoc, normalize(input.OutNormal), input.OutTexCoord), Trans);
}