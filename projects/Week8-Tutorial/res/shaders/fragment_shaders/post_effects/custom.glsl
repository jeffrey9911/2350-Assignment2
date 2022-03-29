#version 430

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec3 outColor;

uniform layout(binding = 0) sampler2D s_Image;
uniform layout(binding = 1) sampler2D s_bright;

uniform float u_multiplier;
uniform float u_brightLim;
uniform float u_exposure;
uniform float u_gamma;

uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
    vec3 calcColor = vec3(0);
    calcColor = texture(s_Image, inUV).rgb;

    float brightness = dot(calcColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    vec4 brightColor = vec4(calcColor.rgb, 1.0);
    vec3 result = calcColor;


    if(brightness > u_brightLim)
    {
        brightColor = vec4(calcColor.rgb * u_multiplier, 1.0);

        vec2 tex_offset = 1.0 / textureSize(s_Image, 0); // gets size of single texel
        brightColor *= weight[0]; // current fragment's contribution

        for(int i = 1; i < 5; ++i)
        {
            result += texture(s_Image, inUV + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(s_Image, inUV - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }

    }
    
    vec3 outputColor = vec3(1.0) - exp(-brightColor.rgb * u_exposure);
    outputColor = pow(outputColor, vec3(1.0 / u_gamma));
    
    

    outColor = outputColor;

}
