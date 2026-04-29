void kernel_main() 
{
    char *video_memory = (char*)0xb8000;
    unsigned char color = 0x0C; // red
    char *msg = "Kernel!";
    char c;
    int i = 0;

    while ((c = *msg++) != '\0') {
       video_memory[i*2 + 0] = c;
       video_memory[i*2 + 1] = color;
       i++;
    }
}
