# HelloFinger
![HelloFinger](https://github.com/Magiclxw/HelloFinger/blob/main/4.Doc/Image/HelloFinger.jpg"HelloFinger")
## 关于本项目：
该项目通过操作单个模块，实现与Windows系统的HID通信，配合上位机实现电脑开机、电脑解锁、鼠标控制、快捷键、多任务、AI对话等功能。

## 项目相关功能：  
  1. AI 对话：接入通义千问API，可进行对话、问答；
  2. 一键开机：HelloFinger具有物理开机按键，按下按键即可实现电脑开机；
  3. 指纹解锁：无需输入密码，验证指纹即可实现电脑解锁；
  4. 自动输入账号密码：在需要输入账号密码的地方通过录入指纹即可自动输入和登录；
  5. 快捷键：可自定义配置快捷键，配置完成后录入指纹即可输入快捷键；
  6. 快捷启动多任务：可自由添加需要启动的程序，配置完成后录入指纹即可一键开启所有程序；
  7. 鼠标：HelloFinger具有鼠标左键、右键、滚轮的功能；
  8. Action：HelloFinger具有一个物理Action按键，用户可以自定义其功能；
  9. RGB灯效：HelloFinger具有6颗RGB灯，可以通过上位机配置其灯效；

## 开发平台：
-**外壳设计**：SolidWorks  
-**原理图、PCB设计**：立创eda  
-**固件**：Keil5  
-**上位机**：Qt  

# 涉及到的能力：
-**语言**:C、C++  
-**开发平台**:Keil MDK5、Qt
-**芯片**:STM32F103C8T6  
