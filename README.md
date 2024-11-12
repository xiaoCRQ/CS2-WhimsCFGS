![image](https://github.com/xiaoCRQ/CS2-WhimsCFGS/blob/main/ditou.jpg)
# CS2-WhimsCFGS
是在cs2利用各种CFG触发方式实现各种功能，可以轻松自定义和扩展您的配置。

## ✨ 特性

- 🔥 配置迅速
- 💤 接口简洁
- 📦 预置插件
- 🧹 优秀设计
- 🚀 快如闪电

## 🚀 入门

<pre>
1.将此文件夹拖入cfg文件夹中，在steam启动项中添加 exec CFGS/init
【示例路径】【D:\Games\Steam\steamapps\common\Counter-Strike Global Offensive\game\csgo\cfg\CFGS】
2.将自己的准心配置写入 【config\crosshair\def.cfg】【一定要做】
3.在【config\options.cfg】文件中根据自己的灵敏度修改旋转角度
4.将【轮盘替换文件\resource】文件夹下的所有文件覆盖【CS2的resource】文件夹
【示例路径】【D:\Games\Steam\steamapps\common\Counter-Strike Global Offensive\game\csgo\resource】
5.详细内容根据个人喜好在【config\options.cfg】和【config\keymaps.cfg】调整
</pre>

## 📂 文件结构

config 下的文件会在适当的时候自动加载，所以你不需要手动引入这些文件。
**WhimsCFGS** 带有一组默认配置文件，这些文件将在您的配置**之前**加载。

<pre>
~/CFGS/
├─config
│  ├─crosshair
│  ├── autoexec.cfg
│  ├── keymaps.cfg
│  └── options.cfg
├─plugins
│  ├─autoview
│  ├─colorful-cro
│  ├─colorful-ui
│  ├─deertube
│  ├─dhop
│  ├─ez
│  ├─jiting
│  ├─jumpthrow
│  ├─lunpan
│  ├─qk_item
│  ├─rapid_fire
│  ├─spin
│  │  └─move
│  ├─superjump
│  ├─tremor
│  └─twocro
├─radiomenu
│  ├─mode
│  │  ├─pag1
│  │  │  ├─autoview
│  │  │  ├─dhop
│  │  │  ├─jiting
│  │  │  ├─spin
│  │  │  └─twocro
│  │  └─pag2
│  │      ├─colorful-cro
│  │      ├─colorful-ui
│  │      ├─deertube
│  │      ├─ez
│  │      └─tremor
│  └─runchat
├─tick
│  ├─new
│  └─old
└─轮盘替换文件
    ├─folder_origin
    └─folder_replace
        └─resource
</pre>

## ⚙️ Configuration
