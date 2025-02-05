#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos dos LEDs e do botão
#define LED_BLUE  11 // LED azul no GPIO 11
#define LED_RED   12 // LED vermelho no GPIO 12
#define LED_GREEN 13 // LED verde no GPIO 13
#define BUTTON  5    // Botão no GPIO 5

// Estados dos LEDs
typedef enum { ALL_ON, RG_ON, G_ON, ALL_OFF } LedState;
LedState ledState = ALL_OFF;

// Controle do temporizador
absolute_time_t previousMillis;
const uint32_t interval = 3000000; // 3 segundos (em microssegundos)
bool timerRunning = false;  // Bloqueia o botão durante a execução

void checkButton();
void startLedCycle();
void manageTimer();
void turn_off_callback();

int main() {
    // Inicializa a Raspberry Pi Pico
    stdio_init_all();

    // Configuração dos pinos
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON); // Ativa resistor pull-up interno

    // Inicializa os LEDs apagados
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);

    while (1) {
        checkButton(); // Verifica se o botão foi pressionado
        manageTimer(); // Controla a sequência dos LEDs
        sleep_ms(10);  // Pequeno delay para evitar leitura excessiva
    }

    return 0;
}

// Verifica se o botão foi pressionado e inicia o ciclo dos LEDs
void checkButton() {
    if (!gpio_get(BUTTON) && !timerRunning) { // Botão pressionado (LOW)
        startLedCycle();
    }
}

// Inicia o ciclo dos LEDs e ativa o temporizador
void startLedCycle() {
    ledState = ALL_ON;
    timerRunning = true;
    previousMillis = get_absolute_time();

    // Liga todos os LEDs
    gpio_put(LED_BLUE, 1);
    gpio_put(LED_RED, 1);
    gpio_put(LED_GREEN, 1);
}

// Gerencia a transição dos LEDs com base no temporizador
void manageTimer() {
    if (timerRunning && absolute_time_diff_us(previousMillis, get_absolute_time()) >= interval) {
        previousMillis = get_absolute_time();
        turn_off_callback();
    }
}

// Callback para desligar os LEDs progressivamente
void turn_off_callback() {
    switch (ledState) {
        case ALL_ON: // Passa para estado vermelho + verde
            gpio_put(LED_BLUE, 0);
            ledState = RG_ON;
            break;

        case RG_ON: // Passa para estado apenas verde
            gpio_put(LED_RED, 0);
            ledState = G_ON;
            break;

        case G_ON: // Desliga todos os LEDs
            gpio_put(LED_GREEN, 0);
            ledState = ALL_OFF;
            timerRunning = false; // Finaliza o ciclo e libera o botão
            break;

        default:
            break;
    }
}
