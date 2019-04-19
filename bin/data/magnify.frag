uniform vec2 eyePos;
uniform sampler2DRect frame;
uniform float height;
uniform float radius;
uniform float scale;

void main() {
    vec2 posPixel = gl_FragCoord.xy;
    //posPixel.y = height - posPixel.y;
    float distanceFromCenter = sqrt(pow(posPixel.x - eyePos.x, 2.0) + pow(posPixel.y - eyePos.y, 2.0));
    if (distanceFromCenter < scale*radius) {
        float deltaX = posPixel.x - eyePos.x;
        float deltaY = posPixel.y - eyePos.y;
        float theta = atan(deltaY, deltaX);
        float mappedRadius = distanceFromCenter / scale;
        float mappedX = mappedRadius * cos(theta);
        float mappedY = mappedRadius * sin(theta);
        
        vec2 mappedPixel = vec2(mappedX, mappedY);
        vec3 rgb = texture2DRect(frame, mappedPixel).rgb;
        gl_FragColor = vec4(rgb, 1.0);
    } else {
        discard;
    }
}
