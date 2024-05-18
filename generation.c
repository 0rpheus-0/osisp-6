#define _GNU_SOURCE

#define MAX 60081.21597
#define MIN 15020.0

#include "index.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    uint64_t records_count = atoll(argv[1]);
    if (argc != 2 || records_count % 256)
    {
        printf("Error parametrs\n");
        return 1;
    }

    FILE *file = fopen("file", "wb");
    struct index_hdr_s data =
        {
            .recsords = records_count,
            .idx = (struct index_s *)malloc(records_count * sizeof(struct index_s))};
    // struct index_hdr_s data;
    // data.recsords = records_count;
    // data.idx = (struct index_s *)malloc(records_count * sizeof(struct index_s));
    for (uint64_t i = 0; i < records_count; i++)
    {
        struct index_s temp =
            {
                .recno = i + 1,
                .time_mark = ((double)rand() / RAND_MAX) * (MAX - MIN) + MIN};
        data.idx[i] = temp;
    }
    fwrite(&data.recsords, sizeof(uint64_t), 1, file);
    fwrite(data.idx, sizeof(struct index_s), data.recsords, file);
    free(data.idx);
    fclose(file);
    // FILE *file = fopen("file", "wb");
    // data_type data;
    // data.recsords = records_count / 16;
    // data.idx = (index_record *)calloc(data.recsords, sizeof(index_record));
    // fwrite(&data.recsords, sizeof(uint64_t), 1, file);
    // fwrite(&data.idx, sizeof(index_record *), 1, file);
    // for (int i = 0; i < data.recsords; i++)
    // {
    //     index_record tmp;
    //     tmp.recno = i + 1;
    //     tmp.time_mark = ((double)rand() / RAND_MAX) * (MAX - MIN) + MIN;
    //     data.idx[i] = tmp;
    //     fwrite(&tmp, sizeof(index_record), 1, file);
    // }
    // puts("");
    // const char end = '\0';
    // fwrite(&end, 1, 32, file);
    // fclose(file);
    return 0;
}