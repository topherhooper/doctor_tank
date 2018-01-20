#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include <pigpio/pigpiod_if2.h>

static constexpr float F = 174.61;
static constexpr float G = 196.0;
static constexpr float A = 220.0;
static constexpr float Bb = 233.08;
static constexpr float C = 261.63;
static constexpr float D = 293.66;
static constexpr float E = 329.63;
static constexpr float F_HI = 349.23;

static constexpr uint32_t MICROS_PER_SECOND = 1000000;

std::vector<pigpio::gpioPulse_t> createSquarePulse(float hz, uint32_t gpio) {
    // Create pulses vector
    float period = MICROS_PER_SECOND / hz;
    float halfPeriod = period / 2;
    std::vector<pigpio::gpioPulse_t> pulses(2);
    pulses[0].gpioOn = 1 << gpio;
    pulses[0].gpioOff = 0;
    pulses[0].usDelay = halfPeriod;
    pulses[1].gpioOn = 0;
    pulses[1].gpioOff = 1 << gpio;
    pulses[1].usDelay = halfPeriod;
    return pulses;
    
    pigpio::gpioPulse_t* pPulse = &pulses[0];
}

int createSquareWave(int pi, std::vector<pigpio::gpioPulse_t>& pulses) {
    pigpio::wave_add_generic(pi, pulses.size(), &pulses[0]);
    return pigpio::wave_create(pi);
}

int main(int argc, char** argv) {
    // Initialize
    constexpr int GPIO = 19;
    int pi = pigpio::pigpio_start(nullptr, nullptr);
    if (pigpio::set_mode(pi, GPIO, PI_OUTPUT)) {
        return 1;
    }
    
    // Create scale
    auto pulseF = createSquarePulse(F, GPIO);
    auto waveF = createSquareWave(pi, pulseF);
    
    auto pulseG = createSquarePulse(G, GPIO);
    auto waveG = createSquareWave(pi, pulseG);
    
    auto pulseA = createSquarePulse(A, GPIO);
    auto waveA = createSquareWave(pi, pulseA);
    
    auto pulseBb = createSquarePulse(Bb, GPIO);
    auto waveBb = createSquareWave(pi, pulseBb);
    
    auto pulseC = createSquarePulse(C, GPIO);
    auto waveC = createSquareWave(pi, pulseC);
    
    auto pulseD = createSquarePulse(D, GPIO);
    auto waveD = createSquareWave(pi, pulseD);
    
    auto pulseE = createSquarePulse(E, GPIO);
    auto waveE = createSquareWave(pi, pulseE);
    
    auto pulseFHI = createSquarePulse(F_HI, GPIO);
    auto waveFHI = createSquareWave(pi, pulseFHI);

    std::vector<int> scale{
            waveF,
            waveG,
            waveA,
            waveBb,
            waveC,
            waveD,
            waveE,
            waveFHI};

    for (const auto& note : scale) {
        pigpio::wave_send_repeat(pi, note);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    pigpio::wave_tx_stop(pi);
    pigpio::wave_clear(pi);
}
