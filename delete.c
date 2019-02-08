#include <stdio.h>
#include <libavformat/avformat.h>
int main(int argc, char *argv[]) {
    int ret;
    ret = avpriv_io_delete("./a_tobe_delete.txt");
    if (ret < 0) {
        av_log(NULL,AV_LOG_INFO,"delete failure");
        return -1;
    }

    av_log(NULL, AV_LOG_INFO, "delete success");
    return 0;
}