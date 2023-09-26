#include <ft_nm.h>

static void set_section_by_index(Elf64_Shdr *section, int index, t_elf64 elf) {
  if (index < 1 || index >= elf.header->e_shnum)
    return;
  *section = elf.sections[index];
}

static int is_data_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".data";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_tdata_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".tdata";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_text_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".text";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_fini_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".fini";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_fini_array_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".fini_array";
  return section.sh_type == SHT_FINI_ARRAY &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_init_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".init";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_init_array_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".init_array";
  return section.sh_type == SHT_INIT_ARRAY &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_bss_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".bss";
  return section.sh_type == SHT_NOBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_tbss_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".tbss";
  return section.sh_type == SHT_NOBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_dynamic_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".dynamic";
  return section.sh_type == SHT_DYNAMIC &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_got_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".got";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_tm_clone_table(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".tm_clone_table";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_readonly_section(Elf64_Shdr section) {
  return section.sh_flags != SHF_WRITE;
}

static int is_debug_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".debug";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_code_section(Elf64_Shdr section, char st_type) {
  return section.sh_type == SHT_PROGBITS || st_type == STT_FUNC ||
         st_type == STT_OBJECT;
}

static void set_r(Elf64_Shdr section, char *type) {
  if (is_readonly_section(section))
    *type = 'r';
}

static void set_a(char st_type, char *type) {
  if (st_type == STT_FILE)
    *type = 'a';
}

static void set_w(char st_bind, char st_type, char shndx, char *type) {
  if (st_bind == STB_WEAK && st_type != STT_OBJECT)
    *type = 'w';
  if (st_bind == STB_WEAK && shndx != SHN_UNDEF && st_type != STT_OBJECT)
    *type = 'W';
}

static void set_v(char st_bind, char st_type, char shndx, char *type) {
  if (st_bind == STB_WEAK && shndx == SHN_UNDEF && st_type == STT_OBJECT)
    *type = 'v';
}

static void set_u(char shndx, char *type) {
  if (shndx == SHN_UNDEF)
    *type = 'u';
}

static void set_t(Elf64_Shdr section, t_elf64 elf, char *type) {
  if (is_text_section(section, elf) || is_init_section(section, elf) ||
      is_fini_section(section, elf))
    *type = 't';
}

static void set_d(Elf64_Shdr section, t_elf64 elf, char *type) {
  if (is_data_section(section, elf) || is_tdata_section(section, elf) ||
      is_fini_array_section(section, elf) ||
      is_init_array_section(section, elf) || is_got_section(section, elf) ||
      is_dynamic_section(section, elf) || is_tm_clone_table(section, elf))
    *type = 'd';
}

static void set_b(Elf64_Shdr section, t_elf64 elf, char *type) {
  if (is_bss_section(section, elf) || is_tbss_section(section, elf))
    *type = 'b';
}

static void set_N(Elf64_Shdr section, t_elf64 elf, char *type) {
  if (is_debug_section(section, elf))
    *type = 'N';
}

static void set_n(Elf64_Shdr section, char st_type, t_elf64 elf, char *type) {
  if (!is_debug_section(section, elf) && !is_data_section(section, elf) &&
      !is_code_section(section, st_type) && is_readonly_section(section))
    *type = 'n';
}

static void set_global(char st_bind, char *type) {
  if (st_bind == STB_GLOBAL && *type != '?')
    *type = ft_toupper(*type);
}

int set_type(char *type, Elf64_Sym symbol, t_elf64 elf) {
  char       st_bind = ELF64_ST_BIND(symbol.st_info);
  char       st_type = ELF64_ST_TYPE(symbol.st_info);
  char       shndx   = symbol.st_shndx;
  Elf64_Shdr section = {0};

  if (shndx >= elf.header->e_shnum)
    return EXIT_FAILURE;
  *type = '?';
  set_section_by_index(&section, shndx, elf);
  set_r(section, type);
  set_n(section, st_type, elf, type);
  set_u(shndx, type);
  set_t(section, elf, type);
  set_d(section, elf, type);
  set_b(section, elf, type);
  set_N(section, elf, type);
  set_a(st_type, type);
  set_w(st_bind, st_type, shndx, type);
  set_v(st_bind, st_type, shndx, type);
  set_global(st_bind, type);
  return EXIT_SUCCESS;
}
