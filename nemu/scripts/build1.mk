.DEFAULT_GOAL = app  # 设置默认目标为 'app'

# 如果目标是共享库，添加必要的选项
ifeq ($(SHARE),1)
SO = -so  # 设置共享库的后缀
CFLAGS  += -fPIC -fvisibility=hidden  # 添加编译标志，用于生成位置无关代码和隐藏符号
LDFLAGS += -shared -fPIC  # 添加链接标志，用于生成共享库
endif

#$(shell pwd) 获取的是执行 make 命令时的当前工作目录，而不是 Makefile 所在目录
WORK_DIR  = $(shell pwd)  # 获取当前工作目录
BUILD_DIR = $(WORK_DIR)/build  # 设置构建目录路径

#:= 是变量赋值操作符，用于立即展开右侧的值并赋值给左侧的变量。这种赋值方式被称为“简单扩展变量”，与延迟展开变量（=）不同
INC_PATH := $(WORK_DIR)/include $(INC_PATH)  
OBJ_DIR  = $(BUILD_DIR)/obj-$(NAME)$(SO)  # 设置目标文件存放目录
BINARY   = $(BUILD_DIR)/$(NAME)$(SO)  # 设置生成的二进制文件路径

# 编译标志
#ifeq ($(CC),clang) 用于检查变量 CC 的值是否等于 clang
ifeq ($(CC),clang)
CXX := clang++  # 如果使用 clang 作为编译器，设置 C++ 编译器为 clang++
else
CXX := g++  # 否则，设置 C++ 编译器为 g++
endif
LD := $(CXX)  # 设置链接器为 C++ 编译器
INCLUDES = $(addprefix -I, $(INC_PATH))  # 将包含路径前加上 -I 标志
CFLAGS  := -O2 -MMD -Wall -Werror $(INCLUDES) $(CFLAGS)  # 设置编译标志
LDFLAGS := -O2 $(LDFLAGS)  # 设置链接标志

#别处理 C 源文件（.c）和 C++ 源文件（.cc），并将生成的目标文件放置在指定的目录中
#OBJS 变量将包含所有经过模式替换后生成的目标文件的完整路径。
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o) $(CXXSRC:%.cc=$(OBJ_DIR)/%.o)  # 生成目标文件列表

# 编译模式
$(OBJ_DIR)/%.o: %.c  
# 匹配所有 .c 文件，生成对应的 .o 文件
#@：抑制命令本身的输出，$< 表示第一个依赖文件，即当前要编译的源文件
	@echo + CC $<  # 打印编译信息
	@mkdir -p $(dir $@)  # 创建目标文件存放目录
	@$(CC) $(CFLAGS) -c -o $@ $<  # 编译 .c 文件，-c：表示只编译，不链接
	$(call call_fixdep, $(@:.o=.d), $@)  # 调用 fixdep 函数修正依赖，$(@:.o=.d)：将目标文件的扩展名从 .o 替换为 .d，表示依赖文件

$(OBJ_DIR)/%.o: %.cc  # 匹配所有 .cc 文件，生成对应的 .o 文件
	@echo + CXX $<  # 打印编译信息
	@mkdir -p $(dir $@)  # 创建目标文件存放目录
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<  # 编译 .cc 文件
	$(call call_fixdep, $(@:.o=.d), $@)  # 调用 fixdep 函数修正依赖

# 包含依赖文件
-include $(OBJS:.o=.d)

# 便捷规则

.PHONY: app clean  # 声明 app 和 clean 为伪目标

app: $(BINARY)  # 定义 app 目标，依赖于二进制文件

$(BINARY):: $(OBJS) $(ARCHIVES)  # 定义二进制文件生成规则，依赖于目标文件和归档文件
	@echo + LD $@  # 打印链接信息
	@$(LD) -o $@ $(OBJS) $(LDFLAGS) $(ARCHIVES) $(LIBS)  # 链接生成二进制文件

clean:
	-rm -rf $(BUILD_DIR)  # 定义 clean 目标，删除构建目录
