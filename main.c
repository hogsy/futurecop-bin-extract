#include <PL/platform_filesystem.h>
#include <PL/platform_image.h>

#include <errno.h>

/* utility to rip bitmaps out of Future Cop's febmp.bin */

int main() {
    size_t size = plGetFileSize("febmp.bin");
    FILE *fp = fopen("febmp.bin", "rb");

    uint32_t num_images;
    fread(&num_images, sizeof(uint32_t), 1, fp);
    for(unsigned int i = 0; i < num_images; ++i) {
        long pos = ftell(fp); /* start of bitmap */

        char bm[2];
        fread(bm, sizeof(uint8_t), 2, fp);
        if(strncmp("BM", bm, 2) != 0) {
            printf("Invalid bitmap header, aborting!\n");
            return EXIT_FAILURE;
        }

        uint32_t length;
        fread(&length, sizeof(uint32_t), 1, fp);

        if(fseek(fp, pos, SEEK_SET) != 0) {
            printf("Failed to set position to start of bitmap (%d), aborting!\n", errno);
            return EXIT_FAILURE;
        } /* seek back to start of bitmap */
        pos = ftell(fp);

        uint8_t buf[length];
        fread(buf, sizeof(uint8_t), length, fp);

        PLImage out;
        plLoadImageFromMemory(buf, length, "bmp", &out);

        char path[PL_SYSTEM_MAX_PATH];
        snprintf(path, sizeof(path), "out/%d.bmp", i);
        plWriteImage(&out, path);
        plFreeImage(&out);
    }
    fclose(fp);

    return 0;
}