#define LOG_TAG "ScreenRecord"
//#define LOG_NDEBUG 0
#include <android/Log.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/wait.h>

/*
#include <gui/SurfaceComposerClient.h>

using namespace android;

void screencap(const char* fn) {
    int fd = open(fn, O_WRONLY | O_CREAT | O_TRUNC, 0664);

    void const* base = 0;
    uint32_t w, h, f;
    size_t size = 0;

    ScreenshotClient screenshot;
    if (screenshot.update() == NO_ERROR) {
        base = screenshot.getPixels();
        w = screenshot.getWidth();
        h = screenshot.getHeight();
        f = screenshot.getFormat();
        size = screenshot.getSize();
    }
    if (base) {
        write(fd, &w, 4);
        write(fd, &h, 4);
        write(fd, &f, 4);
        write(fd, base, size);
    }
    close(fd);
}
*/

long long currentTimeInMilliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
 * Parses args and kicks things off.
 */
int main(int argc, char* const argv[]) {
    char* targetDir = argv[1];
    char command[256];
    char filename[256];
    while (1) {
        sprintf(filename, "%s/fb_%lld.raw", targetDir, currentTimeInMilliseconds());
        sprintf(command, "/system/bin/screencap %s", filename);
        system(command);
        //screencap(filename);
    }
}


