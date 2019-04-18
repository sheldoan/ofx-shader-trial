uniform vec2 eyePos;
uniform sampler2DRect frame;
uniform float height;

void main() {
    vec2 posPixel = gl_FragCoord.xy;
    //posPixel.y = height - posPixel.y;
    if (sqrt(pow(posPixel.x - eyePos.x, 2.0) + pow(posPixel.y - eyePos.y, 2.0)) < 40.0) {
        gl_FragColor = vec4(texture2DRect(frame, posPixel).rgb, 1.0);
    } else {
        discard;
    }
}
