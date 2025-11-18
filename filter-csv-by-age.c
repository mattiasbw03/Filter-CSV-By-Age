#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 100
#define DELIM "," // CSV delimiter

char *ifile, *ofile;
unsigned filter_age_max;
FILE *istream, *ostream;

const char USAGE[] =
    R"(Filters CSV rows, keeping only those with provided maximum age
%1$s max-age [input-file] [output-file]

Example: 
%1$s max-age 17 input.csv output.csv
%1$s max-age 10 input.csv (outputs to stdout)
%1$s max-age 54           (inputs from stdin, outputs to stdout)
)";

void filter_stream(FILE *istream, FILE *ostream) {
  char line[LINE_MAX];
  char *fgets_return;
  char *name, *age_str;
  size_t line_no = 0;

  while (
      // Read a line from `istream` and assign the return value to `fgets_return`
      (fgets_return = fgets(line, LINE_MAX, istream)) != NULL
  ) {
    ++line_no;

    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        // Assign `name` and `age_str` using `strtok`
        name = strtok(line, DELIM);
        age_str = strtok(NULL, DELIM);

        if (!age_str) {
          // Error: Age missing
          fprintf(stderr, "Line %zu: age missing (only one column).\n", line_no);
          continue;
        }
      }
    } else {
      // Error: Blank line
      fprintf(stderr, "Line %zu: blank or missing line.\n", line_no);
      continue;
    }

    // Age processing
    unsigned age;
    auto recognized_count = sscanf(age_str, "%d", &age);
    if (recognized_count == 1) {
      if (age <= filter_age_max) {
        // Forward input line to `ostream`
        fprintf(ostream, "%s,%s", name, age_str);
      }
    } else {
      // Error: Age not a number
      fprintf(stderr, "Line %zu: age not recognized as a number.\n", line_no);
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 4:
    // max-age ifile ofile
    ofile = argv[3];
  case 3:
    // max-age ifile
    ifile = argv[2];
  case 2:
    // max-age
    if (!sscanf(argv[1], "%d", &filter_age_max)) {
      puts("First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;
  default:
    printf(USAGE, argv[0]);
    return EXIT_SUCCESS;
  }

  if (ifile) {
    // Open `ifile` and assign it to `istream`
    istream = fopen(ifile, "r");
    if (!istream) {
      fprintf(stderr, "Could not open input file '%s'.\n", ifile);
      exit(EXIT_FAILURE);
    }
  } else {
    // Set `istream` if no file provided
    istream = stdin;
  }

  if (ofile) {
    // Open `ofile` and assign it to `ostream`
    ostream = fopen(ofile, "w");
    if (!ostream) {
      fprintf(stderr, "Could not open output file '%s'.\n", ofile);
      exit(EXIT_FAILURE);
    }
  } else {
    // Set `ostream` if no file provided
    ostream = stdout;
  }

  // Process filtering
  filter_stream(istream, ostream);

  // Close any open files (if not stdin/stdout)
  if (istream != stdin)
    fclose(istream);
  if (ostream != stdout)
    fclose(ostream);

  return EXIT_SUCCESS;
}
