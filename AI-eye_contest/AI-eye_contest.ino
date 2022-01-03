////////////////////////////////////////
//AI-EYE_ROBOT
//메카트로닉스공학과
////////////////////////////////////////

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <Servo.h>

HUSKYLENS huskylens; //허스키렌즈 클래스 선언
Servo myservo; //서보모터 객체 선언
SoftwareSerial mySerial(10, 11); // RX, TX

//LED 구동 함수
void turnoff(); // 모든 LED 끄기
void LED1_ON(); // LED1 켜기
void LED2_ON(); // LED2 켜기
void LED3_ON(); // LED3 켜기
void RED_ON(); //RED LED 켜기
void changetarget(); // LED가 켜질 동안 러닝 대상 바꾸기

int i = 0;
int j = 0;
int pos = 150;

void setup()
{
  //LED
  pinMode(4, OUTPUT); //첫 번째 비트
  pinMode(5, OUTPUT); //두 번째 비트
  pinMode(6, OUTPUT); //세 번째 비트
  pinMode(7, OUTPUT); //오류
  //서보모터
  myservo.attach(9); // 허스키랜즈 제어 서보 선언
  
  //허스키렌즈
  Serial.begin(115200);
  mySerial.begin(9600);
  while (!huskylens.begin(mySerial))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  myservo.write(150); //서보모터150도로 이동!
  delay(1000);
  huskylens.writeForget(); //기존 러닝 데이터 삭제
  delay(100);
  turnoff(); //모든 LED OFF!
  delay(100);
  //참가자 입력 코드 start

  //참가자 입력 코드 end
}

void loop()
{
  //myservo.detach();
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
  else if (!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
  else
  {
    while (huskylens.available())//허스키랜즈가 연결이 되면 동작!
    {
      HUSKYLENSResult result = huskylens.read();
      //참가자 입력 코드 start
       if (result.ID == 0) //허스키랜즈가 알 수 없는 것을 보고 있을 때
       {
        turnoff();
        RED_ON(); //RED LED ON
       }
      //참가자 입력 코드 end
    }
  }
}

void turnoff()
{
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 1);
}

void LED1_ON()
{
  digitalWrite(4, 0);
}

void LED2_ON()
{
  digitalWrite(5, 0);
}

void LED3_ON()
{
  digitalWrite(6, 0);
}

void RED_ON()
{
  digitalWrite(7, 0);
}

void changetarget()
{
  LED1_ON();
  delay(2000);
  turnoff();
  LED2_ON();
  delay(2000);
  turnoff();
  LED3_ON();
  delay(2000);
  turnoff();
  RED_ON();
  delay(2000);
}
