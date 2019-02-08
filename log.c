#include<stdio.h>
#include<libavutil/log.h>

int main(int argc, char* argv[]) {
    // printf("hello world");
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_INFO , "hello------world\n");
    return 0;
}