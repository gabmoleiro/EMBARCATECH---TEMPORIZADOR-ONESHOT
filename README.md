# Temporizador de um disparo (One Shot) com Raspberry Pi Pico W

Este repositório contém a implementação de um sistema de temporização utilizando a placa Raspberry Pi Pico W, programado em C com o Pico SDK. O sistema aciona três LEDs a partir do clique em um botão (pushbutton), desligando-os progressivamente a cada 3 segundos, utilizando a função `add_alarm_in_ms()`.

!(imagens/diagram_temporizador.png)

## Requisitos
Para executar este projeto, é necessário:

- Raspberry Pi Pico W (ou simulação no BitDogLab)
- 3 LEDs (azul, vermelho e verde)
- 3 resistores de 330Ω
- 1 Botão (Pushbutton)
- Ambiente de desenvolvimento configurado com:
  - VS Code
  - Pico SDK
  - Simulador BitDogLab

## Configuração do Hardware
Os LEDs e o botão devem ser conectados aos GPIOs da Raspberry Pi Pico W da seguinte forma:

| Componente   | GPIO |
|-------------|------|
| LED Azul    | 11   |
| LED Vermelho | 12  |
| LED Verde   | 13   |
| Botão       | 5    |

Cada LED deve ser ligado em série com um resistor de 330Ω.

## Instalação e Execução

1. Clone este repositório:
   ```sh
   git clone https://github.com/gabmoleiro/EMBARCATECH---TEMPORIZADOR-ONESHOT.git
   cd EMBARCATECH---TEMPORIZADOR-ONESHOT
   ```
2. Configure o ambiente de desenvolvimento:
   - Instale o Pico SDK
   - Configure o VS Code para compilar códigos C para o Raspberry Pi Pico
   - Integre o simulador BitDogLab ao VS Code
3. Compile o código:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Execute a simulação no BitDogLab:
   - Abra o projeto no BitDogLab e carregue o código-fonte
   - Inicie a simulação

## Funcionamento
1. Quando o botão for pressionado, todos os LEDs serão ligados.
2. Após 3 segundos, o LED azul será desligado.
3. Após mais 3 segundos, o LED vermelho será desligado.
4. Após mais 3 segundos, o LED verde será desligado.
5. O botão só pode ser pressionado novamente após o ciclo ser concluído.


