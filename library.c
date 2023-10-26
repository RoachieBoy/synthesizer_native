#include "library.h"
#include <math.h>

#define PI 3.141592653589793238462643383279502884f

static float ping_pong(float value, float max) {
    float modulated = fmodf(value, 2 * max);
    if (modulated > max) {
        return 2 * max - modulated;
    } else {
        return modulated;
    }
}

sample_state_t generate_sine_sample(float frequency, float amplitude, float initialPhase, float sampleRate) {
    float phaseIncrement = frequency / sampleRate;
    float sample = amplitude * sinf(initialPhase * 2 * PI);

    sample *= amplitude;

    initialPhase += phaseIncrement;
    initialPhase = fmodf(initialPhase, 1);

    return (sample_state_t) {sample, initialPhase};
}

sample_state_t generate_pulse_sample(
        float frequency,
        float amplitude,
        float initialPhase,
        float sampleRate,
        float volumeModifier,
        float dutyCycle) {

    float phaseIncrement = frequency / sampleRate;

    amplitude *= volumeModifier;

    float sample = initialPhase < dutyCycle ? amplitude : -amplitude;

    initialPhase += phaseIncrement;
    initialPhase = fmodf(initialPhase, 1);

    return (sample_state_t) {sample, initialPhase};
}

sample_state_t generate_square_sample(
        float frequency,
        float amplitude,
        float initialPhase,
        float sampleRate,
        float volumeModifier) {

    float phaseIncrement = frequency / sampleRate;

    amplitude *= volumeModifier;

    // use sign of sin to determine square wave
    float sample = amplitude * sinf(initialPhase * 2 * PI) > 0 ? amplitude : -amplitude;

    initialPhase += phaseIncrement;
    initialPhase = fmodf(initialPhase, 1);

    return (sample_state_t) {sample, initialPhase};
}

sample_state_t generate_sawtooth_sample(
        float frequency,
        float amplitude,
        float initialPhase,
        float sampleRate,
        float volumeModifier) {

    float phaseIncrement = frequency / sampleRate;

    amplitude *= volumeModifier;

    float sample = (initialPhase + 0.5f);
    sample = fmodf(sample, 1) * amplitude;

    initialPhase += phaseIncrement;
    initialPhase = fmodf(initialPhase, 1);

    return (sample_state_t) {sample, initialPhase};
}

sample_state_t generate_triangle_sample(float frequency, float amplitude, float initialPhase, float sampleRate){
    float phaseIncrement = frequency / sampleRate;

    float sample = ping_pong(initialPhase * 2, 1);

    sample *= amplitude;

    initialPhase += phaseIncrement;
    initialPhase = fmodf(initialPhase, 1);

    return (sample_state_t) {sample, initialPhase};
}
