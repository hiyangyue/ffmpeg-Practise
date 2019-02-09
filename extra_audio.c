#include <libavutil/log.h>
#include <libavformat/avformat.h>

int main(int argc, char *argv[]){

    av_log_set_level(AV_LOG_INFO);

    //检测输入的参数是否小于3
    if (argc < 3){
        av_log(NULL, AV_LOG_ERROR, "the count of params should be more than 3 \n");
        return -1;
    }

    int rec;
    char *src = NULL;
    char *dst = NULL;
    src = argv[1];
    dst = argv[2];
    AVFormatContext *fmt_cxt = NULL;

    if (!src || !dst){
        av_log(NULL, AV_LOG_ERROR, "src or dst is NULL\n");
        return -1;
    }

    rec = avformat_open_input(&fmt_cxt, src, NULL, NULL);
    if (rec < 0){
        av_log(NULL, AV_LOG_ERROR, "cannot open file : %s\n", av_err2str(rec));
        return -1;
    }

    FILE *dst_fd = fopen(dst, "wb");
    if (!dst_fd){
        av_log(NULL, AV_LOG_ERROR, "cannot open out file\n");
        return -1;
    }

    //打印视频的信息
    av_dump_format(fmt_cxt, 0, src, 0);

    //step2. get stream
    rec = av_find_best_stream(fmt_cxt, AVMEDIA_TYPE_AUDIO, -1,-1,NULL,0);
    if (rec < 0) {
        av_log(NULL,AV_LOG_ERROR,"can't find best stream\n");
        return -1;
    }

    //step3. write audio data to acc file
    AVPacket pkt;
    av_init_packet(&pkt);
    av_read_frame(fmt_cxt,&pkt);


    // 0 -> 音频，1 -> 视频
    int audio_index;
    int len;
    while(av_read_frame(fmt_cxt,&pkt) > 0){
        if (pkt.stream_index == audio_index) {
            len = fwrite(pkt.data,1,pkt.size,dst_fd);
            if (len != pkt.size) {
                av_log(NULL,AV_LOG_WARNING,"len is't equals size of pkt");
            }
            
        }

        av_packet_unref(&pkt);
    }

    avformat_close_input(&fmt_cxt);
    if (dst_fd) {
        fclose(dst_fd);
    }
    

    return 0;
}