#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "synchapi.h"
#include "winnt.h"
#define USER_PATH "../../../../../../../userdata/"
#define USER_KEY "cs2_user_keys_0_slot0.vcfg"
#define USER_CONVARS "cs2_user_convars_0_slot0.vcfg"
#define MACHINE_CONVARS "cs2_machine_convars.vcfg"
#define LOCAL_CONFIG_PATH "/730/local/cfg/"
#define EXEC "+exec CFGS/init.cfg"
#define FILE_COUNT 3
#define CMD_CD "cd "
#define CMD_DIR "dir "

FILE *file_user_key, *file_user_convers, *file_machine_convers;

char *save_tin() { // 赋值字符串
  int i = 0;
  char *str = (char *)malloc(1);
  while ((str[i++] = getchar()) != '\n')
    realloc(str, i + 1);
  str[i - 1] = 0; // 结尾'\0'
  return str;
}

int save(char ***str) { // 给指针数组赋值字符串
  int i = 0, siz = sizeof(char *);
  *str = (char **)malloc(siz); // 分配初始的指针数组内存
  do {
    printf("......字符串%d ", i);
    (*str)[i] = save_tin();                       // 赋值字符串
    *str = (char **)realloc(*str, siz * (i + 2)); // 增加字符串
  } while (*(*str)[i++]); // 无字符则跳出
  realloc(*str, siz * --i); // 删除最后的无用字符
  return i;
}

void del_qt(char *str) {
  char temp[500];
  if (*str != '\"' || str[strlen(str) - 1] != '\"')
    return;
  strcpy(temp, str + 1);
  temp[strlen(temp) - 1] = '\0';
  strcpy(str, temp);
}

int strcmp_in(char *str1, char *str2) {
  while (*str1 == *str2 && *str1 && *str2) {
    str1++;
    str2++;
  }
  if (*str2)
    return 0;
  else
    return 1;
}

void file_seek(FILE *file, int count) {
  rewind(file);
  while (count-- > 1) {
    fscanf(file, "%s");
  }
}

int file_find_str(FILE *file, char *find_str,
                  int *count) { // 字符串位置 | 初始化文件位置
  char str[500];
  if (*count < 0)
    *count = 0;
  file_seek(file, *count);

  do {
    fscanf(file, "%s", str);
    del_qt(str);
    (*count)++;
  } while (!strcmp_in(str, find_str) && !feof(file));
  if (!strcmp_in(str, find_str)) {
    rewind(file);
    *count = 0;
    return 0;
  }
  puts("---");
  printf("%s %d\n", str, *count);
  puts("---");
  file_seek(file, *count);
  return 1;
}

void file_print(FILE *file) {
  do {
    char str[100];
    fscanf(file, "%s", str);
    puts(str);
  } while (!feof(file));
}

FILE *load_file(char *path, char *file_name, char *file_restrict) {
  // path - 文件路径 | file_name - 文件名 |  file_restrict - 文件读取方式
  FILE *file;
  char *cmd =
      (char *)malloc(sizeof(char) * (strlen(path) + strlen(file_name) + 1));
  if (!strcmp("r", file_restrict) || !strcmp("r+", file_restrict))
    printf("......正在读取 %s\n", file_name);
  else if (!strcmp("w", file_restrict) || !strcmp("w+", file_restrict))
    printf("......正在写入 %s\n", file_name);
  else if (!strcmp("a", file_restrict) || !strcmp("a+", file_restrict))
    printf("......正在添加 %s\n", file_name);
  else
    puts("格式错误");
  strcpy(cmd, path);
  strcat(cmd, file_name);
  Sleep(100);
  file = fopen(cmd, file_restrict);
  if (file)
    puts("......成功!");
  else
    puts("......失败!");
  ;
  free(cmd);
  Sleep(100);
  return file;
}

void load_config() { // 读取文件
  char *user_name, *user_path;
  int error, file_count = 0;

  while (1) {
    char *cmd;
    error =
        system("powershell -NoProfile cls;dir ../../../../../../../userdata/");
    if (error) {
      puts("未找到userdata文件夹，请将CFGS文件夹放入cs2的cfg文件夹下再尝试...");
      exit(0);
    }
    puts("--------------------------用户目录如上--------------------------");
    printf("\n请输入您的steam号码[不要输入空格][0退出程序]: ");
    user_name = save_tin();
    if (!strcmp(user_name, "0"))
      exit(0);
    cmd = (char *)malloc(sizeof(char) *
                         (strlen(CMD_CD) + strlen(USER_PATH) +
                          strlen(user_name) + strlen(LOCAL_CONFIG_PATH) + 1));
    strcpy(cmd, CMD_CD);
    strcat(cmd, USER_PATH);
    strcat(cmd, user_name);
    strcat(cmd, LOCAL_CONFIG_PATH);
    error = system(cmd); // 测试steam号是否存在
    free(cmd);
    if (error) {
      puts("");
      system("cls");
      puts("----------------------------------------------------------------");
      puts("未找到steam号,请重试!");
      Sleep(100);
    } else
      break;
    system("cls");
  }
  putchar('\n');
  user_path =
      (char *)malloc(sizeof(char) * (strlen(USER_PATH) + strlen(user_name) +
                                     strlen(LOCAL_CONFIG_PATH) + 1));
  strcpy(user_path, USER_PATH);
  strcat(user_path, user_name);
  strcat(user_path, LOCAL_CONFIG_PATH);

  // 加载key文件
  file_user_key = load_file(user_path, USER_KEY, "r");
  if (file_user_key)
    file_count++;

  // 加载user_convars文件
  file_user_convers = load_file(user_path, USER_CONVARS, "r");
  if (file_user_convers)
    file_count++;

  // 加载machine_convars文件
  file_machine_convers = load_file(user_path, MACHINE_CONVARS, "r");
  if (file_machine_convers)
    file_count++;

  if (file_count == FILE_COUNT)
    puts("\n--- 已加载所有配置文件 ---\n");
  else
    printf("\n--- 缺失的%d个文件将使用默认配置 ---\n\n",
           FILE_COUNT - file_count);

  free(user_name);
}

void config_key() {
  puts("------------------------开始写入键位配置------------------------");
  FILE *bind = load_file("config/", "keymaps.cfg", "r+");
  puts("------------------------键位配置写入成功------------------------");
  fclose(bind);
}

void config_convers_user() {
  puts("------------------------开始写入准星配置------------------------");
  FILE *crosshair = load_file("config/crosshair/", "define.cfg", "w");
  int count = 0;
  char str[2][500];
  rewind(file_user_convers);
  while (file_find_str(file_user_convers, "cl_crosshair", &count)) {
    fscanf(file_user_convers, "%s%s", str[0], str[1]);
    del_qt(str[0]);
    del_qt(str[1]);
    fprintf(crosshair, "%s\t\t%s\n", str[0], str[1]);
    count++;
  }
  puts("------------------------准星配置写入成功------------------------");
  fclose(crosshair);
  rewind(file_user_convers);
}

void config_convers_machine() {
  puts("------------------------开始写入游戏配置------------------------");
  puts("------------------------游戏配置写入成功------------------------");
}

void config_to_cfg() {
  puts("......开始提取配置文件");
  if (file_user_key)
    config_key();
  else
    puts("......按键设置将使用默认值[缺失文件]");

  if (file_user_convers)
    config_convers_user();
  else
    puts("......用户设置将使用默认值[缺失文件]");

  if (file_machine_convers)
    config_convers_machine();
  else
    puts("......游戏设置将使用默认值[缺失文件]");

  puts("......加载完毕");
}

int autoexec_5e() {
  printf("......添加5e启动项中\n");
  FILE *file_autoexec_5e = load_file("../", "f5eautoexec.cfg", "a");
  if (file_autoexec_5e)
    puts("......添加成功");
  else
    puts("......添加失败");
  fprintf(file_autoexec_5e, "\n%s\n", EXEC);
  fclose(file_autoexec_5e);
}

void autoexec() {
  printf("......添加启动项中\n");
  FILE *file_autoexec = load_file("../", "autoexec.cfg", "a");
  if (file_autoexec)
    puts("......添加成功");
  else
    puts("......添加失败");
  fprintf(file_autoexec, "\n%s\n", EXEC);
  fclose(file_autoexec);
}

void start() {
  char *cmd;
  while (1) {
    system("cls");
    puts("----------------------------------------------------------------");
    printf("是否开始安装[yes/no]？ ");
    cmd = save_tin();
    if (strcmp(cmd, "yes") == 0 || strcmp(cmd, "y") == 0)
      break;
    else if (strcmp(cmd, "no") == 0 || strcmp(cmd, "n") == 0)
      exit(0);
    else {
      system("cls");
      puts("----------------------------------------------------------------");
      puts("输入错误请重试!");
    }
    free(cmd);
  }
}

int main(int argc, char *argv[]) {
  start();
  system("cls");
  puts("-------------------------加载默认配置中-------------------------");
  load_config();   // 加载配置文件
  config_to_cfg(); // 写入配置

  puts("------------------------添加游戏启动项中------------------------");
  // autoexec();    // 添加启动项
  // autoexec_5e(); // 添加5e启动项

  fclose(file_user_key);
  fclose(file_user_convers);
  fclose(file_machine_convers);
  puts("--安装结束--");
  system("pause");
  return EXIT_SUCCESS;
}
