#include <stdio.h>
#include <string.h>

int deserialize_ttf(char* file_name) {
	unsigned char data[400000];
	long file_size;

	char out[400001] = {0};

	FILE *file = fopen(file_name, "rb");
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	fread(data, file_size, 1, file);
	fclose(file);

	for (long c = 0; c < 400000; c++)
		sprintf(out[c], "%d", data[c]);
	printf(out);

	return 1;

	// char output[out + 1];
	// char padded[pad];
	// char end_line[2] = "\n\t";
	// char start[26 + sizeof(name)];
	// char end_bracket[] = "\n};\n";
	// long index = 0;
	// for (int c = 0; c < chunk; c++) {
	// 	sprintf(padded, "0x%x, ", bitmap[c]);
	// 	memcpy(output + index, padded, pad * sizeof(char));
	// 	index += pad;
	// 	if (!((c + 1) % line_width)) {
	// 		memcpy(output + index, end_line, 2 * sizeof(char));
	// 		index += 2;
	// 	}
	// 	else if (!((c + 1) % bytes))
	// 		output[index++] = ' ';
	// }
	// output[index - 3] = '\0';
	// sprintf(start, "\nunsigned char %s[] = {\n\t", name);

	// fputs(start, out_file);
	// fputs(output, out_file);
	// fputs(end_bracket, out_file);

	return 1;
}

int main() {
	deserialize_ttf("Cousine.ttf");
	return 0;
}
