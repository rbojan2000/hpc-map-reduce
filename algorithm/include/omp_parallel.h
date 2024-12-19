
    // int parts = 5;
    // long part_size = file_size / parts;
    // long remainder = file_size % parts;

    // for (int i = 0; i < parts; i++) {
    //     long current_part_size = part_size + (i < remainder ? 1 : 0);
    //     char* part = (char*)malloc(current_part_size + 1);

    //     if (!part) {
    //         perror("Failed to allocate memory for part");
    //         return 1;
    //     }

    //     memcpy(part, text + i * part_size + (i < remainder ? i : remainder), current_part_size);
    //     part[current_part_size] = '\0';

    //     printf("Part %d:\n%s\n\n", i + 1, part);
    //     free(part);
    // }
