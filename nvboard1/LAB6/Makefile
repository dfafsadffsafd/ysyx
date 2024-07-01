TOPNAME = top
NXDC_FILES = constr/top.nxdc
#条件赋值操作符的用法。它用来为变量设定默认值（此处为空），但仅当该变量在之前没有被定义或赋值时生效
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

default: $(BIN)

#$(shell ...) 函数是一种执行shell命令并捕获其输出的方式，mkdir -p创建指定的目录路径中的所有必需的父目录
$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	#$^代表所有的依赖文件，$@代表当前规则的目标文件名
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
#向已存在的 CSRCS 变量追加 $(SRC_AUTO_BIND) 的值
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
#INCFLAGS存储编译器的包括（include）目录选项，指示编译器在哪些目录中查找头文件
#取一个字符串（-I）和一个字符串列表（$(INC_PATH) 中的路径），然后将这个字符串添加到列表中每个元素的前面
INCFLAGS = $(addprefix -I, $(INC_PATH))
#CXXFLAGS存储C++编译器的选项，-D 是GCC和其他C/C++编译器用来定义宏的选项。TOP_NAME：宏的名称
#"\"V$(TOPNAME)\""：宏的值。这里，$(TOPNAME) 是一个Makefile变量，它的值会被展开，然后加上前缀 V 和双引号。注意这里的引号使用了转义字符 \"
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	#@符号意味着不在终端显示执行的命令。
	#--Mdir存放Verilator生成的所有中间文件，-o指定Verilator编译链接生成的最终可执行文件的存放路径
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

all: default

run: $(BIN)
	@$^

clean:
	rm -rf $(BUILD_DIR)

.PHONY: default all clean run
