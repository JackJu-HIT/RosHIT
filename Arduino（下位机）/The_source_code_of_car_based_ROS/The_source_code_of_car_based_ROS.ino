/*code authors 
  * Jack Ju
  * HITACTIWH606
  * Harbin institute of technology at weihai
  */
#include <ros.h>
#include <geometry_msgs/Twist.h>
/***电机引脚定义*****/
#define MOTOR_L1 3
#define MOTOR_L2 5
#define MOTOR_R1 6
#define MOTOR_R2 9

double PWM_R=0, PWM_L=0;//初始脉冲
//wheel_rad is the wheel radius ,wheel_sep is
double wheel_rad = 0.0325, wheel_sep = 0.295;
double speed_angular=0;
double speed_linear=0;
ros::NodeHandle nh;
/***回调函数****/
void messageCb(const geometry_msgs::Twist& msg)
{
  speed_angular= msg.angular.z;
  speed_linear = msg.linear.x;
  PWM_L=((speed_linear/wheel_rad)+ ((speed_angular*wheel_sep)/(2.0*wheel_rad)));
  PWM_R=((speed_linear/wheel_rad) - ((speed_angular*wheel_sep)/(2.0*wheel_rad)));
  if(PWM_L>254)
  {
    PWM_L=255;
  }
  if(PWM_R>254)
  {
    PWM_R=255;
   }
  
  
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb);
//发布者，为了调试系统控制系统
geometry_msgs::Twist data;
ros::Publisher  feed_back_data("pwm_l_and_pwm_r",&data);

void MotorL(int Pulse_Width1);
void MotorR(int Pulse_Width2);
void setup()
{
  pinMode( MOTOR_L1, OUTPUT);
  pinMode( MOTOR_L2, OUTPUT);
  pinMode( MOTOR_R1, OUTPUT);
  pinMode( MOTOR_R2, OUTPUT);
  digitalWrite(MOTOR_L1, LOW);
  digitalWrite(MOTOR_L2, LOW);
  digitalWrite( MOTOR_R1, LOW);
  digitalWrite(MOTOR_R2, LOW);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(feed_back_data);
}
/****左边电机函数****/
void MotorL(double Pulse_Width1)
{
  if (Pulse_Width1 > 0){
     analogWrite(MOTOR_L1, Pulse_Width1);
     digitalWrite(MOTOR_L2, LOW);
 }
 if (Pulse_Width1 < 0){
     Pulse_Width1=abs(Pulse_Width1);
      digitalWrite(MOTOR_L1, LOW);
     analogWrite(MOTOR_L2, Pulse_Width1);
 }
 if (Pulse_Width1 == 0){
     digitalWrite(MOTOR_L1, LOW);
     digitalWrite(MOTOR_L2, LOW);
 } 
  }
  /****右侧边电机函数****/
  void MotorR(double Pulse_Width2)
{
  if (Pulse_Width2 > 0){
     analogWrite(MOTOR_R1, Pulse_Width2);
     digitalWrite(MOTOR_R2, LOW);
 }
 if (Pulse_Width2 < 0){
     Pulse_Width2=abs(Pulse_Width2);
      digitalWrite(MOTOR_R1, LOW);
     analogWrite(MOTOR_R2, Pulse_Width2);
 }
 if (Pulse_Width2 == 0){
     digitalWrite(MOTOR_R1, LOW);
     digitalWrite(MOTOR_R2, LOW);
 } 
}
 /***主函数*****/
void loop()
{
 
  MotorL(PWM_L);
  MotorR(PWM_R);
  data.linear.x=PWM_L;
  data.linear.y=PWM_R;
  feed_back_data.publish( &data );
  nh.spinOnce();
  //delay(1);
} 
