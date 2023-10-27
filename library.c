#include "library.h"
#include <math.h>

#define PI 3.141592653589793238462643383279502884f

/// \brief Ping-pong a value between 0 and max
/// \param value the value to ping-pong
/// \param max the maximum value that can be returned
/// \return a float between 0 and max that is the ping-ponged value
static float ping_pong(float value, float max) {
    float modulated = fmodf(value, 2 * 1.0);

    if (modulated > 1.0) {
        return 2 * 1.0 - modulated;
    } else {
        return modulated;
    }
}

/// \brief Calculate the updated phase
/// \param initialPhase the initial phase of the wave
/// \param phaseIncrement the increment to increase the phase by
/// \return a float value representing the updated phase
static float calculate_updated_phase(float initialPhase, float phaseIncrement) {
    float updatedPhase = initialPhase + phaseIncrement;
    updatedPhase = fmodf(updatedPhase, 1);
    return updatedPhase;
}

/// \brief Generate a sine wave sample
/// \param frequency the frequency of the wave in Hz
/// \param amplitude the amplitude of the wave
/// \param initialPhase the initial phase that the wave begins at
/// \param sampleRate the sample rate of the output audio (defaults to system sample rate)
/// \return sample_state_t struct containing the sample and the updated phase
sample_state_t generate_sine_sample(float frequency, float amplitude, float initialPhase, float sampleRate) {
    float phaseIncrement = frequency / sampleRate;
    float sample = amplitude * sinf(initialPhase * 2 * PI);

    sample *= amplitude;

    calculate_updated_phase(initialPhase, phaseIncrement);

    return (sample_state_t) {sample, initialPhase};
}

/// \brief Generate a pulse wave sample
/// \param frequency the frequency of the wave in Hz
/// \param amplitude the amplitude of the wave
/// \param initialPhase the initial phase that the wave begins at
/// \param sampleRate the sample rate of the output audio (defaults to system sample rate)
/// \param volumeModifier used for louder waves to prevent different volumes between waves
/// \param dutyCycle the duty cycle of the wave (defaults to 0.5)
/// \return sample_state_t struct containing the sample and the updated phase
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

    calculate_updated_phase(initialPhase, phaseIncrement);

    return (sample_state_t) {sample, initialPhase};
}

/// \brief Generate a square wave sample
/// \param frequency the frequency of the wave in Hz
/// \param amplitude the amplitude of the wave
/// \param initialPhase the initial phase that the wave begins at
/// \param sampleRate the sample rate of the output audio (defaults to system sample rate)
/// \param volumeModifier used for louder waves to prevent different volumes between waves
/// \return sample_state_t struct containing the sample and the updated phase
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

    calculate_updated_phase(initialPhase, phaseIncrement);

    return (sample_state_t) {sample, initialPhase};
}

/// \brief Generate a sawtooth wave sample
/// \param frequency the frequency of the wave in Hz
/// \param amplitude the amplitude of the wave
/// \param initialPhase the initial phase that the wave begins at
/// \param sampleRate the sample rate of the output audio (defaults to system sample rate)
/// \param volumeModifier used for louder waves to prevent different volumes between waves
/// \return a sample_state_t struct containing the sample and the updated phase
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

    calculate_updated_phase(initialPhase, phaseIncrement);

    return (sample_state_t) {sample, initialPhase};
}

/// \brief Generate a triangle wave sample
/// \param frequency the frequency of the wave in Hz
/// \param amplitude the amplitude of the wave
/// \param initialPhase the initial phase that the wave begins at
/// \param sampleRate the sample rate of the output audio (defaults to system sample rate)
/// \return a sample_state_t struct containing the sample and the updated phase
sample_state_t generate_triangle_sample(float frequency, float amplitude, float initialPhase, float sampleRate){
    float phaseIncrement = frequency / sampleRate;

    float sample = ping_pong(initialPhase * 2, 1);

    sample *= amplitude;

    calculate_updated_phase(initialPhase, phaseIncrement);

    return (sample_state_t) {sample, initialPhase};
}
