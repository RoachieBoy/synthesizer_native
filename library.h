#ifndef SYNTHESIZER_NATIVE_LIBRARY_H
#define SYNTHESIZER_NATIVE_LIBRARY_H

#ifdef PLATFORM_WINDOWS
#   define SYMBOL_EXPORT __declspec(dllexport)
#else
#   define SYMBOL_EXPORT
#endif

typedef struct {
    float sample;
    float phase;
} sample_state_t;

SYMBOL_EXPORT sample_state_t generate_sine_sample(float frequency, float amplitude, float initialPhase, float sampleRate);

SYMBOL_EXPORT sample_state_t generate_pulse_sample(float frequency, float amplitude, float initialPhase, float sampleRate,
                                                   float volumeModifier, float dutyCycle);

SYMBOL_EXPORT sample_state_t generate_square_sample(float frequency, float amplitude, float initialPhase, float sampleRate,
                                                    float volumeModifier);

SYMBOL_EXPORT sample_state_t generate_sawtooth_sample(float frequency, float amplitude, float initialPhase, float sampleRate,
                                                    float volumeModifier);

SYMBOL_EXPORT sample_state_t generate_triangle_sample(float frequency, float amplitude, float initialPhase, float sampleRate);

#endif //SYNTHESIZER_NATIVE_LIBRARY_H
