/////////////////////////////////////////////////////
//*-----------------------------------------------*//
//| Part of Flip It (https://www.maus-games.at)   |//
//*-----------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics           |//
//| Released under the zlib License               |//
//*-----------------------------------------------*//
/////////////////////////////////////////////////////


void FragmentMain()
{
    vec4  v4Texture     = vec4(coreTexture2D(0, v_av2TexCoord[0]).rgb, 1.0);
    vec2  v2ScreenCoord = gl_FragCoord.xy * u_v4Resolution.zw;
    float v1Intensity   = 1.2 - coreLengthSq(v2ScreenCoord - vec2(0.5)) * 1.2;
    vec4  v4Color       = vec4(u_v4Color.rgb * v1Intensity, u_v4Color.a);

    gl_FragColor = v4Texture * v4Color;
}