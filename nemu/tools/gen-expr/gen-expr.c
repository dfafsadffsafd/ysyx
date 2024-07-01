#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static int choose(int n) {
  return rand() % n;
}

// 生成一个非零的随机数
static void gen_non_zero_num() {
  unsigned int num;
  do {
    num = (unsigned int)choose(100);
  } while (num == 0); // 确保不生成零
  sprintf(buf + strlen(buf), "%uu", num);
  buf[strlen(buf)] = '\0';
}

static void gen_num() {
  unsigned int num = (unsigned int)choose(100);
  sprintf(buf + strlen(buf), "%uu", num);
  buf[strlen(buf)] = '\0';
}

static void gen(char a) {
  sprintf(buf + strlen(buf), "%c", a);
  buf[strlen(buf)] = '\0';
}

static void gen_rand_op() {
  char opt = 0;
  switch (choose(4)) {
    case 0: opt = '+'; break;
    case 1: opt = '-'; break;
    case 2: opt = '*'; break;
    case 3: opt = '/'; break;
  }
  sprintf(buf + strlen(buf), "%c", opt);
  buf[strlen(buf)] = '\0';
}

static inline void gen_rand_expr() {
  if (strlen(buf) < 100) {
    switch (choose(3)) {
      case 0: gen_num(); break;
      case 1: gen('('); gen_rand_expr(); gen(')'); break;
      default:
        gen_rand_expr();
        gen_rand_op();
        if (buf[strlen(buf) - 1] == '/') {
          gen_non_zero_num(); // 确保除数不为零
        } else {
          gen_rand_expr();
        }
        break;
    }
  } else {
    gen_num();
  }
  buf[strlen(buf)] = '\0';
}

void remove_u(char *p) {
  char *q = p;
  while ((q = strchr(q, 'u')) != NULL) {
    // reuse code_buf
    strcpy(code_buf, q + 1);
    strcpy(q, code_buf);
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i++) {
    memset(buf, 0, sizeof(buf));
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    if (ret != 1) continue;
    ret = pclose(fp);
    if (ret != 0) continue;

    remove_u(buf);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
