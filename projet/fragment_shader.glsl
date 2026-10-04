uniform sampler2D textureId;
varying vec3 ma_couleur;
varying vec2 ma_coordonnee_texture;
uniform int mode;

void main()
{
    vec4 textureColor = texture2D(textureId, ma_coordonnee_texture);
    vec4 baseColor = vec4(ma_couleur, 1.0);
    if( mode == 0 )
    {
        gl_FragColor = baseColor;
    }
    else
    {
        gl_FragColor = textureColor;
    }
}