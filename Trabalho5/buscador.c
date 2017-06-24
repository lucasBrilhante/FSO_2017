#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <limits.h> /* PATH_MAX */
#include <string.h>
#include <stdlib.h>

int count = 1;
char abspath[1000];

int removeLastDir(char str[])
{
  int j;
  int i = strlen(str);
  for(j = i-2; j >= 1; j--){
    //printf("%d caralho",j);
    if(str[j] == '/'){
      return j;
    };
  }
  return i;
}
void listdir(int level, const char *m_path, char *substr,int N)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(m_path)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", m_path, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            strcat(abspath,entry->d_name);
            strcat(abspath, "/");
            //printf("%*s[%s]\n", level*2, "", entry->d_name);
            listdir( level + 1,path,substr,N);
            //printf("1%s\n",abspath);
            int index = removeLastDir(abspath);
            char tmppath[index+1]; // note 6, not 5, there's one there for the null terminator
            strncpy(tmppath, abspath, index);
            tmppath[index] = '\0';
            strcpy(abspath,tmppath);
            strcat(abspath, "/");

            //printf("2%s :: %d\n",abspath,index);

        }
        else{
          //printf("Estouu aqui");
          char lpath[100];
          strcpy(lpath,abspath);
          //char *res = realpath(entry->d_name, path);
          //strcat(lpath, "/");
          strcat(lpath, entry->d_name);
          //if(res){
          if(strstr(entry->d_name, substr) != NULL){
            printf("%d.%s --\n",count++,lpath);
            char buff[N];
            FILE *f = fopen(lpath, "r");
            fgets(buff, N, f);
            printf("  %s\n", buff);
            fclose(f);
          }
        }
    } while (entry = readdir(dir));
    closedir(dir);
}

int main(int argc, char *argv[]){

	if(argc < 4){
    printf("Como utilizar este programa: ./prog PATH SEARCHSTR NFILE");
    return 1;
  }
  char path[100];
  char *res = realpath(argv[1], path);
  //strcpy(abspath,path);
  printf("Resultado de buscador \"%s\" na pasta %s \n",argv[2],path);
  //abspath = "";
  listdir( 0, argv[1], argv[2], atoi(argv[3]));
  return 0;
}
