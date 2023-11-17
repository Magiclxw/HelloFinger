# HelloFinger
![HelloFinger](https://github.com/Magiclxw/HelloFinger/blob/main/4.Doc/Image/HelloFinger.jpg)
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

## 设计原理
HelloFinger使用一颗STM32F103作为主控通过串口与CH9329芯片通信,CH9329通过HID接口与Windows系统交互；交互方式分为两类，一类直接操作Windows系统，一类以自定义数据包方式与Windows系统进行数据传输。上位机通过HID接口收发自定义数据包，进而实现自定义的交互功能。
在整个系统中，CH9329芯片作为处理器和上位机通信的桥梁，硬件外设产生的各种操作(如编码器拨动、摇杆移动、指纹识别验证等)经过处理后都会通过CH9329传输到电脑，同时，上位机的各种操作也会通过CH9329以指令的方式传输给处理器。

## 开发环境
  1. Qt
     1. 版本：V5.12.12
     2. 编译环境: MinGW 32-bit
     3. 链接库
        1. [全局鼠标键盘监听库](https://github.com/mahuifa/QtGlobalEvent)
        2. [HID通信库](https://github.com/libusb/hidapi)
  2. Keil 5
     1. 版本:5.26.2
     2. 编译器:5.06
     3. 软件包:Keil.STM32F1xx_DFP.2.1.0

## 目录结构
  1. Hardware:硬件文件夹，包含与PCB相关文件；
  2. Firmware:固件文件夹，包含STM32开发相关工程，**bootloader功能尚未实现**；
  3. Software:上位机文件夹，包含上位机工程及编译文件；
  4. Doc:文档文件夹，包含datasheet以及项目相关文档；
  5. Model:模型文件夹：包含3D打印文件；
  6. Tools：工具文件夹：包含硬件外设的测试工具；

## PCB说明
本项目需要2个PCB板，分别是主板和连接器板，其中连接器板不是必须的，如果不需要连接电脑的物理开机键，就可以舍弃掉连接器板。
![连接器板正面](https://github.com/Magiclxw/HelloFinger/blob/main/4.Doc/Image/%E8%BF%9E%E6%8E%A5%E5%99%A8%E6%9D%BF%E6%AD%A3%E9%9D%A2.jpg)
![连接器板背面](https://github.com/Magiclxw/HelloFinger/blob/main/4.Doc/Image/%E8%BF%9E%E6%8E%A5%E5%99%A8%E6%9D%BF%E8%83%8C%E9%9D%A2.jpg)
![主板正面](https://github.com/Magiclxw/HelloFinger/blob/main/4.Doc/Image/%E4%B8%BB%E6%9D%BF%E6%AD%A3%E9%9D%A2.jpg)
![主板背面](https://github.com/Magiclxw/HelloFinger/blob/main/4.Doc/Image/%E4%B8%BB%E6%9D%BF%E8%83%8C%E9%9D%A2.jpg)
PCB采用4层板，电容电阻封装采用0603，整体含有3个非标准封装，分别是JoyStick摇杆、FPM383C指纹识别模块以及弯角微动。
PCB焊接时需要遵循一定的焊接步骤，具体的步骤见[焊接指南](https://github.com/Magiclxw/HelloFinger/blob/main/4.Doc/HelloFinger%E7%84%8A%E6%8E%A5%E6%8C%87%E5%8D%97V1.0.pdf)

## 3D结构件
HelloFinger一共有8个结构件，分别是[连接器上壳](https://github.com/Magiclxw/HelloFinger/blob/main/5.Model/%E8%BF%9E%E6%8E%A5%E5%99%A8%E4%B8%8A%E5%A3%B3..STL)、[连接器下壳](https://github.com/Magiclxw/HelloFinger/blob/main/5.Model/%E8%BF%9E%E6%8E%A5%E5%99%A8%E4%B8%8B%E5%A3%B3.STL)、[主板上壳](https://github.com/Magiclxw/HelloFinger/blob/main/5.Model/%E4%B8%8A%E5%A3%B3.STL)、[主板下壳](https://github.com/Magiclxw/HelloFinger/blob/main/5.Model/%E4%B8%8B%E5%A3%B3.STL)、[上按钮*2](https://github.com/Magiclxw/HelloFinger/blob/main/5.Model/%E4%B8%8A%E6%8C%89%E9%92%AE.STL)、[侧键*2](https://github.com/Magiclxw/HelloFinger/blob/main/5.Model/%E4%BE%A7%E9%94%AE.STL)。

