# INSTALL.md — Guia de Instalação

> **Resumo**: este guia configura o ambiente de desenvolvimento, bibliotecas e partições, grava o firmware e realiza o provisionamento **SoftAP** do ESP RainMaker.

---

## 1) Pré‑requisitos
- **Arduino IDE** atualizado.
- **ESP32 core (Espressif)** instalado via Gerenciador de Placas.
- Cabos e drivers USB (CP210x/CH34x) instalados.

## 2) Bibliotecas necessárias
Instale via **Gerenciador de Bibliotecas** (ou ZIP):
-  'BLynk
- `WiFiProv`
- `Adafruit BMP085 Library` (para **BMP180**)
- `DHT sensor library`
- `LiquidCrystal_I2C`

## 3) Configuração da Placa
Ferramentas → selecione **ESP32 Dev Module** (ou sua variante) e ajuste:
- **Partition Scheme**: `RainMaker 4MB No OTA` (recomendado).
- (Opcional, 1ª gravação após mudar partição): **Erase All Flash Before Sketch Upload → All Flash Contents**.

## 4) Gravação do firmware
- Abra o sketch `.ino` do projeto.
- Clique **Upload**.
- Monitore a **Serial** (115200) para checar mensagens de boot e sensores.







