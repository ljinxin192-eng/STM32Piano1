# STM32 MiniPiano 项目说明

## 项目概述
这是一个基于STM32的迷你钢琴合成器项目，包含音频合成、键盘输入处理和DAC输出等功能。

## 用户自定义函数说明

### 音频合成模块 (wavegener.c/h)

#### `void SynthInit(void)`
**功能**: 初始化合成器
- 生成正弦波查找表
- 初始化所有语音通道
- 为音频生成准备必要的资源

#### `int16_t SynthGenSample(void)`
**返回值**: `int16_t` - 合成的音频采样值（范围：-32767 ~ +32767）
**功能**: 生成单个音频采样
- 更新所有活动音符的包络
- 合成所有谐波分量
- 添加起始噪声效果
- 混音所有活动语音
- 限制输出在16位范围内

#### `void GetFsFromKey(uint8_t note)`
**参数**: `note` - MIDI音符编号（0-127）
**功能**: 根据MIDI音符编号计算频率
- 计算公式：`Frequency = 440 * 2^((note - 69) / 12)`

#### `int GetFreeVoice(void)`
**返回值**: `int` - 空闲语音索引号，如果没有空闲返回-1
**功能**: 查找可用的语音通道

#### `void NoteOn(uint8_t note)`
**参数**: `note` - MIDI音符编号
**功能**: 触发音符
1. 查找空闲语音通道
2. 计算音符频率
3. 设置语音参数
4. 激活语音通道

#### `void UpdateEnvelopes(void)`
**功能**: 更新所有语音的ADSR包络
- 实现攻击、衰减、保持、释放四个阶段
- 使用线性插值计算包络值
- 自动停用已完成释放阶段的语音

#### `float CalculateHarmonicDecay(float harmonicTime, int harmonicIndex)`
**参数**:
- `harmonicTime`: 谐波时间（秒）
- `harmonicIndex`: 谐波索引号（0-8）
**返回值**: `float` - 谐波衰减因子
**功能**: 计算谐波随时间衰减的程度

#### `void SwitchTone(const uint8_t* ampArray, const uint8_t* decArray)`
**参数**:
- `ampArray`: 谐波振幅数组（9个元素）
- `decArray`: 谐波衰减率数组（9个元素）
**功能**: 切换音色
- 更新谐波振幅参数
- 更新谐波衰减率参数

### 输入处理模块 (inputhandler.c/h)

#### `int CalcuRbKey(uint16_t inputkey)`
**参数**: `inputkey` - GPIO引脚编号
**返回值**: `int` - 对应的MIDI音符偏移量（60-71）
**功能**: 将物理按键映射到MIDI音符
- 支持12个白键/黑键映射
- 返回C4到B4范围内的音符偏移

#### `void ChangeInNote(uint16_t inputkey, int* LEVEL)`
**参数**:
- `inputkey`: GPIO引脚编号
- `LEVEL`: 指向八度偏移变量的指针
**功能**: 处理按键输入并触发相应音符
1. 识别功能键（FK1-3）调整八度
2. 识别音符键计算最终MIDI音符
3. 调用`NoteOn`触发音符

### 主程序模块 (main.c)

#### `void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)`
**参数**: `GPIO_PIN` - 触发中断的引脚编号
**功能**: GPIO外部中断回调函数
- 处理音符键的实时中断
- 调用`ChangeInNote`处理输入

#### `void OutputToDAC(int16_t sample)`
**参数**: `sample` - 16位音频采样值
**功能**: 将音频采样输出到DAC
- 将±32767范围转换为0-4095范围
- 设置DAC通道输出值

#### `void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)`
**参数**: `htim` - 定时器句柄指针
**功能**: 定时器中断回调函数
- TIM2: 音频处理定时标志
- TIM3: 功能键扫描定时标志

#### `void AudioProcess(void)`
**功能**: 音频处理主函数
1. 检查音频定时标志
2. 生成音频采样
3. 输出到DAC
4. 清除定时标志

#### `void ScanFunctionKeys(void)`
**功能**: 功能键扫描函数
- 实现按键消抖
- 检测功能键（FK1-3）状态变化
- 处理八度切换功能

## 硬件接口定义

### 按键映射
- **音符键 (NK1-NK12)**: C4#到B4的12个音符
- **功能键**:
  - FK1: 八度升高
  - FK2: 复位到中央C
  - FK3: 八度降低

### 定时器配置
- **TIM2**: 音频采样定时器（44.1kHz）
- **TIM3**: 功能键扫描定时器

### DAC输出
- **通道**: DAC通道1
- **分辨率**: 12位
- **对齐**: 右对齐

## 技术特性

### 音频合成特性
- 采样率：44.1kHz
- 最大复音数：12个音符
- 波表大小：1024点
- 谐波数量：9个
- 包络类型：ADSR（攻击、衰减、保持、释放）

### 信号处理特性
- 相位累加器：32位精度
- 线性插值波表查找
- 谐波时间衰减
- 起始噪声效果

### 系统参数
- 系统时钟：通过PLL配置
- 内存使用：全局变量+查找表
- 中断驱动：定时器中断+GPIO外部中断

## 使用说明

1. 初始化系统后，合成器自动准备就绪
2. 按下音符键触发对应音高的音符
3. 使用功能键调整八度范围
4. 音频通过DAC输出到外部放大器
5. 可通过`SwitchTone`函数切换不同音色

## 注意事项

1. 确保TIM2定时器频率配置为44.1kHz
2. GPIO引脚需要正确配置为输入模式和中断
3. DAC输出范围需要与外部电路匹配
4. 内存资源有限，注意复音数设置
5. 实时性要求高，避免在中断中处理复杂运算
