#include <ft_nm.h>

// int set_elf32_infos(t_elf32 *elf, uint8_t *map, char *file_name,
//                     off_t file_size) {
//   elf->map       = map;
//   elf->file_name = file_name;
//   elf->file_size = file_size;
//   elf->header    = (Elf32_Ehdr *) map;
//   elf->sections  = (Elf32_Shdr *) &map[elf->header->e_shoff];
//   elf->shstrtab =
//       (char *) &map[elf->sections[elf->header->e_shstrndx].sh_offset];
//
//   for (int i = 0; i < elf->header->e_shnum; i++) {
//     const char *section_name = &elf->shstrtab[elf->sections[i].sh_name];
//
//     if (!ft_strncmp(".symtab", section_name, ft_strlen(".symtab")) &&
//         elf->sections[i].sh_type == SHT_SYMTAB) {
//       elf->symtab      = (Elf32_Sym *) &map[elf->sections[i].sh_offset];
//       elf->symtab_size = elf->sections[i].sh_size;
//     }
//     if (!ft_strncmp(".strtab", section_name, ft_strlen(".strtab")) &&
//         elf->sections[i].sh_type == SHT_STRTAB) {
//       elf->strtab = (char *) &map[elf->sections[i].sh_offset];
//     }
//     if (!ft_strncmp(".dynsym", section_name, ft_strlen(".dynsym")) &&
//         elf->sections[i].sh_type == SHT_DYNSYM) {
//       elf->dynsym      = (Elf32_Sym *) &map[elf->sections[i].sh_offset];
//       elf->dynsym_size = elf->sections[i].sh_size;
//     }
//     if (!ft_strncmp(".dynstr", section_name, ft_strlen(".dynstr")) &&
//         elf->sections[i].sh_type == SHT_STRTAB) {
//       elf->dynstr = (char *) &map[elf->sections[i].sh_offset];
//     }
//   }
//   return EXIT_SUCCESS;
// }
//
// void print_symtab_x32(t_elf32 elf) {
//   ft_printf("symtab: \n");
//   for (uint32_t i = 0; i < elf.symtab_size / sizeof(Elf32_Sym); i++) {
//     char *sym_name = &elf.strtab[elf.symtab[i].st_name];
//     ft_printf("[%d] %s", i, sym_name);
//     ft_printf(" %p\n", elf.symtab[i].st_value);
//   }
// }
//
// void print_dynsym_x32(t_elf32 elf) {
//   ft_printf("dynsym: \n");
//   for (uint32_t i = 0; i < elf.dynsym_size / sizeof(Elf32_Sym); i++) {
//     char *sym_name = &elf.dynstr[elf.dynsym[i].st_name];
//     ft_printf("[%d] %s ", i, sym_name);
//     if (elf.dynsym[i].st_value)
//       ft_printf("%p", elf.dynsym[i].st_value);
//     ft_printf("\n");
//   }
// }
int handle_elf32(char *file_name, uint8_t *map, off_t file_size) {
  (void) file_name;
  (void) map;
  (void) file_size;
  ft_printf("Not handled yet...\n");
  // t_elf32 elf = {0};
  // set_elf32_infos(&elf, map, file_name, file_size);
  // print_symtab_x32(elf);
  // print_dynsym_x32(elf);
  return EXIT_SUCCESS;
}
