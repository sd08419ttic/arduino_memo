/* serial_com_test.cpp */

/* header file */
#include "stdafx.h"
#include "serial_com_test.h"

/* static variable */
static int apl_cyc_count = 0;

#define READ_BUFSIZE  (7)   //受信バッファサイズ　x.x,x.x; を想定(終端文字は含まない)
#define SEND_BUFSIZE  (50)  //送信用バッファサイズ
#define SEND_DATA_SIZE (6)  //整数桁3 小数点1 小数点以下2 を想定

//デバッグ用変数
static float deb_val1 = 0.0;
static float deb_val2 = 0.0;
static int keta = 0;

//通信の初期化用関数
void com_init (void)
{
     //Serial Communication initialization
    Serial.begin(115200);      //boudrate 115200
    Serial.setTimeout(5);      //read timeout for serial communication
    Serial.print("Serial Communication Start!");
    return;
}

//シリアル通信読み込み用関数
void com_read (void)
{
    char buff_A[4];
    char buff_B[4];
    if(Serial.available())  //読み込むデータが存在する場合
    {
        //終端データ";"までのすべてのデータを読み込む
        String str_buf = Serial.readStringUntil(';');
        if (str_buf.length() == READ_BUFSIZE )
        {
            str_buf.toCharArray(buff_A,4);
            deb_val1 = atoi(buff_A);
            str_buf.toCharArray(buff_B,4,4);  //先頭バイトの指定
            deb_val2 = atof(buff_B);
        }
    }
    return;
}

//シリアル通信読み込み用関数
void com_send (void)
{
    float deb_send_val1;
    float deb_send_val2;

    char test_str[SEND_BUFSIZE]={'\0'}; //配列を初期化用データで埋める
    char *ptr = test_str;

    deb_send_val1 = deb_val1 + 10.0;
    deb_send_val2 = deb_val2 - deb_val1;

    /*Send Acceralation information*/
    dtostrf(deb_send_val1,SEND_DATA_SIZE,2,ptr);
    ptr = ptr + SEND_DATA_SIZE;
    *ptr=',';  //区切り文字_token 
    ptr = ptr + 1;
    dtostrf(deb_send_val2,SEND_DATA_SIZE,2,ptr);
    ptr = ptr + SEND_DATA_SIZE;
    *ptr=';';  //end_token 
    Serial.println(test_str);
    return;
}

/*arduino　初期化処理*/
void setup()
{
    /*Initialize Communication */
    com_init();
}

/*arduinoメインループ*/
void loop()
{
     //50msec 周期実行
	interval<50000>::run([]{
        switch (apl_cyc_count)
        {
            case 0:
                com_read();
                break;
            case 1:
                com_send();;
                break;
            default:
                //no action
                break; 
        }
        if (apl_cyc_count>=1)
        {
            apl_cyc_count = 0;
        }
        else
        {
            apl_cyc_count++;
        }
	});
}
