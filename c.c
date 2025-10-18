/*
 * c.exe - Cross-Architecture C Compiler/Linker/Runner/Package Manager
 * 
 * An opensource tool built for cross-architecture support (x86, x86_64, arm, arm64)
 * providing C compilation, linking, running, and package management capabilities.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>

#define VERSION "1.0.0"
#define MAX_ARGS 256
#define MAX_PATH 4096

/* Architecture types */
typedef enum {
    ARCH_X86,
    ARCH_X86_64,
    ARCH_ARM,
    ARCH_ARM64,
    ARCH_UNKNOWN
} Architecture;

/* Operation modes */
typedef enum {
    MODE_COMPILE,
    MODE_LINK,
    MODE_RUN,
    MODE_PACKAGE,
    MODE_HELP,
    MODE_VERSION
} OperationMode;

/* Architecture detection */
Architecture detect_architecture() {
    struct utsname sys_info;
    if (uname(&sys_info) != 0) {
        return ARCH_UNKNOWN;
    }
    
    if (strcmp(sys_info.machine, "x86_64") == 0 || strcmp(sys_info.machine, "amd64") == 0) {
        return ARCH_X86_64;
    } else if (strcmp(sys_info.machine, "i386") == 0 || strcmp(sys_info.machine, "i686") == 0) {
        return ARCH_X86;
    } else if (strcmp(sys_info.machine, "aarch64") == 0 || strcmp(sys_info.machine, "arm64") == 0) {
        return ARCH_ARM64;
    } else if (strncmp(sys_info.machine, "arm", 3) == 0) {
        return ARCH_ARM;
    }
    
    return ARCH_UNKNOWN;
}

/* Get architecture name */
const char* get_arch_name(Architecture arch) {
    switch (arch) {
        case ARCH_X86: return "x86";
        case ARCH_X86_64: return "x86_64";
        case ARCH_ARM: return "arm";
        case ARCH_ARM64: return "arm64";
        default: return "unknown";
    }
}

/* Print version information */
void print_version() {
    Architecture arch = detect_architecture();
    printf("c.exe version %s\n", VERSION);
    printf("Architecture: %s\n", get_arch_name(arch));
    printf("Cross-architecture C compiler/linker/runner/package manager\n");
}

/* Print help information */
void print_help() {
    printf("c.exe - Cross-Architecture C Compiler/Linker/Runner/Package Manager\n\n");
    printf("Usage:\n");
    printf("  c.exe [OPTIONS] <file.c>\n\n");
    printf("Modes:\n");
    printf("  -c           Compile only (produce object file)\n");
    printf("  -l           Link mode (link object files)\n");
    printf("  -r           Run mode (compile and execute)\n");
    printf("  -p           Package manager mode\n");
    printf("  -v, --version   Show version information\n");
    printf("  -h, --help      Show this help message\n\n");
    printf("Options:\n");
    printf("  -o <file>    Specify output file\n");
    printf("  -O<level>    Optimization level (0-3)\n");
    printf("  -g           Include debug information\n");
    printf("  -Wall        Enable all warnings\n");
    printf("  -I<dir>      Add include directory\n");
    printf("  -L<dir>      Add library directory\n");
    printf("  -l<lib>      Link with library\n");
    printf("  --arch=<arch>   Target architecture (x86|x86_64|arm|arm64)\n\n");
    printf("Examples:\n");
    printf("  c.exe program.c              # Compile and link program.c\n");
    printf("  c.exe -c module.c            # Compile module.c to module.o\n");
    printf("  c.exe -l main.o module.o     # Link object files\n");
    printf("  c.exe -r program.c           # Compile and run program.c\n");
    printf("  c.exe -o app program.c       # Compile to specific output\n");
}

/* Execute external command */
int execute_command(char *argv[]) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return -1;
    }
    
    if (pid == 0) {
        /* Child process */
        execvp(argv[0], argv);
        perror("execvp failed");
        exit(1);
    } else {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}

/* Compile source file */
int compile_file(const char *input, const char *output, char **extra_args, int extra_count, int compile_only) {
    char *args[MAX_ARGS];
    int argc = 0;
    
    args[argc++] = "gcc";
    
    if (compile_only) {
        args[argc++] = "-c";
    }
    
    /* Add extra arguments */
    for (int i = 0; i < extra_count; i++) {
        args[argc++] = extra_args[i];
    }
    
    args[argc++] = (char*)input;
    
    if (output) {
        args[argc++] = "-o";
        args[argc++] = (char*)output;
    }
    
    args[argc] = NULL;
    
    printf("Compiling %s...\n", input);
    return execute_command(args);
}

/* Link object files */
int link_files(char **inputs, int input_count, const char *output, char **extra_args, int extra_count) {
    char *args[MAX_ARGS];
    int argc = 0;
    
    args[argc++] = "gcc";
    
    /* Add input files */
    for (int i = 0; i < input_count; i++) {
        args[argc++] = inputs[i];
    }
    
    /* Add extra arguments */
    for (int i = 0; i < extra_count; i++) {
        args[argc++] = extra_args[i];
    }
    
    if (output) {
        args[argc++] = "-o";
        args[argc++] = (char*)output;
    }
    
    args[argc] = NULL;
    
    printf("Linking...\n");
    return execute_command(args);
}

/* Run compiled program */
int run_program(const char *program, char **args, int arg_count) {
    char *run_args[MAX_ARGS];
    run_args[0] = (char*)program;
    
    for (int i = 0; i < arg_count; i++) {
        run_args[i + 1] = args[i];
    }
    run_args[arg_count + 1] = NULL;
    
    printf("Running %s...\n", program);
    return execute_command(run_args);
}

/* Package manager operations */
int package_manager(const char *operation, const char *package) {
    printf("Package manager mode: %s %s\n", operation, package ? package : "");
    printf("Package management functionality coming soon!\n");
    printf("Planned features:\n");
    printf("  - Install C libraries and headers\n");
    printf("  - Manage dependencies\n");
    printf("  - Cross-architecture package support\n");
    return 0;
}

int main(int argc, char *argv[]) {
    OperationMode mode = MODE_COMPILE;
    const char *output_file = NULL;
    char *input_files[MAX_ARGS];
    int input_count = 0;
    char *extra_args[MAX_ARGS];
    int extra_count = 0;
    char *run_args[MAX_ARGS];
    int run_arg_count = 0;
    int compile_only = 0;
    const char *target_arch = NULL;
    
    if (argc < 2) {
        print_help();
        return 1;
    }
    
    /* Parse arguments */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        } else if (strcmp(argv[i], "-c") == 0) {
            compile_only = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            mode = MODE_LINK;
        } else if (strcmp(argv[i], "-r") == 0) {
            mode = MODE_RUN;
        } else if (strcmp(argv[i], "-p") == 0) {
            mode = MODE_PACKAGE;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            }
        } else if (strncmp(argv[i], "--arch=", 7) == 0) {
            target_arch = argv[i] + 7;
            printf("Target architecture: %s\n", target_arch);
        } else if (argv[i][0] == '-') {
            /* Other compiler flags */
            extra_args[extra_count++] = argv[i];
            /* Check if this flag takes an argument */
            if ((strcmp(argv[i], "-I") == 0 || strcmp(argv[i], "-L") == 0 || 
                 strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-O") == 0) && 
                i + 1 < argc && argv[i+1][0] != '-') {
                extra_args[extra_count++] = argv[++i];
            }
        } else {
            /* Input file */
            input_files[input_count++] = argv[i];
        }
    }
    
    if (input_count == 0 && mode != MODE_PACKAGE) {
        fprintf(stderr, "Error: No input files specified\n");
        return 1;
    }
    
    /* Execute based on mode */
    int result = 0;
    
    switch (mode) {
        case MODE_COMPILE:
            if (compile_only) {
                /* Compile each file to object file */
                for (int i = 0; i < input_count; i++) {
                    const char *out = output_file;
                    if (!out && input_count == 1) {
                        /* Generate default object file name */
                        static char obj_file[MAX_PATH];
                        snprintf(obj_file, sizeof(obj_file), "%s", input_files[i]);
                        char *dot = strrchr(obj_file, '.');
                        if (dot) *dot = '\0';
                        strcat(obj_file, ".o");
                        out = obj_file;
                    }
                    result = compile_file(input_files[i], out, extra_args, extra_count, 1);
                    if (result != 0) break;
                }
            } else {
                /* Compile and link */
                result = compile_file(input_files[0], output_file ? output_file : "a.out", 
                                    extra_args, extra_count, 0);
            }
            break;
            
        case MODE_LINK:
            result = link_files(input_files, input_count, output_file ? output_file : "a.out",
                              extra_args, extra_count);
            break;
            
        case MODE_RUN: {
            /* Compile to temporary file, run, then clean up */
            const char *tmp_output = "/tmp/c_exe_temp_output";
            result = compile_file(input_files[0], tmp_output, extra_args, extra_count, 0);
            if (result == 0) {
                result = run_program(tmp_output, run_args, run_arg_count);
                unlink(tmp_output);
            }
            break;
        }
            
        case MODE_PACKAGE:
            result = package_manager("install", input_count > 0 ? input_files[0] : NULL);
            break;
            
        default:
            fprintf(stderr, "Unknown mode\n");
            result = 1;
            break;
    }
    
    return result;
}
