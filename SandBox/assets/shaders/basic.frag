#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform float u_time;

// Fonction de bruit pseudo-aléatoire
float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

// Fonction de bruit de Perlin simplifié
float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

// Fonction de bruit fractal (FBM - Fractional Brownian Motion)
float fbm(vec2 st) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;

    for (int i = 0; i < 6; i++) {
        value += amplitude * noise(st * frequency);
        frequency *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

// Fonction de distance SDF pour créer des formes
float sdCircle(vec2 p, float r) {
    return length(p) - r;
}

// Palette de couleurs dynamique
vec3 palette(float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b * cos(6.28318 * (c * t + d));
}

// Fonction de rotation 2D
mat2 rotate2D(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

void main() {
    // Coordonnées centrées
    vec2 uv = (vUV - 0.5) * 2.0;
    vec2 originalUV = uv;

    // Animation temporelle
    float time = u_time * 0.5;

    // === EFFET DE TUNNEL PSYCHÉDÉLIQUE ===
    float dist = length(uv);
    float angle = atan(uv.y, uv.x);

    // Transformation polaire animée
    vec2 polarUV = vec2(dist, angle);
    polarUV.x += time * 0.3;
    polarUV.y += sin(dist * 8.0 - time * 2.0) * 0.2;

    // === FRACTALES ET BRUIT ===
    vec2 noiseUV = uv * 3.0;
    noiseUV = rotate2D(time * 0.1) * noiseUV;
    float noiseValue = fbm(noiseUV + time * 0.2);

    // === ONDULATIONS CONCENTRIQUES ===
    float waves = sin(dist * 15.0 - time * 4.0) * 0.5 + 0.5;
    waves *= sin(dist * 25.0 + time * 3.0) * 0.3 + 0.7;

    // === SPIRALE GALACTIQUE ===
    float spiral = sin(angle * 6.0 + dist * 10.0 - time * 2.0);
    spiral = smoothstep(-0.2, 0.2, spiral);

    // === PLASMA ÉLECTRIQUE ===
    vec2 plasmaUV = uv * 4.0;
    float plasma = 0.0;
    plasma += sin(plasmaUV.x * 2.0 + time) * 0.5;
    plasma += sin(plasmaUV.y * 3.0 + time * 1.3) * 0.3;
    plasma += sin((plasmaUV.x + plasmaUV.y) * 1.5 + time * 0.7) * 0.4;
    plasma += sin(sqrt(plasmaUV.x * plasmaUV.x + plasmaUV.y * plasmaUV.y) * 4.0 + time * 1.8) * 0.6;
    plasma = plasma * 0.5 + 0.5;

    // === ÉTOILES SCINTILLANTES ===
    vec2 starUV = uv * 20.0;
    float stars = 0.0;
    for (int i = 0; i < 3; i++) {
        vec2 grid = fract(starUV) - 0.5;
        float starNoise = random(floor(starUV) + float(i) * 100.0);
        if (starNoise > 0.95) {
            float starBrightness = sin(time * 10.0 + starNoise * 100.0) * 0.5 + 0.5;
            stars += (1.0 - smoothstep(0.0, 0.05, length(grid))) * starBrightness;
        }
        starUV *= 1.3;
        starUV = rotate2D(0.7) * starUV;
    }

    // === VORTEX CENTRAL ===
    vec2 vortexUV = uv;
    vortexUV = rotate2D(time + dist * 2.0) * vortexUV;
    float vortex = smoothstep(0.1, 0.8, 1.0 - dist);
    vortex *= sin(dist * 20.0 - time * 5.0) * 0.5 + 0.5;

    // === COMBINAISON DES EFFETS ===
    float finalPattern = 0.0;
    finalPattern += waves * 0.3;
    finalPattern += spiral * 0.25;
    finalPattern += plasma * 0.4;
    finalPattern += noiseValue * 0.3;
    finalPattern += vortex * 0.5;
    finalPattern += stars * 2.0;

    // === DISTORSION TEMPORELLE ===
    float distortion = sin(time * 1.5 + dist * 5.0) * 0.1;
    finalPattern += distortion;

    // === PALETTE DE COULEURS DYNAMIQUE ===
    vec3 color1 = palette(finalPattern + time * 0.1);
    vec3 color2 = palette(finalPattern * 0.7 + time * 0.15 + 0.3);
    vec3 color3 = palette(finalPattern * 1.3 - time * 0.08 + 0.6);

    // Mélange des couleurs avec des poids dynamiques
    float weight1 = sin(time * 2.0 + dist * 3.0) * 0.5 + 0.5;
    float weight2 = cos(time * 1.7 + angle * 2.0) * 0.5 + 0.5;

    vec3 finalColor = mix(color1, color2, weight1);
    finalColor = mix(finalColor, color3, weight2 * 0.5);

    // === EFFETS DE POST-TRAITEMENT ===
    // Vignetage dynamique
    float vignette = 1.0 - smoothstep(0.5, 1.2, dist);
    vignette = pow(vignette, 0.5);
    finalColor *= vignette;

    // Boost de saturation
    float luminance = dot(finalColor, vec3(0.299, 0.587, 0.114));
    finalColor = mix(vec3(luminance), finalColor, 1.5);

    // Contraste et luminosité dynamiques
    finalColor = pow(finalColor, vec3(0.8));
    finalColor *= 1.2;

    // Effet de bloom
    float bloom = smoothstep(0.8, 1.0, length(finalColor));
    finalColor += bloom * 0.3;

    // Clamp pour éviter les valeurs trop élevées
    finalColor = clamp(finalColor, 0.0, 1.0);

    FragColor = vec4(finalColor, 1.0);
}