# 标题修饰符(黑粗体,一级标题)

## 标题修饰符（二级标题）

### 标题修饰符（三级标题）

#### 标题修饰符（四级标题）

#####标题修饰符（五级标题）

## 正文与换行

编辑一段测试正文内容<br>
第二段测试文本,在markdone语言中\<br\>为换行符

##字体修饰符

####字体加粗

一段测试**文本**，其中要将**文本**两字用粗体修饰,在需要修饰的正文左右两侧用\*\*包含<br>

####斜体

一段*测试*文本，其中*测试*两字变为斜体，，在需要修饰的文本左右两侧用\*包含<br>

####粗斜体

一段测试文本，其中***修饰***两字变为粗斜体,在需要***修饰***的文本左右两侧用\*\*\*包含<br>

####删除线

一段测试文本，其中~~有一段机密的信息~~，机密信息加入删除线效果，其中两侧用\~\~包含<br>

####关键字凸显

一段测试文本,`珍贵`两字变为凸显关键，需要在文本左右两侧用\`包含<br>

####引用
>一级引用文本
>>二级引用文本
>>>三级引用文本
>>>>四级引用文本

##列表

####有序列表

1. 进程知识
    1. 进程间通信
         1. 管道
         2. MMAP
         3. 消息队列
    2. 进程关系
         1. 子进程
         2. 父进程
    3. 进程安全
2. 线程相关
3. 信号相关
4. 网络相关

####无序列表

* 进程知识
  * 进程间通信
    * 管道
    * MMAP
    * 消息队列
  * 进程关系
    * 子进程
    * 父进程
  * 进程安全
* 线程相关
* 信号相关
* 网络相关

####混合列表

* 热门游戏
   1. 鹅鸭杀
   2. CSGO
   3. 道德与法治5
   4. 王者荣耀

1.获奖游戏
  * GTA
  * FIFA23
  * 原神

##表格

游戏名(居左)|游戏价格(居中)|游戏评分(居中)|游戏热度(居右)|
--|:--:|:--:|--:
GTA|299|90|75%
FIFA23|299|95|85%
原神|10|75|90%

##代码片段

```c
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(void)
{
	printf("test output...\n");
	return 0;
}
```

```bash
	git add filename
	git rm filename
	git remote add origin SSH_address
	echo "数据回显"
```

```cpp
	//C++代码片段
```

```python
	import os;
	#python的代码片段
```

```java
	//java代码片段
```
##插入图片和链接

[bilibili弹幕网](https://www.bilibili.com "进入B站")<br>
[Github](https://github.com "进入GitHub")<br>

![壁纸截图](C:\Users\Aelous\Pictures\老相册\bili\8.jpg "图片")

![壁纸截图](https://m.qpic.cn/psc?/V51ixxtZ4ZqEWc2t5ADK46bYU21N8nql/ruAMsa53pVQWN7FLK88i5qpxEMFIYohVTKnWA2UZGW6D.LV0wWeB19f7.b6BL7SCrR3OZ0yLA4iZsgFhQ*2GM1Stb3AMYGZ70BpD5O4m6RE!/b&bo=ewK2BAAAAAABB.s!&rf=viewer_4 "图片")

###上传的图片地址不允许是本地图片地址，将本地的图片上传到某个图片网站，生成一个 图片的网络地址(URL),用网络地址，github就可以生成出来了
