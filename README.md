# simple game frame
一个简单的C++游戏框架，使用SDL多媒体库。
### 参考资料
 https://wangzhechao.com/sdl2-you-xi-kai-fa-zhi-kuang-jia-da-jian/ \
 https://www.libsdl.org/
### 使用方法
- **初始化** game.init() 自定义窗口名称、宽高、游戏更新帧率等基本信息
- **加载资源** game.loadResource() 利用sgfHelper.h中的getResourceData函数，或直接通过文件路径加载
- **处理游戏事件** game.processEvent() 根据用户输入更新游戏数据
- **更新游戏数据** game.update() 自动化的数据更新，如动画，读秒等。(可利用数据成员game.FPS实现，即该函数每次被调用时间流动1000f/game.FPS毫秒）。
- **渲染游戏画面** game.render() 渲染帧率是最大化渲染，与game.FPS（更新帧率）无关
- **一些可能会用到的工具** 见sgfHHelper.h