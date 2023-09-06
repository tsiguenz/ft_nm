#include <ft_nm.h>

int nm_wrapper(char *filename) {
  uint8_t *map = NULL;
  off_t file_size = 0;
  char arch = 0;

  if (init(filename, &map, &file_size, &arch))
    return EXIT_FAILURE;
  ft_printf("arch = %d\n", arch);
  //  Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
  //  Elf64_Shdr *shdr = (Elf64_Shdr *)map + ehdr->e_shoff;
  //  (void)ehdr;
  //  (void)shdr;
  // ft_printf("%d\n", section->sh_type);
  //  for (int i = 0; i < fs.st_size; i++)
  //    write(1, &map[i], 1);
  munmap(map, file_size);
  return EXIT_SUCCESS;
}
