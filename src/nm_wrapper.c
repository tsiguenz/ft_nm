#include <ft_nm.h>

void handle_elf32(char *filename, uint8_t *map) {
  (void)filename;
  (void)map;
}
void handle_elf64(char *filename, uint8_t *map) {
  (void)filename;
  Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
  Elf64_Shdr *shdr = (Elf64_Shdr *)(map + (ehdr->e_shoff));
  char *shstrtab = (char *)&map[shdr[ehdr->e_shstrndx].sh_offset];
  for (int i = 0; i < ehdr->e_shnum; i++)
    ft_printf("[%d] %s\n", i, &shstrtab[shdr[i].sh_name]);
}

int nm_wrapper(char *filename) {
  uint8_t *map = NULL;
  off_t file_size = 0;
  char arch = 0;

  if (init(filename, &map, &file_size, &arch))
    return EXIT_FAILURE;
  if (arch == ELFCLASS32)
    handle_elf32(filename, map);
  else
    handle_elf64(filename, map);
  munmap(map, file_size);
  return EXIT_SUCCESS;
}
