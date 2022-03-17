#include <stdio.h>
#include <string.h>

#define height 32
#define width 32
#define bytes 4
#define pad 6

#define elements height * width
#define chunk elements * bytes
#define line_width ((80 / pad) - (80 / pad) % bytes)
#define out chunk * pad + (2 * chunk * pad / line_width)

int deserialize_bitmap(char* name, char* file_name, FILE* out_file) {
	unsigned char bitmap[chunk];
	FILE *file = fopen(file_name, "rb");
	fseek(file, 0, SEEK_END);
	fseek(file, (ftell(file) - chunk), SEEK_SET);
	fread(bitmap, chunk, 1, file);
	fclose(file);

	char output[out + 1];
	char padded[pad];
	char end_line[2] = "\n\t";
	char start[26 + sizeof(name)];
	char end_bracket[] = "\n};\n";
	long index = 0;
	for (int c = 0; c < chunk; c++) {
		sprintf(padded, "0x%x, ", bitmap[c]);
		memcpy(output + index, padded, pad * sizeof(char));
		index += pad;
		if (!((c + 1) % line_width)) {
			memcpy(output + index, end_line, 2 * sizeof(char));
			index += 2;
		}
		else if (!((c + 1) % bytes))
			output[index++] = ' ';
	}
	output[index - 3] = '\0';
	sprintf(start, "\nunsigned char %s[] = {\n\t", name);

	fputs(start, out_file);
	fputs(output, out_file);
	fputs(end_bracket, out_file);

	return 1;
}

int main() {

	char* file_names[12] = {
		"./bitmap_files/close_icon.bmp",
		"./bitmap_files/close_hover.bmp",
		"./bitmap_files/close_down.bmp",
		"./bitmap_files/maximize_icon.bmp",
		"./bitmap_files/maximize_hover.bmp",
		"./bitmap_files/maximize_down.bmp",
		"./bitmap_files/minimize_icon.bmp",
		"./bitmap_files/minimize_hover.bmp",
		"./bitmap_files/minimize_down.bmp",
		"./bitmap_files/restore_icon.bmp",
		"./bitmap_files/restore_hover.bmp",
		"./bitmap_files/restore_down.bmp"
	};

	char* names[12] = {
		"close_bmp",
		"close_hover_bmp",
		"close_down_bmp",
		"maximize_bmp",
		"maximize_hover_bmp",
		"maximize_down_bmp",
		"minimize_bmp",
		"minimize_hover_bmp",
		"minimize_down_bmp",
		"restore_bmp",
		"restore_hover_bmp",
		"restore_down_bmp"
	};

	FILE *out_file = fopen("output.c", "w");

	for (int file_ptr = 0; file_ptr < 12; file_ptr++)
		deserialize_bitmap(names[file_ptr], file_names[file_ptr], out_file);

	fclose(out_file);

	return 0;
}
