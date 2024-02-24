/**
*   Código do projeto final (Módulo 5) de Arquitetura de Computadores do 11º Ano
*
*   Desenvolvido por:
*       - Daniel Nunes - I190044
*       - Maria Brazuna - I190051
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int nJogo = 0;
LiquidCrystal_I2C lcd(0x27,16,2);

// Menu
int jogoAEscolher = 1;
int const BtnEsquerda = 2, BtnSelecionar = 3, BtnDireita = 4;
int BtnEsquerdaState = 0, BtnSelecionarState = 0, BtnDireitaState = 0;

// JOGO 1 - Cofre
int rand1 = 0, rand2 = 0, rand3 = 0, rand4 = 0;
int acertos[4] = {0, 0, 0, 0};
int const LED1r = A0, LED1g = A2, LED1b = A1;
int const LED2r = A3, LED2g = A5, LED2b = A4;
int const LED3r = A6, LED3g = A8, LED3b = A7;
int const LED4r = A9, LED4g = A11, LED4b = A10;
int const Roda1 = A12, Roda2 = A13, Roda3 = A14, Roda4 = A15;
int BtnVerificarState = 0;

// JOGO 2 - Clique rápido
int const Tempo1A = 31, Tempo1B = 32, Tempo1C = 33, Tempo1D = 34, Tempo1E = 35, Tempo1F = 36, Tempo1G = 37;
int const Tempo2A = 24, Tempo2B = 25, Tempo2C = 26, Tempo2D = 27, Tempo2E = 28, Tempo2F = 29, Tempo2G = 30;
int const BtnClique = 23;
int BtnCliqueState = 0;
int cliques = 0, millisTempo = 0;
int tempoPassado = 0, dezenas = 0, unidades = 0;

// JOGO 3 - Martelo
int btnNumber = 0, randomBtn = 0;
int const Btn1 = 44, Btn2 = 42, Btn3 = 40, Btn4 = 38, Btn5 = 45, Btn6 = 43, Btn7 = 41, Btn8 = 39;
int const NumeroA = 5, NumeroB = 6, NumeroC = 7, NumeroD = 8, NumeroE = 9, NumeroF = 10, NumeroG = 11;
int const btnMulti = 12;
int points = 0, generateNew = 1;

byte const Numeros[10][7] = {
  { 0, 0, 0, 0, 0, 0, 1 },  // 0
  { 1, 0, 0, 1, 1, 1, 1 },  // 1
  { 0, 0, 1, 0, 0, 1, 0 },  // 2
  { 0, 0, 0, 0, 1, 1, 0 },  // 3
  { 1, 0, 0, 1, 1, 0, 0 },  // 4
  { 0, 1, 0, 0, 1, 0, 0 },  // 5
  { 0, 1, 0, 0, 0, 0, 0 },  // 6
  { 0, 0, 0, 1, 1, 1, 1 },  // 7
  { 0, 0, 0, 0, 0, 0, 0 },  // 8
  { 0, 0, 0, 0, 1, 0, 0 }   // 9
};

void setup()
{
  // Menu
  pinMode(BtnEsquerda, INPUT_PULLUP);
  pinMode(BtnSelecionar, INPUT_PULLUP);
  pinMode(BtnDireita, INPUT_PULLUP);

  // JOGO 1 - Cofre
  pinMode(LED1r, OUTPUT);
  pinMode(LED1g, OUTPUT);
  pinMode(LED1b, OUTPUT);
  pinMode(LED2r, OUTPUT);
  pinMode(LED2g, OUTPUT);
  pinMode(LED2b, OUTPUT);
  pinMode(LED3r, OUTPUT);
  pinMode(LED3g, OUTPUT);
  pinMode(LED3b, OUTPUT);
  pinMode(LED4r, OUTPUT);
  pinMode(LED4g, OUTPUT);
  pinMode(LED4b, OUTPUT);
  pinMode(LED4r, OUTPUT);
  pinMode(LED4g, OUTPUT);
  pinMode(LED4b, OUTPUT);
  pinMode(Roda1, INPUT);
  pinMode(Roda2, INPUT);
  pinMode(Roda3, INPUT);
  pinMode(Roda4, INPUT);

  // JOGO 2 - Clique rápido
  pinMode(BtnClique, INPUT_PULLUP);
  pinMode(Tempo1A, OUTPUT);
  pinMode(Tempo1B, OUTPUT);
  pinMode(Tempo1C, OUTPUT);
  pinMode(Tempo1D, OUTPUT);
  pinMode(Tempo1E, OUTPUT);
  pinMode(Tempo1F, OUTPUT);
  pinMode(Tempo1G, OUTPUT);
  pinMode(Tempo2A, OUTPUT);
  pinMode(Tempo2B, OUTPUT);
  pinMode(Tempo2C, OUTPUT);
  pinMode(Tempo2D, OUTPUT);
  pinMode(Tempo2E, OUTPUT);
  pinMode(Tempo2F, OUTPUT);
  pinMode(Tempo2G, OUTPUT);
  digitalWrite(Tempo1A, HIGH);
  digitalWrite(Tempo1B, HIGH);
  digitalWrite(Tempo1C, HIGH);
  digitalWrite(Tempo1D, HIGH);
  digitalWrite(Tempo1E, HIGH);
  digitalWrite(Tempo1F, HIGH);
  digitalWrite(Tempo1G, HIGH);
  digitalWrite(Tempo2A, HIGH);
  digitalWrite(Tempo2B, HIGH);
  digitalWrite(Tempo2C, HIGH);
  digitalWrite(Tempo2D, HIGH);
  digitalWrite(Tempo2E, HIGH);
  digitalWrite(Tempo2F, HIGH);
  digitalWrite(Tempo2G, HIGH);
  
  // JOGO 3 - Martelo
  pinMode(btnMulti, INPUT_PULLUP);
  pinMode(Btn1, INPUT_PULLUP);
  pinMode(Btn2, INPUT_PULLUP);
  pinMode(Btn3, INPUT_PULLUP);
  pinMode(Btn4, INPUT_PULLUP);
  pinMode(Btn5, INPUT_PULLUP);
  pinMode(Btn6, INPUT_PULLUP);
  pinMode(Btn7, INPUT_PULLUP);
  pinMode(Btn8, INPUT_PULLUP);
  pinMode(NumeroA, OUTPUT);
  pinMode(NumeroB, OUTPUT);
  pinMode(NumeroC, OUTPUT);
  pinMode(NumeroD, OUTPUT);
  pinMode(NumeroE, OUTPUT);
  pinMode(NumeroF, OUTPUT);
  pinMode(NumeroG, OUTPUT);
  digitalWrite(NumeroA, HIGH);
  digitalWrite(NumeroB, HIGH);
  digitalWrite(NumeroC, HIGH);
  digitalWrite(NumeroD, HIGH);
  digitalWrite(NumeroE, HIGH);
  digitalWrite(NumeroF, HIGH);
  digitalWrite(NumeroG, HIGH);

  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop()
{
  if (nJogo == 0)
  {
    lcdClean();
    lcd.setCursor(0, 0);
    lcd.print("Escolha um jogo:");
    for ( ; ; )
    {
      lcd.setCursor(0, 1);
      lcd.print("        ");
      lcd.print(jogoAEscolher);
      if (digitalRead(BtnEsquerda) == LOW && BtnEsquerdaState == 0)
      {
        BtnEsquerdaState = 1;
        jogoAEscolher -= 1;
        if (jogoAEscolher < 1)
          jogoAEscolher = 3;
      }
      else if (digitalRead(BtnEsquerda) == HIGH)
        BtnEsquerdaState = 0;
  
      if (digitalRead(BtnSelecionar) == LOW && BtnSelecionarState == 0)
      {
        BtnSelecionarState = 1;
        nJogo = jogoAEscolher;
        lcdClean();
        break;
      }
      else if (digitalRead(BtnSelecionar) == HIGH)
        BtnSelecionarState = 0;

      if (digitalRead(BtnDireita) == LOW && BtnDireitaState == 0)
      {
        BtnDireitaState = 1;
        jogoAEscolher += 1;
        if (jogoAEscolher > 3)
          jogoAEscolher = 1;
      }
      else if (digitalRead(BtnDireita) == HIGH)
        BtnDireitaState = 0;
    }
  }
  else if (nJogo == 1)
  {
    randomSeed(analogRead(Roda1));
    rand1 = random(157, 1023);
    rand2 = random(157, 1023);
    rand3 = random(157, 1023);
    rand4 = random(157, 1023);
    analogWrite(LED1r, 128);
    analogWrite(LED1g, 64);
    analogWrite(LED1b, 128);
    analogWrite(LED2r, 128);
    analogWrite(LED2g, 64);
    analogWrite(LED2b, 128);
    analogWrite(LED3r, 128);
    analogWrite(LED3g, 64);
    analogWrite(LED3b, 128);
    analogWrite(LED4r, 128);
    analogWrite(LED4g, 64);
    analogWrite(LED4b, 128);
    for ( ; ; )
    {
      if (digitalRead(btnMulti) == LOW && BtnVerificarState == 0)
      {
        BtnVerificarState = 1;
        if (analogRead(Roda1) < rand1 + 40 && analogRead(Roda1) > rand1 - 40)
        {
          analogWrite(LED1r, 64);
          analogWrite(LED1g, 128);
          analogWrite(LED1b, 79);
          acertos[0] = 1;
        }
        else
        {
          analogWrite(LED1r, 128);
          analogWrite(LED1g, 64);
          analogWrite(LED1b, 128);
          acertos[0] = 0;
        }

        if (analogRead(Roda2) < rand2 + 40 && analogRead(Roda2) > rand2 - 40)
        {
          analogWrite(LED2r, 64);
          analogWrite(LED2g, 128);
          analogWrite(LED2b, 79);
          acertos[1] = 1;
        }
        else
        {
          analogWrite(LED2r, 128);
          analogWrite(LED2g, 64);
          analogWrite(LED2b, 128);
          acertos[1] = 0;
        }

        if (analogRead(Roda3) < rand3 + 40 && analogRead(Roda3) > rand3 - 40)
        {
          analogWrite(LED3r, 64);
          analogWrite(LED3g, 128);
          analogWrite(LED3b, 79);
          acertos[2] = 1;
        }
        else
        {
          analogWrite(LED3r, 128);
          analogWrite(LED3g, 64);
          analogWrite(LED3b, 128);
          acertos[2] = 0;
        }

        if (analogRead(Roda4) < rand4 + 40 && analogRead(Roda4) > rand4 - 40)
        {
          analogWrite(LED4r, 64);
          analogWrite(LED4g, 128);
          analogWrite(LED4b, 79);
          acertos[3] = 1;
        }
        else
        {
          analogWrite(LED4r, 128);
          analogWrite(LED4g, 64);
          analogWrite(LED4b, 128);
          acertos[3] = 0;
        }

        if (acertos[0] == 1 && acertos[1] == 1 && acertos[2] == 1 && acertos[3] == 1)
        {
          delay(1000);
          acertos[0] = 0;
          acertos[1] = 0;
          acertos[2] = 0;
          acertos[3] = 0;
          analogWrite(LED1r, 0);
          analogWrite(LED1g, 0);
          analogWrite(LED1b, 0);
          analogWrite(LED2r, 0);
          analogWrite(LED2g, 0);
          analogWrite(LED2b, 0);
          analogWrite(LED3r, 0);
          analogWrite(LED3g, 0);
          analogWrite(LED3b, 0);
          analogWrite(LED4r, 0);
          analogWrite(LED4g, 0);
          analogWrite(LED4b, 0);
          lcdClean();
          lcd.setCursor(0, 0);
          lcd.print("   Parabens");
          rainbowColors();
          break;
        }
      }
      else if (digitalRead(btnMulti) == HIGH)
        BtnVerificarState = 0;
    }
    nJogo = 0;
  }
  else if (nJogo == 2)
  {
    digitalWrite(Tempo1B, LOW);
    digitalWrite(Tempo1C, LOW);
    digitalWrite(Tempo1E, LOW);
    digitalWrite(Tempo1F, LOW);
    digitalWrite(Tempo1G, LOW);
    digitalWrite(Tempo2B, LOW);
    digitalWrite(Tempo2C, LOW);
    for ( ; ; ) {
      if (digitalRead(BtnClique) == LOW)
        break;
    }
    dezenas = 2;
    unidades = 0;
    digitalWrite(Tempo1A, Numeros[0][0]);
    digitalWrite(Tempo1B, Numeros[0][1]);
    digitalWrite(Tempo1C, Numeros[0][2]);
    digitalWrite(Tempo1D, Numeros[0][3]);
    digitalWrite(Tempo1E, Numeros[0][4]);
    digitalWrite(Tempo1F, Numeros[0][5]);
    digitalWrite(Tempo1G, Numeros[0][6]);
    digitalWrite(Tempo2A, Numeros[3][0]);
    digitalWrite(Tempo2B, Numeros[3][1]);
    digitalWrite(Tempo2C, Numeros[3][2]);
    digitalWrite(Tempo2D, Numeros[3][3]);
    digitalWrite(Tempo2E, Numeros[3][4]);
    digitalWrite(Tempo2F, Numeros[3][5]);
    digitalWrite(Tempo2G, Numeros[3][6]);
    delay(1000);
    digitalWrite(Tempo2A, Numeros[2][0]);
    digitalWrite(Tempo2B, Numeros[2][1]);
    digitalWrite(Tempo2C, Numeros[2][2]);
    digitalWrite(Tempo2D, Numeros[2][3]);
    digitalWrite(Tempo2E, Numeros[2][4]);
    digitalWrite(Tempo2F, Numeros[2][5]);
    digitalWrite(Tempo2G, Numeros[2][6]);
    delay(1000);
    digitalWrite(Tempo2A, Numeros[1][0]);
    digitalWrite(Tempo2B, Numeros[1][1]);
    digitalWrite(Tempo2C, Numeros[1][2]);
    digitalWrite(Tempo2D, Numeros[1][3]);
    digitalWrite(Tempo2E, Numeros[1][4]);
    digitalWrite(Tempo2F, Numeros[1][5]);
    digitalWrite(Tempo2G, Numeros[1][6]);
    delay(1000);
    tempoPassado = millis();
    digitalWrite(Tempo1A, Numeros[dezenas][0]);
    digitalWrite(Tempo1B, Numeros[dezenas][1]);
    digitalWrite(Tempo1C, Numeros[dezenas][2]);
    digitalWrite(Tempo1D, Numeros[dezenas][3]);
    digitalWrite(Tempo1E, Numeros[dezenas][4]);
    digitalWrite(Tempo1F, Numeros[dezenas][5]);
    digitalWrite(Tempo1G, Numeros[dezenas][6]);
    digitalWrite(Tempo2A, Numeros[unidades][0]);
    digitalWrite(Tempo2B, Numeros[unidades][1]);
    digitalWrite(Tempo2C, Numeros[unidades][2]);
    digitalWrite(Tempo2D, Numeros[unidades][3]);
    digitalWrite(Tempo2E, Numeros[unidades][4]);
    digitalWrite(Tempo2F, Numeros[unidades][5]);
    digitalWrite(Tempo2G, Numeros[unidades][6]);
    for ( ; ; )
    {
      millisTempo = millis();
      if ((millisTempo - tempoPassado) >= 1000)
      {
        tempoPassado = millisTempo;
        if (unidades != 0)
        {
          --unidades;
          digitalWrite(Tempo2A, Numeros[unidades][0]);
          digitalWrite(Tempo2B, Numeros[unidades][1]);
          digitalWrite(Tempo2C, Numeros[unidades][2]);
          digitalWrite(Tempo2D, Numeros[unidades][3]);
          digitalWrite(Tempo2E, Numeros[unidades][4]);
          digitalWrite(Tempo2F, Numeros[unidades][5]);
          digitalWrite(Tempo2G, Numeros[unidades][6]);
        }
        else if (dezenas != 0)
        {
          --dezenas;
          unidades = 9;
          digitalWrite(Tempo1A, Numeros[dezenas][0]);
          digitalWrite(Tempo1B, Numeros[dezenas][1]);
          digitalWrite(Tempo1C, Numeros[dezenas][2]);
          digitalWrite(Tempo1D, Numeros[dezenas][3]);
          digitalWrite(Tempo1E, Numeros[dezenas][4]);
          digitalWrite(Tempo1F, Numeros[dezenas][5]);
          digitalWrite(Tempo1G, Numeros[dezenas][6]);
          digitalWrite(Tempo2A, Numeros[unidades][0]);
          digitalWrite(Tempo2B, Numeros[unidades][1]);
          digitalWrite(Tempo2C, Numeros[unidades][2]);
          digitalWrite(Tempo2D, Numeros[unidades][3]);
          digitalWrite(Tempo2E, Numeros[unidades][4]);
          digitalWrite(Tempo2F, Numeros[unidades][5]);
          digitalWrite(Tempo2G, Numeros[unidades][6]);
        }
        else
          break;
      }
      if (digitalRead(BtnClique) == LOW && BtnCliqueState == 0)
      {
        BtnCliqueState = 1;
        cliques++;
      }
      else if (digitalRead(BtnClique) == HIGH)
        BtnCliqueState = 0;
    }
    lcdClean();
    lcd.setCursor(0, 0);
    lcd.print("   Parabens");
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(cliques);
    for (int i = 0; i < 6; i++)
    {
      digitalWrite(Tempo1A, LOW);
      digitalWrite(Tempo1B, LOW);
      digitalWrite(Tempo1C, HIGH);
      digitalWrite(Tempo1D, HIGH);
      digitalWrite(Tempo1E, HIGH);
      digitalWrite(Tempo1F, LOW);
      digitalWrite(Tempo1G, LOW);
      digitalWrite(Tempo2A, HIGH);
      digitalWrite(Tempo2B, HIGH);
      digitalWrite(Tempo2C, LOW);
      digitalWrite(Tempo2D, LOW);
      digitalWrite(Tempo2E, LOW);
      digitalWrite(Tempo2F, HIGH);
      digitalWrite(Tempo2G, LOW);
      delay(150);
      digitalWrite(Tempo1A, HIGH);
      digitalWrite(Tempo1B, HIGH);
      digitalWrite(Tempo1C, LOW);
      digitalWrite(Tempo1D, LOW);
      digitalWrite(Tempo1E, LOW);
      digitalWrite(Tempo1F, HIGH);
      digitalWrite(Tempo1G, LOW);
      digitalWrite(Tempo2A, LOW);
      digitalWrite(Tempo2B, LOW);
      digitalWrite(Tempo2C, HIGH);
      digitalWrite(Tempo2D, HIGH);
      digitalWrite(Tempo2E, HIGH);
      digitalWrite(Tempo2F, LOW);
      digitalWrite(Tempo2G, LOW);
      delay(150);
    }
    digitalWrite(Tempo1A, HIGH);
    digitalWrite(Tempo1B, HIGH);
    digitalWrite(Tempo1C, HIGH);
    digitalWrite(Tempo1D, HIGH);
    digitalWrite(Tempo1E, HIGH);
    digitalWrite(Tempo1F, HIGH);
    digitalWrite(Tempo1G, HIGH);
    digitalWrite(Tempo2A, HIGH);
    digitalWrite(Tempo2B, HIGH);
    digitalWrite(Tempo2C, HIGH);
    digitalWrite(Tempo2D, HIGH);
    digitalWrite(Tempo2E, HIGH);
    digitalWrite(Tempo2F, HIGH);
    digitalWrite(Tempo2G, HIGH);
    delay(3000);
    nJogo = 0;
  }
  else if (nJogo == 3)
  {
    digitalWrite(NumeroA, LOW);
    digitalWrite(NumeroB, LOW);
    digitalWrite(NumeroC, LOW);
    digitalWrite(NumeroD, LOW);
    digitalWrite(NumeroE, LOW);
    digitalWrite(NumeroF, LOW);
    digitalWrite(Tempo1B, LOW);
    digitalWrite(Tempo1C, LOW);
    digitalWrite(Tempo1E, LOW);
    digitalWrite(Tempo1F, LOW);
    digitalWrite(Tempo1G, LOW);
    digitalWrite(Tempo2B, LOW);
    digitalWrite(Tempo2C, LOW);
    for ( ; ; ) {
      if (digitalRead(btnMulti) == LOW)
        break;
    }
    dezenas = 3;
    unidades = 0;
    digitalWrite(Tempo1A, Numeros[0][0]);
    digitalWrite(Tempo1B, Numeros[0][1]);
    digitalWrite(Tempo1C, Numeros[0][2]);
    digitalWrite(Tempo1D, Numeros[0][3]);
    digitalWrite(Tempo1E, Numeros[0][4]);
    digitalWrite(Tempo1F, Numeros[0][5]);
    digitalWrite(Tempo1G, Numeros[0][6]);
    digitalWrite(Tempo2A, Numeros[3][0]);
    digitalWrite(Tempo2B, Numeros[3][1]);
    digitalWrite(Tempo2C, Numeros[3][2]);
    digitalWrite(Tempo2D, Numeros[3][3]);
    digitalWrite(Tempo2E, Numeros[3][4]);
    digitalWrite(Tempo2F, Numeros[3][5]);
    digitalWrite(Tempo2G, Numeros[3][6]);
    delay(1000);
    digitalWrite(Tempo2A, Numeros[2][0]);
    digitalWrite(Tempo2B, Numeros[2][1]);
    digitalWrite(Tempo2C, Numeros[2][2]);
    digitalWrite(Tempo2D, Numeros[2][3]);
    digitalWrite(Tempo2E, Numeros[2][4]);
    digitalWrite(Tempo2F, Numeros[2][5]);
    digitalWrite(Tempo2G, Numeros[2][6]);
    delay(1000);
    digitalWrite(Tempo2A, Numeros[1][0]);
    digitalWrite(Tempo2B, Numeros[1][1]);
    digitalWrite(Tempo2C, Numeros[1][2]);
    digitalWrite(Tempo2D, Numeros[1][3]);
    digitalWrite(Tempo2E, Numeros[1][4]);
    digitalWrite(Tempo2F, Numeros[1][5]);
    digitalWrite(Tempo2G, Numeros[1][6]);
    delay(1000);
    tempoPassado = millis();
    digitalWrite(Tempo1A, Numeros[dezenas][0]);
    digitalWrite(Tempo1B, Numeros[dezenas][1]);
    digitalWrite(Tempo1C, Numeros[dezenas][2]);
    digitalWrite(Tempo1D, Numeros[dezenas][3]);
    digitalWrite(Tempo1E, Numeros[dezenas][4]);
    digitalWrite(Tempo1F, Numeros[dezenas][5]);
    digitalWrite(Tempo1G, Numeros[dezenas][6]);
    digitalWrite(Tempo2A, Numeros[unidades][0]);
    digitalWrite(Tempo2B, Numeros[unidades][1]);
    digitalWrite(Tempo2C, Numeros[unidades][2]);
    digitalWrite(Tempo2D, Numeros[unidades][3]);
    digitalWrite(Tempo2E, Numeros[unidades][4]);
    digitalWrite(Tempo2F, Numeros[unidades][5]);
    digitalWrite(Tempo2G, Numeros[unidades][6]);
    for ( ; ; )
    {
      millisTempo = millis();
      if ((millisTempo - tempoPassado) >= 1000)
      {
        tempoPassado = millisTempo;
        if (unidades != 0)
        {
          --unidades;
          digitalWrite(Tempo2A, Numeros[unidades][0]);
          digitalWrite(Tempo2B, Numeros[unidades][1]);
          digitalWrite(Tempo2C, Numeros[unidades][2]);
          digitalWrite(Tempo2D, Numeros[unidades][3]);
          digitalWrite(Tempo2E, Numeros[unidades][4]);
          digitalWrite(Tempo2F, Numeros[unidades][5]);
          digitalWrite(Tempo2G, Numeros[unidades][6]);
        }
        else if (dezenas != 0)
        {
          --dezenas;
          unidades = 9;
          digitalWrite(Tempo1A, Numeros[dezenas][0]);
          digitalWrite(Tempo1B, Numeros[dezenas][1]);
          digitalWrite(Tempo1C, Numeros[dezenas][2]);
          digitalWrite(Tempo1D, Numeros[dezenas][3]);
          digitalWrite(Tempo1E, Numeros[dezenas][4]);
          digitalWrite(Tempo1F, Numeros[dezenas][5]);
          digitalWrite(Tempo1G, Numeros[dezenas][6]);
          digitalWrite(Tempo2A, Numeros[unidades][0]);
          digitalWrite(Tempo2B, Numeros[unidades][1]);
          digitalWrite(Tempo2C, Numeros[unidades][2]);
          digitalWrite(Tempo2D, Numeros[unidades][3]);
          digitalWrite(Tempo2E, Numeros[unidades][4]);
          digitalWrite(Tempo2F, Numeros[unidades][5]);
          digitalWrite(Tempo2G, Numeros[unidades][6]);
        }
        else
          break;
      }
      if (generateNew == 1)
      {
        btnNumber = random(1, 9);
        digitalWrite(NumeroA, Numeros[btnNumber][0]);
        digitalWrite(NumeroB, Numeros[btnNumber][1]);
        digitalWrite(NumeroC, Numeros[btnNumber][2]);
        digitalWrite(NumeroD, Numeros[btnNumber][3]);
        digitalWrite(NumeroE, Numeros[btnNumber][4]);
        digitalWrite(NumeroF, Numeros[btnNumber][5]);
        digitalWrite(NumeroG, Numeros[btnNumber][6]);
        switch (btnNumber)
        {
          case 1:
            randomBtn = Btn1;
            break;
          case 2:
            randomBtn = Btn2;
            break;
          case 3:
            randomBtn = Btn3;
            break;
          case 4:
            randomBtn = Btn4;
            break;
          case 5:
            randomBtn = Btn5;
            break;
          case 6:
            randomBtn = Btn6;
            break;
          case 7:
            randomBtn = Btn7;
            break;
          case 8:
            randomBtn = Btn8;
            break;
        }
        generateNew = 0;
      }
      if (digitalRead(randomBtn) == LOW)
      {
        points++;
        generateNew = 1;
      }
    }
    lcdClean();
    lcd.setCursor(0, 0);
    lcd.print("   Parabens");
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(points);
    digitalWrite(NumeroA, HIGH);
    digitalWrite(NumeroB, HIGH);
    digitalWrite(NumeroC, HIGH);
    digitalWrite(NumeroD, HIGH);
    digitalWrite(NumeroE, HIGH);
    digitalWrite(NumeroF, HIGH);
    digitalWrite(NumeroG, HIGH);
    generateNew = 1;
    for (int i = 0; i < 6; i++)
    {
      digitalWrite(Tempo1A, LOW);
      digitalWrite(Tempo1B, LOW);
      digitalWrite(Tempo1C, HIGH);
      digitalWrite(Tempo1D, HIGH);
      digitalWrite(Tempo1E, HIGH);
      digitalWrite(Tempo1F, LOW);
      digitalWrite(Tempo1G, LOW);
      digitalWrite(Tempo2A, HIGH);
      digitalWrite(Tempo2B, HIGH);
      digitalWrite(Tempo2C, LOW);
      digitalWrite(Tempo2D, LOW);
      digitalWrite(Tempo2E, LOW);
      digitalWrite(Tempo2F, HIGH);
      digitalWrite(Tempo2G, LOW);
      delay(150);
      digitalWrite(Tempo1A, HIGH);
      digitalWrite(Tempo1B, HIGH);
      digitalWrite(Tempo1C, LOW);
      digitalWrite(Tempo1D, LOW);
      digitalWrite(Tempo1E, LOW);
      digitalWrite(Tempo1F, HIGH);
      digitalWrite(Tempo1G, LOW);
      digitalWrite(Tempo2A, LOW);
      digitalWrite(Tempo2B, LOW);
      digitalWrite(Tempo2C, HIGH);
      digitalWrite(Tempo2D, HIGH);
      digitalWrite(Tempo2E, HIGH);
      digitalWrite(Tempo2F, LOW);
      digitalWrite(Tempo2G, LOW);
      delay(150);
    }
    digitalWrite(Tempo1A, HIGH);
    digitalWrite(Tempo1B, HIGH);
    digitalWrite(Tempo1C, HIGH);
    digitalWrite(Tempo1D, HIGH);
    digitalWrite(Tempo1E, HIGH);
    digitalWrite(Tempo1F, HIGH);
    digitalWrite(Tempo1G, HIGH);
    digitalWrite(Tempo2A, HIGH);
    digitalWrite(Tempo2B, HIGH);
    digitalWrite(Tempo2C, HIGH);
    digitalWrite(Tempo2D, HIGH);
    digitalWrite(Tempo2E, HIGH);
    digitalWrite(Tempo2F, HIGH);
    digitalWrite(Tempo2G, HIGH);
    rainbowColors();
    nJogo = 0;
  }
}

void lcdClean() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void rainbowColors() {
  delay(500);
  analogWrite(LED1r, 128);
  analogWrite(LED1g, 0);
  analogWrite(LED1b, 0);
  delay(500);
  analogWrite(LED2r, 128);
  analogWrite(LED2g, 0);
  analogWrite(LED2b, 0);
  analogWrite(LED1r, 128);
  analogWrite(LED1g, 120);
  analogWrite(LED1b, 0);
  delay(500);
  analogWrite(LED3r, 128);
  analogWrite(LED3g, 0);
  analogWrite(LED3b, 0);
  analogWrite(LED2r, 128);
  analogWrite(LED2g, 120);
  analogWrite(LED2b, 0);
  analogWrite(LED1r, 128);
  analogWrite(LED1g, 128);
  analogWrite(LED1b, 0);
  delay(500);
  analogWrite(LED4r, 128);
  analogWrite(LED4g, 0);
  analogWrite(LED4b, 0);
  analogWrite(LED3r, 128);
  analogWrite(LED3g, 120);
  analogWrite(LED3b, 0);
  analogWrite(LED2r, 128);
  analogWrite(LED2g, 128);
  analogWrite(LED2b, 0);
  analogWrite(LED1r, 0);
  analogWrite(LED1g, 128);
  analogWrite(LED1b, 0);
  delay(500);
  analogWrite(LED4r, 128);
  analogWrite(LED4g, 120);
  analogWrite(LED4b, 0);
  analogWrite(LED3r, 128);
  analogWrite(LED3g, 128);
  analogWrite(LED3b, 0);
  analogWrite(LED2r, 0);
  analogWrite(LED2g, 128);
  analogWrite(LED2b, 0);
  analogWrite(LED1r, 0);
  analogWrite(LED1g, 0);
  analogWrite(LED1b, 128);
  delay(500);
  analogWrite(LED4r, 128);
  analogWrite(LED4g, 128);
  analogWrite(LED4b, 0);
  analogWrite(LED3r, 0);
  analogWrite(LED3g, 128);
  analogWrite(LED3b, 0);
  analogWrite(LED2r, 0);
  analogWrite(LED2g, 0);
  analogWrite(LED2b, 128);
  analogWrite(LED1r, 128);
  analogWrite(LED1g, 0);
  analogWrite(LED1b, 128);
  delay(500);
  analogWrite(LED4r, 0);
  analogWrite(LED4g, 128);
  analogWrite(LED4b, 0);
  analogWrite(LED3r, 0);
  analogWrite(LED3g, 0);
  analogWrite(LED3b, 128);
  analogWrite(LED2r, 128);
  analogWrite(LED2g, 0);
  analogWrite(LED2b, 128);
  analogWrite(LED1r, 0);
  analogWrite(LED1g, 0);
  analogWrite(LED1b, 0);
  delay(500);
  analogWrite(LED4r, 0);
  analogWrite(LED4g, 0);
  analogWrite(LED4b, 128);
  analogWrite(LED3r, 128);
  analogWrite(LED3g, 0);
  analogWrite(LED3b, 128);
  analogWrite(LED2r, 0);
  analogWrite(LED2g, 0);
  analogWrite(LED2b, 0);
  delay(500);
  analogWrite(LED4r, 128);
  analogWrite(LED4g, 0);
  analogWrite(LED4b, 128);
  analogWrite(LED3r, 0);
  analogWrite(LED3g, 0);
  analogWrite(LED3b, 0);
  delay(500);
  analogWrite(LED4r, 0);
  analogWrite(LED4g, 0);
  analogWrite(LED4b, 0);
}