#include <libavutil/log.h>
#include <libavformat/avformat.h>

int main(int argc, char* argv[]) {

    av_log_set_level(AV_LOG_INFO);
    int rec;
    AVFormatContext *fmt_cxt = NULL;
    rec = avformat_open_input(&fmt_cxt,"./loop.MP4",NULL,NULL);
    if (rec < 0) {
        av_log(NULL,AV_LOG_ERROR,"cannot open file : %s\n",av_err2str(rec));
        return -1;
    }

    av_dump_format(fmt_cxt,0,"./loop.MP4",0);

    return 0;
}